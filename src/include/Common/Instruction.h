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
    virtual bool hasBreakpoint() const = 0;
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

    InstructionBase(const InstructionBase&) = delete;
    InstructionBase& operator=(const InstructionBase&) = delete;

protected:
    virtual int invokeOperator(Bytes...) = 0;

    int applyOperand()
    {
        int offset = 0;
        applyByte<Byte>();
        int cycles = 0;
        cycles = applyArguments({ applyByte<Bytes>()... }, std::index_sequence_for<Bytes...>());
        for (int i = -size(); i < 0; ++i) {
            state.incrementProgramApplicationCount(i);
        }
        return cycles;
    }

    std::string operandToString() const
    {
        std::ostringstream ss;
        for (int i = size() - 1; i > 0; --i) {
            state.printProgramByte(i, ss);
        }
        return ss.str();
    }

    int size() const
    {
        return sizeof...(Bytes) + 1;
    }

    State& state;

private:
    bool hasBreakpoint() const override
    {
        for (int i = 0; i < size(); ++i) {
            if (state.hasBreakpoint(i)) {
                return true;
            }
        }
        return false;
    }

    template <typename Byte>
    Byte applyByte()
    {
        return state.applyProgramByte();
    }

    template<std::size_t... Indices>
    int applyArguments(const std::tuple<Bytes...>& arguments, std::index_sequence<Indices...>)
    {
        return invokeOperator(std::get<Indices>(arguments)...);
    }
};
