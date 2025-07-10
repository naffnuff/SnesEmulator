#include "CpuInstructionDecoder.h"

#define PROFILING_ENABLED false

#include "CpuOpcode.h"

namespace CPU {

template<int Code>
struct OpcodeWrapper : Instruction<State>
{
    int execute(State& state) override
    {
        return Opcode<State, Code>::execute(state);
    }

    std::string opcodeToString() const override
    {
        return Opcode<State, Code>::opcodeToString();
    }

    std::string toString(const State& state) const override
    {
        return Opcode<State, Code>::Instruction::toString(state);
    }

    void applyBreakpoints(const State& state) const override
    {
        Opcode<State, Code>::Instruction::Type::applyBreakpoints(state);
    }

    int size() const override
    {
        return Opcode<State, Code>::Instruction::Type::size();
    }
};

template<std::size_t... Indices>
constexpr std::array<Instruction<State>*, Byte::spaceSize> makeInstructionSequence(std::index_sequence<Indices...>)
{
    return { new OpcodeWrapper<Indices>()... };
}

static constexpr std::array<Instruction<State>*, Byte::spaceSize> makeInstructions()
{
    return makeInstructionSequence(std::make_index_sequence<Byte::spaceSize>{ });
}

std::array<Instruction<State>*, Byte::spaceSize> InstructionDecoder::instructions = makeInstructions();

}