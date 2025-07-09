#pragma once

#include <unordered_map>
#include <string>

static const std::unordered_map<std::string, std::tuple<std::vector<std::string>, std::vector<std::string>>> addressModeImplementations =
{
    {
        "Absolute",
        {
            {
                "MemoryAccess access = obsoleteState.getMemoryAccess(lowByte, highByte);",
                "return Operator::invoke(obsoleteState, access);"
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
                "return Operator::invoke(obsoleteState, Word(lowByte, highByte));"
            },
            {
                R"(return Operator::toString() + " $" + operandToString();)"
            }
        }
    },
    {
        "AbsoluteIndexedIndirect",
        {
            {
                "Word address(lowByte, highByte);",
                "address += Word(obsoleteState.readRegister<State::Register::X>());",
                "return Operator::invoke(obsoleteState, obsoleteState.readMemoryWord(address));"
            },
            {
                R"(return Operator::toString() + " [$" + operandToString() + "+X]";)"
            }
        }
    },
    {
        "AbsoluteIndexedRegister",
        {
            {
                "MemoryAccess access = obsoleteState.getMemoryAccess(Word(Word(lowByte, highByte) + obsoleteState.readRegister<FirstRegister>()));",
                "return Operator::invoke(obsoleteState, access, obsoleteState.readRegister<SecondRegister>());"
            },
            {
                R"(return Operator::toString() + " $" + operandToString() + "+" + State::getRegisterName<FirstRegister>() + ", " + State::getRegisterName<SecondRegister>();)"
            }
        }
    },
    {
        "AbsoluteRegister",
        {
            {
                "MemoryAccess access = obsoleteState.getMemoryAccess(lowByte, highByte);",
                "return Operator::invoke(obsoleteState, access, obsoleteState.readRegister<RegisterIndex>());"
            },
            {
                R"(return Operator::toString() + " $" + operandToString() + ", " + State::getRegisterName<RegisterIndex>();)"
            }
        }
    },
    {
        "CarryMemoryBit",
        {
            {
                R"(throw NotYetImplementedException("CarryMemoryBit");)",
                "MemoryAccess access = obsoleteState.getMemoryAccess(0);",
                "return Operator::invoke(obsoleteState, access, 0);"
            },
            {
                R"(return Operator::toString() + " $" + operandToString() + " TODO";)"
            }
        }
    },
    {
        "CarryNegatedMemoryBit",
        {
            {
                R"(throw NotYetImplementedException("CarryNegatedMemoryBit");)",
                "MemoryAccess access = obsoleteState.getMemoryAccess(0);",
                "return Operator::invoke(obsoleteState, access, 0);"
            },
            {
                R"(return Operator::toString() + " $" + operandToString() + " TODO";)"
            }
        }
    },
    {
        "Direct",
        {
            {
                "MemoryAccess access = obsoleteState.getDirectMemoryAccess(lowByte);",
                "return Operator::invoke(obsoleteState, access);"
            },
            {
                R"(return Operator::toString() + " $" + operandToString();)"
            }
        }
    },
    {
        "DirectDirect",
        {
            {
                "MemoryAccess access = obsoleteState.getDirectMemoryAccess(highByte);",
                "return Operator::invoke(obsoleteState, access, obsoleteState.readDirectMemoryByte(lowByte));"
            },
            {
                "std::string o = operandToString();",
                R"(return Operator::toString() + " $" + o.substr(0, 2) + ", $" + o.substr(2, 2);)"
            }
        }
    },
    {
        "DirectImmediate",
        {
            {
                "MemoryAccess access = obsoleteState.getDirectMemoryAccess(highByte);",
                "return Operator::invoke(obsoleteState, access, lowByte);"
            },
            {
                "std::string operand = operandToString();",
                R"(return Operator::toString() + " $" + operand.substr(0, 2) + ", #$" + operand.substr(2, 2);)"
            }
        }
    },
    {
        "DirectIndexed",
        {
            {
                "MemoryAccess access = obsoleteState.getDirectMemoryAccess(lowByte + obsoleteState.readRegister<RegisterIndex>());",
                "return Operator::invoke(obsoleteState, access);"
            },
            {
                R"(return Operator::toString() + " $" + operandToString() + "+" + State::getRegisterName<RegisterIndex>();)"
            }
        }
    },
    {
        "DirectIndexedIndirectRegister",
        {
            {
                "Word address = obsoleteState.readDirectMemoryWord(lowByte + obsoleteState.readRegister<FirstRegister>());",
                "MemoryAccess access = obsoleteState.getMemoryAccess(address);",
                "return Operator::invoke(obsoleteState, access, obsoleteState.readRegister<SecondRegister>());"
            },
            {
                R"(return Operator::toString() + " [$" + operandToString() + "+" + State::getRegisterName<FirstRegister>() + "], " + State::getRegisterName<SecondRegister>();)"
            }
        }
    },
    {
        "DirectIndexedProgramCounterRelative",
        {
            {
                "MemoryAccess access = obsoleteState.getDirectMemoryAccess(lowByte + obsoleteState.readRegister<RegisterIndex>());",
                "return Operator::invoke(obsoleteState, access, highByte);"
            },
            {
                "std::ostringstream ss;",
                R"(ss << Operator::toString() + " $";)",
                R"(ss << obsoleteState.inspectProgramByte(1) << "+X, $";)",
                "ss << obsoleteState.getProgramCounter(int((int8_t)size() + (int8_t)obsoleteState.inspectProgramByte(2)));",
                "return ss.str();"
            }
        }
    },
    {
        "DirectIndexedRegister",
        {
            {
                "MemoryAccess access = obsoleteState.getDirectMemoryAccess(lowByte + obsoleteState.readRegister<FirstRegister>());",
                "return Operator::invoke(obsoleteState, access, obsoleteState.readRegister<SecondRegister>());"
            },
            {
                R"(return Operator::toString() + " $" + operandToString() + "+" + State::getRegisterName<FirstRegister>() + ", " + State::getRegisterName<SecondRegister>();)"
            }
        }
    },
    {
        "DirectIndirectIndexedRegister",
        {
            {
                "Word address = obsoleteState.readDirectMemoryWord(lowByte) + obsoleteState.readRegister<FirstRegister>();",
                "MemoryAccess access = obsoleteState.getMemoryAccess(address);",
                "return Operator::invoke(obsoleteState, access, obsoleteState.readRegister<SecondRegister>());"
            },
            {
                R"(return Operator::toString() + " [$" + operandToString() + "]+" + State::getRegisterName<FirstRegister>() + ", " + State::getRegisterName<SecondRegister>();)"
            }
        }
    },
    {
        "DirectProgramCounterRelative",
        {
            {
                "MemoryAccess access = obsoleteState.getDirectMemoryAccess(lowByte);",
                "return Operator::invoke(obsoleteState, access, highByte);"
            },
            {
                "std::ostringstream ss;",
                R"(ss << Operator::toString() + " $";)",
                R"(ss << obsoleteState.inspectProgramByte(1) << ", $";)",
                "ss << obsoleteState.getProgramCounter(int((int8_t)size() + (int8_t)obsoleteState.inspectProgramByte(2)));",
                "return ss.str();"
            }
        }
    },
    {
        "DirectRegister",
        {
            {
                "MemoryAccess access = obsoleteState.getDirectMemoryAccess(lowByte);",
                "return Operator::invoke(obsoleteState, access, obsoleteState.readRegister<RegisterIndex>());"
            },
            {
                R"(return Operator::toString() + " $" + operandToString() + ", " + State::getRegisterName<RegisterIndex>();)"
            }
        }
    },
    {
        "DirectYAccumulator",
        {
            {
                "MemoryAccess access = obsoleteState.getDirectMemoryAccess(lowByte);",
                "return Operator::invoke(obsoleteState, access, obsoleteState.getYAccumulator());"
            },
            {
                R"(return Operator::toString() + " $" + operandToString() + ", YA";)"
            }
        }
    },
    {
        "Implied",
        {
            {
                "return Operator::invoke(obsoleteState);"
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
                R"(throw NotYetImplementedException("IndirectIndirect");)",
                "MemoryAccess access = obsoleteState.getMemoryAccess(0);",
                "return Operator::invoke(obsoleteState, access, 0);"
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
                R"(throw NotYetImplementedException("MemoryBit");)",
                "MemoryAccess access = obsoleteState.getMemoryAccess(0);",
                "return Operator::invoke(obsoleteState, access, 0);"
            },
            {
                R"(return Operator::toString() + " $" + operandToString() + " TODO";)"
            }
        }
    },
    {
        "MemoryBitCarry",
        {
            {
                R"(throw NotYetImplementedException("MemoryBitCarry");)",
                "MemoryAccess access = obsoleteState.getMemoryAccess(0);",
                "return Operator::invoke(obsoleteState, access, 0);"
            },
            {
                R"(return Operator::toString() + " $" + operandToString() + " TODO";)"
            }
        }
    },
    {
        "ProgramCounterRelative",
        {
            {
                "return Operator::invoke(obsoleteState, lowByte);"
            },
            {
                "std::ostringstream ss;",
                R"(ss << Operator::toString() + " $";)",
                "ss << obsoleteState.getProgramCounter(int((int8_t)size() + (int8_t)obsoleteState.inspectProgramByte(1)));",
                "return ss.str();"
            }
        }
    },
    {
        "Register",
        {
            {
                "State::RegisterAccess access = obsoleteState.getRegisterAccess<RegisterIndex>();",
                "return Operator::invoke(obsoleteState, access);"
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
                "State::RegisterAccess registerAccess = obsoleteState.getRegisterAccess<RegisterIndex>();",
                "return Operator::invoke(obsoleteState, registerAccess, obsoleteState.readMemoryByte(lowByte, highByte));"
            },
            {
                R"(return Operator::toString() + " " + State::getRegisterName<RegisterIndex>() + ", $" + operandToString();)"
            }
        }
    },
    {
        "RegisterAbsoluteIndexed",
        {
            {
                "State::RegisterAccess registerAccess = obsoleteState.getRegisterAccess<FirstRegister>();",
                "Word address(lowByte, highByte);",
                "address += Word(obsoleteState.readRegister<SecondRegister>());",
                "return Operator::invoke(obsoleteState, registerAccess, obsoleteState.readMemoryByte(address));"
            },
            {
                R"(return Operator::toString() + " " + State::getRegisterName<FirstRegister>() + ", $" + operandToString() + "+" + State::getRegisterName<SecondRegister>();)"
            }
        }
    },
    {
        "RegisterDirect",
        {
            {
                "State::RegisterAccess registerAccess = obsoleteState.getRegisterAccess<RegisterIndex>();",
                "return Operator::invoke(obsoleteState, registerAccess, obsoleteState.readDirectMemoryByte(lowByte));"
            },
            {
                R"(return Operator::toString() + " " + State::getRegisterName<RegisterIndex>() + ", $" + operandToString();)"
            }
        }
    },
    {
        "RegisterDirectIndexed",
        {
            {
                "State::RegisterAccess registerAccess = obsoleteState.getRegisterAccess<FirstRegister>();",
                "return Operator::invoke(obsoleteState, registerAccess, obsoleteState.readDirectMemoryByte(lowByte + obsoleteState.readRegister<SecondRegister>()));"
            },
            {
                R"(return Operator::toString() + " " + State::getRegisterName<FirstRegister>() + ", $" + operandToString() + "+X";)"
            }
        }
    },
    {
        "RegisterDirectIndexedIndirect",
        {
            {
                "State::RegisterAccess registerAccess = obsoleteState.getRegisterAccess<FirstRegister>();",
                "Word address = obsoleteState.readDirectMemoryWord(lowByte + obsoleteState.readRegister<SecondRegister>());",
                "return Operator::invoke(obsoleteState, registerAccess, obsoleteState.readMemoryByte(address));"
            },
            {
                R"(return Operator::toString() + " " + State::getRegisterName<FirstRegister>() + ", [$" + operandToString() + "+" + State::getRegisterName<SecondRegister>() + "]";)"
            }
        }
    },
    {
        "RegisterDirectIndirectIndexed",
        {
            {
                "State::RegisterAccess registerAccess = obsoleteState.getRegisterAccess<FirstRegister>();",
                "Word indexedAddress = obsoleteState.readDirectMemoryWord(lowByte) + obsoleteState.readRegister<SecondRegister>();",
                "return Operator::invoke(obsoleteState, registerAccess, obsoleteState.readMemoryByte(indexedAddress));"
            },
            {
                R"(return Operator::toString() + " " + State::getRegisterName<FirstRegister>() + ", [$" + operandToString() + "]+" + State::getRegisterName<SecondRegister>();)"
            }
        }
    },
    {
        "RegisterImmediate",
        {
            {
                "State::RegisterAccess registerAccess = obsoleteState.getRegisterAccess<RegisterIndex>();",
                "return Operator::invoke(obsoleteState, registerAccess, lowByte);"
            },
            {
                R"(return Operator::toString() + " " + State::getRegisterName<RegisterIndex>() + ", #$" + operandToString();)"
            }
        }
    },
    {
        "RegisterIndirectIncrementRegister",
        {
            {
                "State::RegisterAccess registerAccess = obsoleteState.getRegisterAccess<FirstRegister>();",
                "Byte firstRegisterValue = registerAccess.readByte();",
                "MemoryAccess access = obsoleteState.getDirectMemoryAccess(firstRegisterValue);",
                "registerAccess.writeByte(firstRegisterValue + 1);",
                "return Operator::invoke(obsoleteState, access, obsoleteState.readRegister<SecondRegister>());"
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
                "MemoryAccess access = obsoleteState.getDirectMemoryAccess(obsoleteState.readRegister<FirstRegister>());",
                "return Operator::invoke(obsoleteState, access, obsoleteState.readRegister<SecondRegister>());"
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
                "State::RegisterAccess registerAccess = obsoleteState.getRegisterAccess<RegisterIndex>();",
                "return Operator::invoke(obsoleteState, registerAccess, lowByte);"
            },
            {
                "std::ostringstream ss;",
                R"(ss << Operator::toString() + " " + State::getRegisterName<RegisterIndex>() + ", $";)",
                "ss << obsoleteState.getProgramCounter(int((int8_t)size() + (int8_t)obsoleteState.inspectProgramByte(1)));",
                "return ss.str();"
            }
        }
    },
    {
        "RegisterRegister",
        {
            {
                "State::RegisterAccess registerAccess = obsoleteState.getRegisterAccess<FirstRegister>();",
                "return Operator::invoke(obsoleteState, registerAccess, obsoleteState.readRegister<SecondRegister>());"
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
                "State::RegisterAccess registerAccess = obsoleteState.getRegisterAccess<FirstRegister>();",
                "Byte value = obsoleteState.readDirectMemoryByte(obsoleteState.readRegister<SecondRegister>());",
                "return Operator::invoke(obsoleteState, registerAccess, value);"
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
                R"(throw NotYetImplementedException("RegisterRegisterIndirectIncrement");)",
                "MemoryAccess access = obsoleteState.getMemoryAccess(0);",
                "return Operator::invoke(obsoleteState, access, 0);"
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
                R"(throw NotYetImplementedException("Table");)",
                "MemoryAccess access = obsoleteState.getMemoryAccess(0);",
                "return Operator::invoke(obsoleteState, access, 0);"
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
                R"(throw NotYetImplementedException("UPage");)",
                "MemoryAccess access = obsoleteState.getMemoryAccess(0);",
                "return Operator::invoke(obsoleteState, access, 0);"
            },
            {
                R"(return Operator::toString() + " $" + operandToString() + " TODO";)"
            }
        }
    },
    {
        "YAccumulator",
        {
            {
                "State::RegisterAccess firstRegisterAccess = obsoleteState.getRegisterAccess<State::Register::A>();",
                "State::RegisterAccess secondRegisterAccess = obsoleteState.getRegisterAccess<State::Register::Y>();",
                "return Operator::invoke(obsoleteState, firstRegisterAccess, secondRegisterAccess);"
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
                "State::RegisterAccess access = obsoleteState.getRegisterAccess<State::Register::A>();",
                "return Operator::invoke(obsoleteState, access, obsoleteState.readDirectMemoryWord(lowByte));"
            },
            {
                R"(return Operator::toString() + " YA, $" + operandToString();)"
            }
        }
    },
    {
        "YAccumulatorIndex",
        {
            {
                "State::RegisterAccess access = obsoleteState.getRegisterAccess<State::Register::A>();",
                "return Operator::invoke(obsoleteState, access, obsoleteState.readRegister<RegisterIndex>());"
            },
            {
                R"(return Operator::toString() + " YA, " + State::getRegisterName<RegisterIndex>();)"
            }
        }
    }
};