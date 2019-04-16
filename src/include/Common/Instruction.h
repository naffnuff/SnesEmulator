#pragma once
 
#include <sstream>
#include <iomanip>
#include <tuple>
#include <utility>

#include "Types.h"

class Instruction
{
public:
    virtual std::string toString() const = 0;
    virtual std::string opcodeToString() const = 0;
    virtual int execute() = 0;
    virtual int size() const = 0;
};

template<typename State, typename... Bytes>
class InstructionBase : public Instruction
{
public:
    InstructionBase(State& state)
        : state(state)
    {
    }

protected:
    virtual int invokeOperator(Bytes...) = 0;

    int applyOperand()
    {
        state.incrementProgramCounter(size());
        int offset = -1;
        return invokeOperator(applyByte<Bytes>(offset)...);
    }

    std::string operandToString() const
    {
        std::ostringstream ss;
        int offset = size() - 1;
        ((ss << readByte<Bytes>(offset)), ...);
        return ss.str();
    }

    int size() const
    {
        return sizeof...(Bytes) + 1;
    }

    State& state;

private:
    template <typename Byte>
    Byte applyByte(int& offset)
    {
        return state.applyProgramByte(offset--);
    }

    template <typename Byte>
    Byte readByte(int& offset) const
    {
        return state.readProgramByte(offset--);
    }
};
