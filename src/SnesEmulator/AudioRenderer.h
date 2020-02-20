#pragma once

#include <stdexcept>
#include <iostream>
#include <array>
#include <vector>
#include <mutex>

namespace Audio {

struct Exception : std::runtime_error
{
    Exception(const std::string& message)
        : std::runtime_error("Audio Exception: " + message)
    {
    }
};

class Renderer
{
public:
    static constexpr int tableSize = 50;
    static constexpr int voiceCount = 8;

    Renderer(std::ostream& output, std::ostream& error)
        : output(output)
        , error(error)
    {
    }

    ~Renderer();

    void initialize();
    void start();
    void tick();

public:
    struct Data
    {
        bool playing = false;
        float counter = 0.0f;
        float pitch = 1.0f;
    };

    float sine[tableSize];

    std::array<Data, voiceCount> data;

    std::ostream& output;
    std::ostream& error;

    bool initialized = false;

    int counter = 0;
    
    uint64_t masterCycle = 0;
    std::mutex mutex;
    std::condition_variable condition;
    
    bool inputUnderflow = false;
    bool inputOverflow = false;
    bool outputUnderflow = false;
    bool outputOverflow = false;
    bool primingOutput = false;
};

}
