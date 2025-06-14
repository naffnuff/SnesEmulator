#pragma once

#include <chrono>
#include <unordered_map>

#include "Output.h"

struct CompilationUnitProfilerCount
{
    static inline int value = 0;
};

class ScopeProfiler;
class CompilationUnitProfiler;

class GlobalProfiler
{
public:
    struct Entry
    {
        const char* name = nullptr;
        std::chrono::nanoseconds time;
        int count = 0;
        std::chrono::nanoseconds averageTime;
    };

    GlobalProfiler()
        : start(std::chrono::high_resolution_clock::now())
    {
    }

    static GlobalProfiler& get()
    {
        if (!instance)
        {
            instance = new GlobalProfiler();
        }
        return *instance;
    }

    void registerProfiler(const char* name, CompilationUnitProfiler* profiler)
    {
        profilers.push_back({ name, profiler });
    }

    void printEntries(Output& output) const;

private:
    static GlobalProfiler* instance;
    std::vector<std::pair<const char*, CompilationUnitProfiler*>> profilers;
    std::chrono::high_resolution_clock::time_point start;
};

class CompilationUnitProfiler
{
public:
    CompilationUnitProfiler(const char* name)
        : unitName(name)
    {
        GlobalProfiler::get().registerProfiler(unitName, this);
    }

    void profileScope(int id, const char* name, const std::chrono::nanoseconds& time)
    {
        if (entries.empty())
        {
            std::cout << unitName << " " << CompilationUnitProfilerCount::value << std::endl;
            entries.resize(CompilationUnitProfilerCount::value);
        }
        entries[id].name = name;
        entries[id].time += time;
        ++entries[id].count;
    }

public:
    std::vector<GlobalProfiler::Entry> entries;
    const char* unitName;
};

class ScopeProfiler
{
public:
    ScopeProfiler(int id, const char* name, CompilationUnitProfiler& profiler)
        : id(id)
        , name(name)
        , start(std::chrono::high_resolution_clock::now())
        , profiler(profiler)
    {
    }

    ~ScopeProfiler()
    {
        const std::chrono::nanoseconds scopeTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
        profiler.profileScope(id, name, scopeTime);
    }

private:
    const int id;
    const char* name;
    std::chrono::high_resolution_clock::time_point start;
    CompilationUnitProfiler& profiler;
};

template<int N>
struct ScopeIdTracker
{
    static constexpr int value = N;
    static inline bool registered = (CompilationUnitProfilerCount::value = N + 1, true);
};

#define SCOPE_ID (ScopeIdTracker<__COUNTER__>::value)

#ifdef PROFILING_ENABLED
#define CREATE_NAMED_PROFILER(name) namespace { static CompilationUnitProfiler compilationUnitProfiler(name); }
#define CREATE_PROFILER() CREATE_NAMED_PROFILER(__FILE__)
#define PROFILE_SCOPE_IMPL2(line, id, name) ScopeProfiler scopeProfiler##line(id, name, compilationUnitProfiler);
#define PROFILE_SCOPE_IMPL(line, id, name) PROFILE_SCOPE_IMPL2(line, id, name)
#define PROFILE_SCOPE(name) PROFILE_SCOPE_IMPL(__LINE__, SCOPE_ID, name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
#else
#define CREATE_NAMED_PROFILER(name)
#define CREATE_PROFILER()
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()
#endif