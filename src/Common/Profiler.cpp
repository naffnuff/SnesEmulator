#include "Profiler.h"

#include <algorithm>
#include <iomanip>

GlobalProfiler* GlobalProfiler::instance = nullptr;

void GlobalProfiler::printEntries(Output& output) const
{
    const std::chrono::nanoseconds totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
    Output::Lock lock(output);
    for (const auto& profiler : profilers)
    {
        if (profiler.second->entries.empty())
        {
            continue;
        }
        std::vector<Entry> entries = profiler.second->entries;
        for (Entry& entry : entries)
        {
            if (entry.count > 0)
            {
                entry.averageTime = entry.time / entry.count;
            }
        }
        std::sort(entries.begin(), entries.end(), [](const Entry& first, const Entry& second)
            {
                return first.count > second.count;
            });
        output.printLine(lock, profiler.first);
        for (int i = 0; i < entries.size(); ++i)
        {
            const char* scopeName = entries[i].name;
            if (scopeName)
            {
                std::ostringstream oss;
                oss << std::left << std::setw(40) << scopeName
                    << std::right << std::setw(10) << entries[i].count << " calls, "
                    << std::setw(10) << std::setprecision(4) << entries[i].averageTime << " on average, "
                    << std::setw(8) << std::fixed << std::setprecision(2)
                    << (double)entries[i].time.count() * 100.0 / (double)totalTime.count() << "% of total time";

                output.printLine(lock, oss.str());
            }
        }
    }
}