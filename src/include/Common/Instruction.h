#pragma once
 
#include <sstream>
#include <iomanip>
#include <tuple>
#include <utility>

#include "Types.h"

template<typename State>
class Instruction
{
public:
    virtual ~Instruction() {}
    virtual std::string toString(const State& state) const = 0;
    virtual std::string opcodeToString() const = 0;
    virtual void applyBreakpoints(const State& state) const = 0;
    virtual int execute(State& state) = 0;
    virtual int size() const = 0;
};

template<typename State, typename... Bytes>
class InstructionType
{
public:
    template<typename Instruction>
    static int applyOperand(State& state)
    {
        applyByte<Byte>(state);
        return applyArguments<Instruction>(state, { applyByte<Bytes>(state)... }, std::index_sequence_for<Bytes...>());
    }

    static std::string operandToString(const State& state)
    {
        std::ostringstream ss;
        for (int i = size() - 1; i > 0; --i)
        {
            state.printProgramByte(i, ss);
        }
        return ss.str();
    }

    static int size()
    {
        return sizeof...(Bytes) + 1;
    }

    static void applyBreakpoints(const State& state)
    {
        for (int i = 0; i < size(); ++i)
        {
            state.applyBreakpoint(i);
        }
    }

private:
    template<typename Byte>
    static Byte applyByte(State& state)
    {
        return state.applyProgramByte();
    }

    template<typename Instruction, std::size_t... Indices>
    static int applyArguments(State& state, const std::tuple<Bytes...>& arguments, std::index_sequence<Indices...>)
    {
        return Instruction::invokeOperator(state, std::get<Indices>(arguments)...);
    }
};

EXCEPTION(InvalidInstructionTypeException, Exception)

template<typename State>
struct InvalidInstructionType
{
    static void applyBreakpoints(const State& state)
    {
        throw InvalidInstructionTypeException();
    }

    static int size()
    {
        throw InvalidInstructionTypeException();
    }
};

EXCEPTION(InvalidInstructionException, Exception)

template<typename State>
struct InvalidInstruction
{
    using Type = InvalidInstructionType<State>;

    static std::string toString(const State& state)
    {
        throw InvalidInstructionException();
    }
};

EXCEPTION(InvalidOpcodeException, Exception)

template<typename State, int Code>
struct Opcode
{
    using Instruction = InvalidInstruction<State>;

    static int execute(State& state)
    {
        throw InvalidOpcodeException(Byte(Code));
    }

    static std::string opcodeToString()
    {
        throw InvalidOpcodeException(Byte(Code));
    }
};