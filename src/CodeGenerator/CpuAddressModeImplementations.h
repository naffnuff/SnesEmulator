#pragma once

#include <unordered_map>
#include <string>

static const std::unordered_map<std::string, std::tuple<std::vector<std::string>, std::vector<std::string>>> addressModeImplementations =
{
    {
        "Absolute",
        {
            {
                "MemoryAccess access = state.getMemoryAccess(lowByte, highByte);",
                "return Operator::invoke(state, access);"
            },
            {
                R"(return Operator::toString() + " $" + operandToString();)"
            }
        }
    },
    {
        "Absolute_ControlFlow",
        {
            {
                "return Operator::invoke(state, Word(lowByte, highByte));"
            },
            {
                R"(return Operator::toString() + " $" + operandToString();)"
            }
        }
    },
    {
        "AbsoluteIndexed",
        {
            {
                "Long staticAddress(lowByte, highByte, state.getDataBank());",
                "Long indexedAddress = staticAddress + state.getIndexRegister<Register>();",
                "MemoryAccess access = state.getMemoryAccess(indexedAddress);",
                "return getCycles(staticAddress, indexedAddress) + Operator::invoke(state, access);"
            },
            {
                R"(return Operator::toString() + " $" + operandToString() + "," + state.getIndexRegisterName<Register>();)"
            }
        }
    },
    {
        "AbsoluteIndexedIndirect",
        {
            {
                "Word indexedAddress = Word(lowByte, highByte) + state.getIndexRegister<State::IndexRegister::X>();",
                "Long longAddress(indexedAddress, state.getProgramBank());",
                "return Operator::invoke(state, state.readMemoryWord<State::MemoryType::WrappingMask::Bank>(longAddress));"
            },
            {
                R"CODE(return Operator::toString() + " ($" + operandToString() + ",X)";)CODE"
            }
        }
    },
    {
        "AbsoluteIndirect",
        {
            {
                "return Operator::invoke(state, state.readMemoryWord<State::MemoryType::WrappingMask::Bank>(Long(lowByte, highByte, 0)));"
            },
            {
                R"CODE(return Operator::toString() + " ($" + operandToString() + ")";)CODE"
            }
        }
    },
    {
        "AbsoluteIndirectLong",
        {
            {
                "return Operator::invoke(state, state.readMemoryLong<State::MemoryType::WrappingMask::Bank>(Long(lowByte, highByte, 0)));"
            },
            {
                R"(return Operator::toString() + " $" + operandToString();)"
            }
        }
    },
    {
        "AbsoluteLong",
        {
            {
                "MemoryAccess access = state.getMemoryAccess(lowByte, highByte, bankByte);",
                "return Operator::invoke(state, access);"
            },
            {
                R"(return Operator::toString() + " $" + operandToString();)"
            }
        }
    },
    {
        "AbsoluteLong_ControlFlow",
        {
            {
                "return Operator::invoke(state, Long(lowByte, highByte, bankByte));"
            },
            {
                R"(return Operator::toString() + " $" + operandToString();)"
            }
        }
    },
    {
        "AbsoluteLongIndexedX",
        {
            {
                "MemoryAccess access = state.getMemoryAccess(lowByte, highByte, bankByte, state.getIndexRegister<State::IndexRegister::X>());",
                "return Operator::invoke(state, access);"
            },
            {
                R"(return Operator::toString() + " $" + operandToString() + ",X";)"
            }
        }
    },
    {
        "Accumulator",
        {
            {
                "int cycles = 0;",
                "if (state.is16Bit(State::Flag::m))",
                "{",
                "    cycles -= 2;",
                "}",
                "State::AccumulatorAccess accumulatorAccess = state.getAccumulatorAccess();",
                "return cycles + Operator::invoke(state, accumulatorAccess);"
            },
            {
                R"(return Operator::toString() + " A";)"
            }
        }
    },
    {
        "BlockMove",
        {
            {
                "Word byteCount = state.getAccumulatorC();",
                "if (byteCount != 0)",
                "{",
                "    state.incrementProgramCounter(Word(-size()));",
                "}",
                "state.setAccumulatorC(byteCount - 1);",
                "return Operator::invoke(state, highByte, lowByte, byteCount);"
            },
            {
                "std::string operands = operandToString();",
                R"(return Operator::toString() + " $" + operands.substr(0, 2) + ",$" + operands.substr(2, 2);)"
            }
        }
    },
    {
        "DirectPage",
        {
            {
                "int cycles = 0;",
                "if (state.getDirectPageRegister().getLowByte() != 0)",
                "{",
                "    cycles += 1;",
                "}",
                "MemoryAccess access = state.getDirectMemoryAccess(lowByte);",
                "return cycles + Operator::invoke(state, access);"
            },
            {
                R"(return Operator::toString() + " $" + operandToString();)"
            }
        }
    },
    {
        "DirectPageIndexed",
        {
            {
                "int cycles = 0;",
                "if (Byte(state.getDirectPageRegister()))",
                "{",
                "    cycles += 1;",
                "}",
                "MemoryAccess access = state.getDirectMemoryAccess(lowByte, state.getIndexRegister<Register>());",
                "return cycles + Operator::invoke(state, access);"
            },
            {
                R"(return Operator::toString() + " $" + operandToString() + "," + State::getIndexRegisterName<Register>();)"
            }
        }
    },
    {
        "DirectPageIndexedIndirectX",
        {
            {
                R"(throw NotYetImplementedException("DirectPageIndexedIndirectX");)",
                "int cycles = 0;",
                "if ((Byte)state.getDirectPageRegister())",
                "{",
                "    cycles += 1;",
                "}",
                "MemoryAccess access = state.getMemoryAccess(0, 0, 0, 0);",
                "return cycles + Operator::invoke(state, access);"
            },
            {
                R"(return Operator::toString() + " $" + operandToString() + " TODO";)"
            }
        }
    },
    {
        "DirectPageIndirect",
        {
            {
                "int cycles = 0;",
                "if ((Byte)state.getDirectPageRegister())",
                "{",
                "    cycles += 1;",
                "}",
                "Long address(state.getDirectMemoryAccess(lowByte).readWord(), state.getDataBank());",
                "MemoryAccess access = state.getMemoryAccess(address);",
                "return cycles + Operator::invoke(state, access);"
            },
            {
                R"CODE(return Operator::toString() + " ($" + operandToString() + ")";)CODE"
            }
        }
    },
    {
        "DirectPageIndirect_ControlFlow",
        {
            {
                "int cycles = 0;",
                "if ((Byte)state.getDirectPageRegister())",
                "{",
                "    cycles += 1;",
                "}",
                "Word address = state.getDirectMemoryAccess(lowByte).readWord();",
                "return cycles + Operator::invoke(state, address);"
            },
            {
                R"CODE(return Operator::toString() + " ($" + operandToString() + ")";)CODE"
            }
        }
    },
    {
        "DirectPageIndirectIndexedY",
        {
            {
                "int cycles = 0;",
                "if ((Byte)state.getDirectPageRegister())",
                "{",
                "    cycles += 1;",
                "}",
                "Long address(state.getDirectMemoryAccess(lowByte).readWord(), state.getDataBank());",
                "Long indexedAddress = address + state.getIndexRegister<State::IndexRegister::Y>();",
                "if (address >> 8 != indexedAddress >> 8)",
                "{",
                "    cycles += 1;",
                "}",
                "MemoryAccess access = state.getMemoryAccess(indexedAddress);",
                "return cycles + Operator::invoke(state, access);"
            },
            {
                R"(return Operator::toString() + " ($" + operandToString() + "),Y";)"
            }
        }
    },
    {
        "DirectPageIndirectLong",
        {
            {
                "int cycles = 0;",
                "if ((Byte)state.getDirectPageRegister())",
                "{",
                "    cycles += 1;",
                "}",
                "Long address = state.getDirectMemoryAccess(lowByte).readLong();",
                "MemoryAccess access = state.getMemoryAccess(address);",
                "return cycles + Operator::invoke(state, access);"
            },
            {
                R"(return Operator::toString() + " [$" + operandToString() + "]";)"
            }
        }
    },
    {
        "DirectPageIndirectLongIndexedY",
        {
            {
                "int cycles = 0;",
                "if ((Byte)state.getDirectPageRegister())",
                "{",
                "    cycles += 1;",
                "}",
                "Long address = state.getDirectMemoryAccess(lowByte).readLong();",
                "MemoryAccess access = state.getMemoryAccess(address, state.getIndexRegister<State::IndexRegister::Y>());",
                "return cycles + Operator::invoke(state, access);"
            },
            {
                R"(return Operator::toString() + " [$" + operandToString() + "], Y";)"
            }
        }
    },
    {
        "Immediate",
        {
            {
                "Memory<Byte> memory(1);",
                "memory.createLocation<ReadOnlyMemory>(0, lowByte);",
                "MemoryAccess<Memory<Byte>> access(memory, 0);",
                "return Operator::invoke(state, access);"
            },
            {
                R"(return Operator::toString() + " #$" + operandToString();)"
            }
        }
    },
    {
        "Immediate16Bit",
        {
            {
                "Memory<Byte> memory(2);",
                "memory.createLocation<ReadOnlyMemory>(0, lowByte);",
                "memory.createLocation<ReadOnlyMemory>(1, highByte);",
                "MemoryAccess access(memory, 0);",
                "return Operator::invoke16Bit(state, access);"
            },
            {
                R"(return Operator::toString() + " #$" + operandToString();)"
            }
        }
    },
    {
        "Implied",
        {
            {
                "return Operator::invoke(state);"
            },
            {
                "return Operator::toString();"
            }
        }
    },
    {
        "ProgramCounterRelative",
        {
            {
                "return Operator::invoke(state, (int8_t)lowByte);"
            },
            {
                "std::ostringstream ss;",
                R"(ss << Operator::toString() + " $";)",
                "ss << state.getProgramCounter(int((int8_t)size() + (int8_t)state.inspectProgramByte(1)));",
                "return ss.str();"
            }
        }
    },
    {
        "ProgramCounterRelativeLong",
        {
            {
                "return Operator::invoke(state, int16_t(highByte << 8 | lowByte));"
            },
            {
                "std::ostringstream ss;",
                R"(ss << Operator::toString() + " $";)",
                "ss << state.getProgramCounter(int((int8_t)size() + int16_t(state.inspectProgramByte(2) << 8 | state.inspectProgramByte(1))));",
                "return ss.str();"
            }
        }
    },
    {
        "StackRelative",
        {
            {
                "MemoryAccess access = state.getMemoryAccess<State::MemoryType::WrappingMask::Bank>(Long(state.getStackPointer() + lowByte, 0));",
                "return Operator::invoke(state, access);"
            },
            {
                R"(return Operator::toString() + " $" + operandToString() + ",S";)"
            }
        }
    },
    {
        "StackRelativeIndirectIndexedY",
        {
            {
                "Word address = state.readMemoryWord<State::MemoryType::WrappingMask::Bank>(Long(state.getStackPointer() + lowByte, 0));",
                "MemoryAccess access = state.getMemoryAccess(Long(address, state.getDataBank()), state.getIndexRegister<State::IndexRegister::Y>());",
                "return Operator::invoke(state, access);"
            },
            {
                R"(return Operator::toString() + " ($" + operandToString() + ",S), Y";)"
            }
        }
    }
};