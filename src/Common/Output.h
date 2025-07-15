#pragma once

#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <mutex>

#ifdef _WIN32
#include <windows.h>
#endif

#define LOG_NAME(NAME) static constexpr const char* NAME = #NAME

class Log
{
public:
    enum class Level
    {
        None,
        Error,
        Info,
        Debug
    };

    static Level toLevel(const std::string& name)
    {
        for (int i = 0; levelNames[i] != 0; ++i) {
            if (name == levelNames[i]) {
                return Level(i);
            }
        }
        throw std::runtime_error("Unknown log name: " + name);
    }

    static std::string toLevelName(Level level)
    {
        return levelNames[size_t(level)];
    }

private:
    static constexpr const char* levelNames[] =
    {
        "none",
        "error",
        "info",
        "debug",
        nullptr
    };
};

class Output
{
public:
#ifdef _WIN32
    enum class Color
    {
        Red = FOREGROUND_RED,
        Green = FOREGROUND_GREEN,
        Yellow = FOREGROUND_RED | FOREGROUND_GREEN,
        Blue = FOREGROUND_BLUE,
        Magenta = FOREGROUND_RED | FOREGROUND_BLUE,
        Cyan = FOREGROUND_BLUE | FOREGROUND_GREEN,
        Default = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
    };
#else
    enum class Color
    {
        Red = 31,
        Green = 32,
        Yellow = 33,
        Blue = 34,
        Magenta = 35,
        Cyan = 36,
        Default = 0
    };
#endif

    class Lock;

    class System
    {
    public:
        System() = delete;

        System(const System&) = delete;
        System& operator=(const System&) = delete;

        System(const std::string& logConfigFilename)
            : logConfigFilename(logConfigFilename)
        {
            deserializeLogConfig();
            ensureExists("default");
            serializeLogConfig();
        }

        void deserializeLogConfig()
        {
            std::ifstream logConfigFile(logConfigFilename);
            if (logConfigFile) {
                std::string entry;
                while (std::getline(logConfigFile, entry)) {
                    std::istringstream ss(entry);
                    std::string logName;
                    ss >> logName;
                    std::string level;
                    ss >> level;
                    if (!level.empty()) {
                        logLevels[logName] = level;
                    }
                }
            }
        }

        void serializeLogConfig()
        {
            std::ofstream logConfigFile(logConfigFilename);
            for (auto kvp : logLevels) {
                logConfigFile << kvp.first << " " << kvp.second << std::endl;
            }
        }

        void ensureExists(const std::string& logName)
        {
            if (logLevels[logName].empty()) {
                if (logLevels["default"].empty()) {
                    logLevels["default"] = Log::toLevelName(Log::Level::Info);
                }
                logLevels[logName] = logLevels["default"];
                serializeLogConfig();
            }
        }

#ifdef _WIN32
        void setOutputColor(Lock&, const Output&, Color color, bool bright)
        {
            int effectiveColor = int(color);
            if (bright) {
                effectiveColor |= FOREGROUND_INTENSITY;
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WORD(effectiveColor));
        }
#else
        void setOutputColor(Lock& lock, const Output& output, Color color, bool bright)
        {
            output.print(lock, "\33[", (int)color);
            if (bright) {
                output.print(lock, ";", 1);
            }
            output.print(lock, "m");
        }
#endif

        Log::Level getLogLevel(const std::string& logName)
        {
            ensureExists(logName);
            return Log::toLevel(logLevels[logName]);
        }

        std::mutex& getMutex()
        {
            return mutex;
        }

    private:
        std::ostream& outputStream = std::cout;
        std::mutex mutex;
        std::string logConfigFilename;
        std::map<std::string, std::string> logLevels;

        friend class Output;
    };

    class ColorScope;

    class Lock
    {
    public:
        Lock(System& system)
            : system(system)
            , lock(system.getMutex())
        {
        }

        Lock(Output& output)
            : Lock(output.system)
        {
        }

        Lock() = delete;

        Lock(const Lock&) = delete;
        Lock& operator=(const Lock&) = delete;

    private:
        System& system;
        std::scoped_lock<std::mutex> lock;

        friend ColorScope;
    };

    class ColorScope
    {
    public:
        ColorScope(Lock& lock, const Output& output, Color color, bool bright)
            : system(lock.system)
            , lock(lock)
            , output(output)
        {
            system.setOutputColor(lock, output, color, bright);
        }

        ~ColorScope()
        {
            system.setOutputColor(lock, output, Color::Default, false);
        }

        ColorScope() = delete;

        ColorScope(const ColorScope&) = delete;
        ColorScope& operator=(const ColorScope&) = delete;

    private:
        System& system;
        Lock& lock;
        const Output& output;
    };

    Output(System& system, const std::string& name)
        : system(system)
        , logLevel(system.getLogLevel(name))
    {
    }

    Output(Output& output, const std::string& name)
        : Output(output.system, name)
    {
    }

    Output() = delete;

    Output(const Output&) = delete;
    Output& operator=(const Output&) = delete;

    template<typename... Ts>
    void print(const Lock&, Ts&&... values) const
    {
        if (logLevel > Log::Level::None) {
            std::ostream& outputStream = system.outputStream;
            (void)(outputStream << ... << std::forward<Ts>(values));
        }
    }

    template<typename... Ts>
    void print(Lock&&, Ts&&... values) const
    {
        if (logLevel > Log::Level::None) {
            std::ostream& outputStream = system.outputStream;
            (void)(outputStream << ... << std::forward<Ts>(values));
        }
    }

    template<typename... Ts>
    void printLine(const Lock&, Ts&&... values) const
    {
        if (logLevel > Log::Level::None) {
            std::ostream& outputStream = system.outputStream;
            (void)(outputStream << ... << std::forward<Ts>(values));
            outputStream << std::endl;
        }
    }

    template<typename... Ts>
    void printLine(Color color, bool bright, Ts&&... values) const
    {
        if (logLevel > Log::Level::None) {
            Lock lock(system);
            ColorScope colorScope(lock, *this, color, bright);
            printLine(lock, std::forward<Ts>(values)...);
        }
    }

    template<typename... Ts>
    void log(Log::Level level, Color color, bool bright, Ts&&... values) const
    {
        if (logLevel >= level) {
            printLine(color, bright, std::forward<Ts>(values)...);
        }
    }

    template<typename... Ts>
    void error(Ts&&... values) const
    {
        log(Log::Level::Error, Color::Red, true, std::forward<Ts>(values)...);
    }

    template<typename... Ts>
    void info(Ts&&... values) const
    {
        log(Log::Level::Info, Color::Default, true, std::forward<Ts>(values)...);
    }

    template<typename... Ts>
    void debug(Ts&&... values) const
    {
        log(Log::Level::Debug, Color::Green, true, std::forward<Ts>(values)...);
    }

private:
    System& system;
    Log::Level logLevel;
};