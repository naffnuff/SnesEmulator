#pragma once

#include <ctime>
#include <set>

#include "Instruction.h"

class Emulator
{
public:
    Emulator(std::ostream& output, std::istream& input, std::ostream& error)
        : output(output)
        , input(input)
        , error(error)
    {
    }

    void run();

private:
    std::ostream& output;
    std::istream& input;
    std::ostream& error;
};

