#include "Profiler.h"

#include <algorithm>

GlobalProfiler* GlobalProfiler::instance = nullptr;

void GlobalProfiler::printEntries(Output& output) const
{
    const std::chrono::nanoseconds totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
    Output::Lock lock(output);
    for (const auto& profiler : profilers)
    {
        std::vector<Entry> entries = profiler.second->entries;
        std::sort(entries.begin(), entries.end(), [](const Entry& first, const Entry& second)
            {
                return first.second > second.second;
            });
        output.printLine(lock, profiler.first);
        for (int i = 0; i < entries.size(); ++i)
        {
            const char* scopeName = entries[i].first;
            if (scopeName)
            {
                const std::chrono::nanoseconds time = entries[i].second;
                output.printLine(lock, scopeName, ": ", time, " (", (double)time.count() * 100.0 / (double)totalTime.count(), "%)");
            }
        }
    }
}