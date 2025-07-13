#pragma once

#include <chrono>
#include <unordered_map>

#include "Output.h"

struct CompilationUnitProfilerCount
{
    static inline int value = 0;
};

template<bool>
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

template<bool Enabled>
class ScopeProfiler
{
public:
    ScopeProfiler(int, const char*, CompilationUnitProfiler&) {}
};

template<>
class ScopeProfiler<true>
{
public:
    ScopeProfiler(int id, const char* name, CompilationUnitProfiler& profiler)
        : id(id)
        , name(name)
        , profiler(profiler)
        , start(std::chrono::high_resolution_clock::now())
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
    CompilationUnitProfiler& profiler;
    std::chrono::high_resolution_clock::time_point start;
};

template<int N>
struct ScopeIdTracker
{
    static constexpr int value = N;
    static inline bool registered = (CompilationUnitProfilerCount::value = N + 1, true);
};

#define SCOPE_ID (ScopeIdTracker<__COUNTER__>::value)

#if PROFILING_ENABLED

#define CREATE_NAMED_PROFILER(name) namespace { static CompilationUnitProfiler compilationUnitProfiler(name); }
#define CREATE_PROFILER() CREATE_NAMED_PROFILER(__FILE__)

#define PROFILE_SCOPE_IMPL2(condition, line, id, name) ScopeProfiler<condition> scopeProfiler##line(id, name, compilationUnitProfiler);
#define PROFILE_SCOPE_IMPL(condition, line, id, name) PROFILE_SCOPE_IMPL2(condition, line, id, name)
#define PROFILE_IF(condition, name) PROFILE_SCOPE_IMPL(condition, __LINE__, SCOPE_ID, name)
#define PROFILE_SCOPE(name) PROFILE_IF(true, name)

#else

#define CREATE_NAMED_PROFILER(name)
#define CREATE_PROFILER()
#define PROFILE_SCOPE(name)
#define PROFILE_IF(condition, name)
#endif