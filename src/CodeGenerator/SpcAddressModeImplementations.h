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
                R"(return Operator::toString() + " $" + Type::operandToString(state);)"
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
                R"(return Operator::toString() + " $" + Type::operandToString(state);)"
            }
        }
    },
    {
        "AbsoluteIndexedIndirect",
        {
            {
                "Word address(lowByte, highByte);",
                "address += Word(state.readRegister<State::Register::X>());",
                "return Operator::invoke(state, state.readMemoryWord(address));"
            },
            {
                R"(return Operator::toString() + " [$" + Type::operandToString(state) + "+X]";)"
            }
        }
    },
    {
        "AbsoluteIndexedRegister",
        {
            {
                "MemoryAccess access = state.getMemoryAccess(Word(Word(lowByte, highByte) + state.readRegister<FirstRegister>()));",
                "return Operator::invoke(state, access, state.readRegister<SecondRegister>());"
            },
            {
                R"(return Operator::toString() + " $" + Type::operandToString(state) + "+" + State::getRegisterName<FirstRegister>() + ", " + State::getRegisterName<SecondRegister>();)"
            }
        }
    },
    {
        "AbsoluteRegister",
        {
            {
                "MemoryAccess access = state.getMemoryAccess(lowByte, highByte);",
                "return Operator::invoke(state, access, state.readRegister<RegisterIndex>());"
            },
            {
                R"(return Operator::toString() + " $" + Type::operandToString(state) + ", " + State::getRegisterName<RegisterIndex>();)"
            }
        }
    },
    {
        "CarryMemoryBit",
        {
            {
                R"(throw NotYetImplementedException("SPC::AddressMode::CarryMemoryBit");)",
                "MemoryAccess access = state.getMemoryAccess(0);",
                "return Operator::invoke(state, access, 0);"
            },
            {
                R"(return Operator::toString() + " $" + Type::operandToString(state) + " TODO";)"
            }
        }
    },
    {
        "CarryNegatedMemoryBit",
        {
            {
                R"(throw NotYetImplementedException("SPC::AddressMode::CarryNegatedMemoryBit");)",
                "MemoryAccess access = state.getMemoryAccess(0);",
                "return Operator::invoke(state, access, 0);"
            },
            {
                R"(return Operator::toString() + " $" + Type::operandToString(state) + " TODO";)"
            }
        }
    },
    {
        "Direct",
        {
            {
                "MemoryAccess access = state.getDirectMemoryAccess(lowByte);",
                "return Operator::invoke(state, access);"
            },
            {
                R"(return Operator::toString() + " $" + Type::operandToString(state);)"
            }
        }
    },
    {
        "DirectDirect",
        {
            {
                "MemoryAccess access = state.getDirectMemoryAccess(highByte);",
                "return Operator::invoke(state, access, state.readDirectMemoryByte(lowByte));"
            },
            {
                "std::string o = Type::operandToString(state);",
                R"(return Operator::toString() + " $" + o.substr(0, 2) + ", $" + o.substr(2, 2);)"
            }
        }
    },
    {
        "DirectImmediate",
        {
            {
                "MemoryAccess access = state.getDirectMemoryAccess(highByte);",
                "return Operator::invoke(state, access, lowByte);"
            },
            {
                "std::string operand = Type::operandToString(state);",
                R"(return Operator::toString() + " $" + operand.substr(0, 2) + ", #$" + operand.substr(2, 2);)"
            }
        }
    },
    {
        "DirectIndexed",
        {
            {
                "MemoryAccess access = state.getDirectMemoryAccess(lowByte + state.readRegister<RegisterIndex>());",
                "return Operator::invoke(state, access);"
            },
            {
                R"(return Operator::toString() + " $" + Type::operandToString(state) + "+" + State::getRegisterName<RegisterIndex>();)"
            }
        }
    },
    {
        "DirectIndexedIndirectRegister",
        {
            {
                "Word address = state.readDirectMemoryWord(lowByte + state.readRegister<FirstRegister>());",
                "MemoryAccess access = state.getMemoryAccess(address);",
                "return Operator::invoke(state, access, state.readRegister<SecondRegister>());"
            },
            {
                R"(return Operator::toString() + " [$" + Type::operandToString(state) + "+" + State::getRegisterName<FirstRegister>() + "], " + State::getRegisterName<SecondRegister>();)"
            }
        }
    },
    {
        "DirectIndexedProgramCounterRelative",
        {
            {
                "MemoryAccess access = state.getDirectMemoryAccess(lowByte + state.readRegister<RegisterIndex>());",
                "return Operator::invoke(state, access, highByte);"
            },
            {
                "std::ostringstream ss;",
                R"(ss << Operator::toString() + " $";)",
                R"(ss << state.inspectProgramByte(1) << "+X, $";)",
                "ss << state.getProgramCounter(int((int8_t)Type::size() + (int8_t)state.inspectProgramByte(2)));",
                "return ss.str();"
            }
        }
    },
    {
        "DirectIndexedRegister",
        {
            {
                "MemoryAccess access = state.getDirectMemoryAccess(lowByte + state.readRegister<FirstRegister>());",
                "return Operator::invoke(state, access, state.readRegister<SecondRegister>());"
            },
            {
                R"(return Operator::toString() + " $" + Type::operandToString(state) + "+" + State::getRegisterName<FirstRegister>() + ", " + State::getRegisterName<SecondRegister>();)"
            }
        }
    },
    {
        "DirectIndirectIndexedRegister",
        {
            {
                "Word address = state.readDirectMemoryWord(lowByte) + state.readRegister<FirstRegister>();",
                "MemoryAccess access = state.getMemoryAccess(address);",
                "return Operator::invoke(state, access, state.readRegister<SecondRegister>());"
            },
            {
                R"(return Operator::toString() + " [$" + Type::operandToString(state) + "]+" + State::getRegisterName<FirstRegister>() + ", " + State::getRegisterName<SecondRegister>();)"
            }
        }
    },
    {
        "DirectProgramCounterRelative",
        {
            {
                "MemoryAccess access = state.getDirectMemoryAccess(lowByte);",
                "return Operator::invoke(state, access, highByte);"
            },
            {
                "std::ostringstream ss;",
                R"(ss << Operator::toString() + " $";)",
                R"(ss << state.inspectProgramByte(1) << ", $";)",
                "ss << state.getProgramCounter(int((int8_t)Type::size() + (int8_t)state.inspectProgramByte(2)));",
                "return ss.str();"
            }
        }
    },
    {
        "DirectRegister",
        {
            {
                "MemoryAccess access = state.getDirectMemoryAccess(lowByte);",
                "return Operator::invoke(state, access, state.readRegister<RegisterIndex>());"
            },
            {
                R"(return Operator::toString() + " $" + Type::operandToString(state) + ", " + State::getRegisterName<RegisterIndex>();)"
            }
        }
    },
    {
        "DirectYAccumulator",
        {
            {
                "MemoryAccess access = state.getDirectMemoryAccess(lowByte);",
                "return Operator::invoke(state, access, state.getYAccumulator());"
            },
            {
                R"(return Operator::toString() + " $" + Type::operandToString(state) + ", YA";)"
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
                R"(return Operator::toString();)"
            }
        }
    },
    {
        "IndirectIndirect",
        {
            {
                R"(throw NotYetImplementedException("SPC::AddressMode::IndirectIndirect");)",
                "MemoryAccess access = state.getMemoryAccess(0);",
                "return Operator::invoke(state, access, 0);"
            },
            {
                R"(return Operator::toString() + " TODO";)"
            }
        }
    },
    {
        "MemoryBit",
        {
            {
                R"(throw NotYetImplementedException("SPC::AddressMode::MemoryBit");)",
                "MemoryAccess access = state.getMemoryAccess(0);",
                "return Operator::invoke(state, access, 0);"
            },
            {
                R"(return Operator::toString() + " $" + Type::operandToString(state) + " TODO";)"
            }
        }
    },
    {
        "MemoryBitCarry",
        {
            {
                R"(throw NotYetImplementedException("SPC::AddressMode::MemoryBitCarry");)",
                "MemoryAccess access = state.getMemoryAccess(0);",
                "return Operator::invoke(state, access, 0);"
            },
            {
                R"(return Operator::toString() + " $" + Type::operandToString(state) + " TODO";)"
            }
        }
    },
    {
        "ProgramCounterRelative",
        {
            {
                "return Operator::invoke(state, lowByte);"
            },
            {
                "std::ostringstream ss;",
                R"(ss << Operator::toString() + " $";)",
                "ss << state.getProgramCounter(int((int8_t)Type::size() + (int8_t)state.inspectProgramByte(1)));",
                "return ss.str();"
            }
        }
    },
    {
        "Register",
        {
            {
                "State::RegisterAccess access = state.getRegisterAccess<RegisterIndex>();",
                "return Operator::invoke(state, access);"
            },
            {
                R"(return Operator::toString() + " " + State::getRegisterName<RegisterIndex>();)"
            }
        }
    },
    {
        "RegisterAbsolute",
        {
            {
                "State::RegisterAccess registerAccess = state.getRegisterAccess<RegisterIndex>();",
                "return Operator::invoke(state, registerAccess, state.readMemoryByte(lowByte, highByte));"
            },
            {
                R"(return Operator::toString() + " " + State::getRegisterName<RegisterIndex>() + ", $" + Type::operandToString(state);)"
            }
        }
    },
    {
        "RegisterAbsoluteIndexed",
        {
            {
                "State::RegisterAccess registerAccess = state.getRegisterAccess<FirstRegister>();",
                "Word address(lowByte, highByte);",
                "address += Word(state.readRegister<SecondRegister>());",
                "return Operator::invoke(state, registerAccess, state.readMemoryByte(address));"
            },
            {
                R"(return Operator::toString() + " " + State::getRegisterName<FirstRegister>() + ", $" + Type::operandToString(state) + "+" + State::getRegisterName<SecondRegister>();)"
            }
        }
    },
    {
        "RegisterDirect",
        {
            {
                "State::RegisterAccess registerAccess = state.getRegisterAccess<RegisterIndex>();",
                "return Operator::invoke(state, registerAccess, state.readDirectMemoryByte(lowByte));"
            },
            {
                R"(return Operator::toString() + " " + State::getRegisterName<RegisterIndex>() + ", $" + Type::operandToString(state);)"
            }
        }
    },
    {
        "RegisterDirectIndexed",
        {
            {
                "State::RegisterAccess registerAccess = state.getRegisterAccess<FirstRegister>();",
                "return Operator::invoke(state, registerAccess, state.readDirectMemoryByte(lowByte + state.readRegister<SecondRegister>()));"
            },
            {
                R"(return Operator::toString() + " " + State::getRegisterName<FirstRegister>() + ", $" + Type::operandToString(state) + "+X";)"
            }
        }
    },
    {
        "RegisterDirectIndexedIndirect",
        {
            {
                "State::RegisterAccess registerAccess = state.getRegisterAccess<FirstRegister>();",
                "Word address = state.readDirectMemoryWord(lowByte + state.readRegister<SecondRegister>());",
                "return Operator::invoke(state, registerAccess, state.readMemoryByte(address));"
            },
            {
                R"(return Operator::toString() + " " + State::getRegisterName<FirstRegister>() + ", [$" + Type::operandToString(state) + "+" + State::getRegisterName<SecondRegister>() + "]";)"
            }
        }
    },
    {
        "RegisterDirectIndirectIndexed",
        {
            {
                "State::RegisterAccess registerAccess = state.getRegisterAccess<FirstRegister>();",
                "Word indexedAddress = state.readDirectMemoryWord(lowByte) + state.readRegister<SecondRegister>();",
                "return Operator::invoke(state, registerAccess, state.readMemoryByte(indexedAddress));"
            },
            {
                R"(return Operator::toString() + " " + State::getRegisterName<FirstRegister>() + ", [$" + Type::operandToString(state) + "]+" + State::getRegisterName<SecondRegister>();)"
            }
        }
    },
    {
        "RegisterImmediate",
        {
            {
                "State::RegisterAccess registerAccess = state.getRegisterAccess<RegisterIndex>();",
                "return Operator::invoke(state, registerAccess, lowByte);"
            },
            {
                R"(return Operator::toString() + " " + State::getRegisterName<RegisterIndex>() + ", #$" + Type::operandToString(state);)"
            }
        }
    },
    {
        "RegisterIndirectIncrementRegister",
        {
            {
                "State::RegisterAccess registerAccess = state.getRegisterAccess<FirstRegister>();",
                "Byte firstRegisterValue = registerAccess.readByte();",
                "MemoryAccess access = state.getDirectMemoryAccess(firstRegisterValue);",
                "registerAccess.writeByte(firstRegisterValue + 1);",
                "return Operator::invoke(state, access, state.readRegister<SecondRegister>());"
            },
            {
                R"(return Operator::toString() + " (" + State::getRegisterName<FirstRegister>() + ")+, " + State::getRegisterName<SecondRegister>();)"
            }
        }
    },
    {
        "RegisterIndirectRegister",
        {
            {
                "MemoryAccess access = state.getDirectMemoryAccess(state.readRegister<FirstRegister>());",
                "return Operator::invoke(state, access, state.readRegister<SecondRegister>());"
            },
            {
                R"(return Operator::toString() + " (" + State::getRegisterName<FirstRegister>() + "), " + State::getRegisterName<SecondRegister>();)"
            }
        }
    },
    {
        "RegisterProgramCounterRelative",
        {
            {
                "State::RegisterAccess registerAccess = state.getRegisterAccess<RegisterIndex>();",
                "return Operator::invoke(state, registerAccess, lowByte);"
            },
            {
                "std::ostringstream ss;",
                R"(ss << Operator::toString() + " " + State::getRegisterName<RegisterIndex>() + ", $";)",
                "ss << state.getProgramCounter(int((int8_t)Type::size() + (int8_t)state.inspectProgramByte(1)));",
                "return ss.str();"
            }
        }
    },
    {
        "RegisterRegister",
        {
            {
                "State::RegisterAccess registerAccess = state.getRegisterAccess<FirstRegister>();",
                "return Operator::invoke(state, registerAccess, state.readRegister<SecondRegister>());"
            },
            {
                R"(return Operator::toString() + " " + State::getRegisterName<FirstRegister>() + ", " + State::getRegisterName<SecondRegister>();)"
            }
        }
    },
    {
        "RegisterRegisterIndirect",
        {
            {
                "State::RegisterAccess registerAccess = state.getRegisterAccess<FirstRegister>();",
                "Byte value = state.readDirectMemoryByte(state.readRegister<SecondRegister>());",
                "return Operator::invoke(state, registerAccess, value);"
            },
            {
                R"CODE(return Operator::toString() + " " + State::getRegisterName<FirstRegister>() + ", (" + State::getRegisterName<SecondRegister>() + ")";)CODE"
            }
        }
    },
    {
        "RegisterRegisterIndirectIncrement",
        {
            {
                R"(throw NotYetImplementedException("SPC::AddressMode::RegisterRegisterIndirectIncrement");)",
                "MemoryAccess access = state.getMemoryAccess(0);",
                "return Operator::invoke(state, access, 0);"
            },
            {
                R"(return Operator::toString() + " TODO";)"
            }
        }
    },
    {
        "Table",
        {
            {
                R"(throw NotYetImplementedException("SPC::AddressMode::Table");)",
                "MemoryAccess access = state.getMemoryAccess(0);",
                "return Operator::invoke(state, access, 0);"
            },
            {
                R"(return Operator::toString() + " TODO";)"
            }
        }
    },
    {
        "UPage",
        {
            {
                R"(throw NotYetImplementedException("SPC::AddressMode::UPage");)",
                "MemoryAccess access = state.getMemoryAccess(0);",
                "return Operator::invoke(state, access, 0);"
            },
            {
                R"(return Operator::toString() + " $" + Type::operandToString(state) + " TODO";)"
            }
        }
    },
    {
        "YAccumulator",
        {
            {
                "State::RegisterAccess firstRegisterAccess = state.getRegisterAccess<State::Register::A>();",
                "State::RegisterAccess secondRegisterAccess = state.getRegisterAccess<State::Register::Y>();",
                "return Operator::invoke(state, firstRegisterAccess, secondRegisterAccess);"
            },
            {
                R"(return Operator::toString() + " YA";)"
            }
        }
    },
    {
        "YAccumulatorDirect",
        {
            {
                "State::RegisterAccess access = state.getRegisterAccess<State::Register::A>();",
                "return Operator::invoke(state, access, state.readDirectMemoryWord(lowByte));"
            },
            {
                R"(return Operator::toString() + " YA, $" + Type::operandToString(state);)"
            }
        }
    },
    {
        "YAccumulatorIndex",
        {
            {
                "State::RegisterAccess access = state.getRegisterAccess<State::Register::A>();",
                "return Operator::invoke(state, access, state.readRegister<RegisterIndex>());"
            },
            {
                R"(return Operator::toString() + " YA, " + State::getRegisterName<RegisterIndex>();)"
            }
        }
    }
};