#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>

namespace
{

struct Instruction
{
    std::string name;
    std::string mnemonic;
    std::string comment;
    std::string code;
    std::string classname;
    std::string addressMode;
    std::string addressModeClass;
    std::string size;
    std::string sizeRemark;
    std::string cycles;
    std::set<int> cyclesRemarks;
    std::string addressModeClassArg;
    bool extraCycleForPageBoundary = false;

    void validate()
    {
        if (name.empty())
        {
            throw std::runtime_error("Instruction name is empty");
        }

        if (mnemonic.empty())
        {
            throw std::runtime_error("Instruction " + name + ": shortname is empty");
        }

        if (classname.empty())
        {
            throw std::runtime_error("Instruction " + name + ": handlername is empty");
        }

        if (code.size() != 2)
        {
            throw std::runtime_error("Instruction " + name + ": code out of range: " + code);
        }

        if (size != "1" && size != "2" && size != "3" && size != "4")
        {
            throw std::runtime_error("Instruction " + name + ": size out of range: " + size);
        }

        if (sizeRemark != "" && sizeRemark != "16" && sizeRemark != "17" && sizeRemark != "18" && sizeRemark != "19")
        {
            throw std::runtime_error("Instruction " + name + ": remark is invalid: " + sizeRemark);
        }

        if (cycles != "0" && cycles != "1" && cycles != "2" && cycles != "3" && cycles != "4" && cycles != "5" && cycles != "6" && cycles != "7" && cycles != "8")
        {
            throw std::runtime_error("Instruction " + name + ": cycles out of range: " + cycles);
        }
    }
};

struct Opcode
{
    std::string comment;
    bool notYetImplemented = false;
};

std::string getRemark(int remarkIndex)
{
    switch (remarkIndex)
    {
    case 1: return "�1: Add 1 cycle if m=0 (16-bit memory/accumulator)";
    case 2: return "�2: Add 1 cycle if low byte of Direct Page Register is non-zero";
    case 3: return "�3: Add 1 cycle if adding index crosses a page boundary";
    case 5: return "�5: Add 2 cycles if m=0 (16-bit memory/accumulator)";
    case 7: return "�7: Add 1 cycle if branch is taken";
    case 8: return "�8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) ";
    case 9: return "�9: Add 1 cycle for 65816 native mode (e=0)";
    case 10: return "�10: Add 1 cycle if x=0 (16-bit index registers)";
    case 13: return "�13: 7 cycles per byte moved";
    case 14: return "�14: Uses 3 cycles to shut the processor down; additional cycles are required by reset to restart it";
    case 15: return "�15: Uses 3 cycles to shut the processor down; additional cycles are required by interrupt to restart it";
    case 16: return "�16: Byte and cycle counts subject to change in future processors which expand WDM into 2-byte opcode portions of instructions of varying lengths";
    case 17: return "�17: Add 1 byte if m=0 (16-bit memory/accumulator)";
    case 18: return "�18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte";
    case 19: return "�19: Add 1 byte if x=0 (16-bit index registers)";
    case 20: return "�20: TODO manually add exception for 3";
    case 21: return "�21: Remove 2 cycles for the special case of Accumulator";
    default: return "";
    }
}

struct CycleModification
{
    std::string condition;
    std::string modification;
};

CycleModification getCycleModification(int remarkIndex)
{
    switch (remarkIndex)
    {
    case 1: return { "state.is16Bit(State::m)", "cycles += 1" }; // Add 1 cycle if m=0 (16-bit memory / accumulator)
    case 2: return { "(Byte)state.getDirectPage()", "cycles += 1" }; // Add 1 cycle if low byte of Direct Page Register is non-zero
    case 3: return { "true /*index added crosses page boundary*/", "cycles += 1;\n            throw std::runtime_error(\"TODO03\")" }; // Add 1 cycle if adding index crosses a page boundary
    case 5: return { "state.is16Bit(State::m)", "cycles += 2" }; // Add 2 cycles if m=0 (16-bit memory / accumulator)
    case 7: return { "true /*branch taken*/", "cycles += 1;\n            throw std::runtime_error(\"TODO07\")" }; // Add 1 cycle if branch is taken
    case 8: return { "true /*branch taken crosses page boundary*/", "cycles += 1;\n            throw std::runtime_error(\"TODO08\")" }; // Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1)
    case 9: return { "state.isNativeMode()", "cycles += 1" }; // Add 1 cycle for 65816 native mode (e=0)
    case 10: return { "state.is16Bit(State::x)", "cycles += 1" }; // Add 1 cycle if x=0 (16-bit index registers)
    case 20: return { "", "throw NotYetImplementedException(\"TODO20\")" }; // Needs specialization in address mode
    case 21: return { "state.is16Bit(State::m)", "cycles -= 2" }; // Removed 2 cycles for the special case of Accumulator
    default: return {};
    }
}

struct OperatorArgs
{
    OperatorArgs()
        : hasOperand(false)
    {
        cycleRemarks = { 1, 5, 7, 8, 9, 10, 13, 14, 15, 16 };
    }
    std::set<int> cycleRemarks;
    bool hasOperand;
    std::string comment;
};

struct AddressModeClassArgs
{
    AddressModeClassArgs()
        : instructionSize(0)
        , registerTemplate(false)

    {
        cycleRemarks = { 2, 3, 21 };
    }
    std::set<int> cycleRemarks;
    int instructionSize;
    std::string comment;
    bool registerTemplate;
};

bool hasCycleModification(const std::set<int>& remarks)
{
    for (int remark : remarks)
    {
        if (!getCycleModification(remark).condition.empty())
        {
            return true;
        }
    }
    return false;
}

void addCycleModifications(std::ostream& output, const std::set<int>& remarks)
{
    for (int remark : remarks)
    {
        CycleModification cycleModification = getCycleModification(remark);
        if (cycleModification.condition.empty())
        {
            if (!cycleModification.modification.empty())
            {
                output << "        " << cycleModification.modification << ";" << std::endl;
            }
        }
        else
        {
            output << "        if (" << cycleModification.condition << ") {" << std::endl;
            if (!cycleModification.modification.empty())
            {
                output << "            " << cycleModification.modification << ";" << std::endl;
            }
            output << "        }" << std::endl;
        }
    }
}

void generateOpcode(std::ostream& output, Instruction& instruction, const Opcode& opcode, bool is16Bit)
{
    int operandSize = stoi(instruction.size) - 1;

    if (!instruction.comment.empty())
    {
        output << "// " << instruction.comment << std::endl;
    }

    output << "// " << instruction.name << std::endl
        << "// " << instruction.addressMode << " (" << instruction.size << "-Byte";
    if (!instruction.sizeRemark.empty())
    {
        output << " [" << instruction.sizeRemark << "]";
    }
    output << ")" << std::endl;

    int sizeRemark = 0;

    std::string addressModeClass = instruction.addressModeClass;
    if (instruction.extraCycleForPageBoundary && addressModeClass == "AbsoluteIndexed")
    {
        const bool hasRemark = instruction.cyclesRemarks.find(20) != instruction.cyclesRemarks.end();
        if (hasRemark)
        {
            instruction.cyclesRemarks.erase(20);
        }
        else
        {
            addressModeClass += "_ExtraCycle";
        }
    }

    std::string operatorName = instruction.mnemonic;

    if (operatorName == "BIT")
    {
        const bool isImmediate = addressModeClass == "Immediate";
        operatorName = operatorName + "<" + (isImmediate ? "true" : "false") + ">";
    }
    else if (operatorName == "JMP" || operatorName == "JSR")
    {
        if (addressModeClass == "AbsoluteLong" || addressModeClass == "AbsoluteIndirectLong")
        {
            operatorName[2] = 'L';
        }
        if (addressModeClass == "Absolute" || addressModeClass == "AbsoluteLong")
        {
            addressModeClass += "_ControlFlow";
        }
    }
    else if (operatorName == "TXA" || operatorName == "TYA")
    {
        operatorName = std::string("T_A<State::IndexRegister::") + operatorName[1] + ">";
    }
    else if (operatorName == "TXY" || operatorName == "TYX")
    {
        operatorName = std::string("T__<State::IndexRegister::") + operatorName[1] + ", State::IndexRegister::" + operatorName[2] + ">";
    }
    else
    {
        const std::string prefix = operatorName.substr(0, 2);
        const char suffix = operatorName[2];

        if (prefix == "CL" || prefix == "SE" && suffix != 'P')
        {
            const bool isSet = prefix == "SE";
            operatorName = std::string("SE_<State::Flag::") + char(std::tolower(suffix)) + ", " + (isSet ? "true" : "false") + ">";
        }
        else if (prefix == "PE" && (suffix == 'A' || suffix == 'I'))
        {
            addressModeClass += "_ControlFlow";
            operatorName = prefix + "_<'" + operatorName[2] + "'>";
        }
        else if ((prefix == "CP" || prefix == "DE" || prefix == "IN" || prefix == "LD" || prefix == "PH" || prefix == "PL" || prefix == "ST" || prefix == "TA") && (suffix == 'X' || suffix == 'Y'))
        {
            operatorName = prefix + "_<State::IndexRegister::" + operatorName[2] + ">";
        }
    }

    if (is16Bit)
    {
        addressModeClass += "16Bit";
    }

    if (!instruction.sizeRemark.empty())
    {
        sizeRemark = stoi(instruction.sizeRemark);
        output << "// " << getRemark(sizeRemark) << std::endl;
    }

    std::string classname = instruction.classname + (is16Bit ? "_16Bit" : "");

    output << "class " << classname
        << " : public AddressMode::" << addressModeClass << "<Operator::" << operatorName;
    if (!instruction.addressModeClassArg.empty())
    {
        output << ", " << instruction.addressModeClassArg;
    }
    output << ">" << std::endl
        << "{" << std::endl
        << "    using " << addressModeClass << "::" << addressModeClass << ";" << std::endl << std::endl
        << "    // " << opcode.comment << std::endl;
    for (int remark : instruction.cyclesRemarks)
    {
        if (!getRemark(remark).empty())
        {
            output << "    // " << getRemark(remark) << std::endl;
        }
    }
    output << "    int execute() override" << std::endl
        << "    {" << std::endl;
    if (opcode.notYetImplemented)
    {
        output << "        throw NotYetImplementedException(\"" + classname + "\");" << std::endl;
    }
    if (hasCycleModification(instruction.cyclesRemarks))
    {
        output << "        int cycles = " << instruction.cycles << ";" << std::endl;
        addCycleModifications(output, instruction.cyclesRemarks);
        output << "        return cycles";
    }
    else
    {
        addCycleModifications(output, instruction.cyclesRemarks);
        output << "        return " << instruction.cycles;
    }
    output << " + applyOperand();" << std::endl
        << "    }" << std::endl
        << std::endl
        << "    std::string opcodeToString() const override { return \"" << instruction.code << ": " << instruction.name;
    if (is16Bit)
    {
        output << " (16-bit)";
    }
    output << "\"; }" << std::endl
        << "};" << std::endl
        << std::endl;
}

void generateOpcodes(std::vector<Instruction>& instructions)
{
    std::ifstream opcodeTableFile("..\\..\\..\\src\\CodeGenerator\\cpuOpcodeTable.txt");
    if (!opcodeTableFile)
    {
        throw std::runtime_error("Cannot find opcode table file");
    }

    typedef std::map<std::string, Opcode> OpcodeMap;
    OpcodeMap opcodeMap;
    std::string line;

    std::cout << "Not yet implemented: ";
    while (std::getline(opcodeTableFile, line))
    {
        std::istringstream stream(line);
        std::string opcode;
        std::getline(stream, opcode, ':');
        std::string comment;
        std::getline(stream, comment, ':');
        std::string flags;
        std::getline(stream, flags);
        const bool notYetImplemented = !flags.empty();
        if (notYetImplemented)
        {
            std::cout << opcode << " ";
        }
        opcodeMap[opcode] = { comment, notYetImplemented};
    }
    std::cout << std::endl;

    std::ofstream output("..\\..\\..\\src\\WDC65816\\CpuOpcode.h");

    output << "#pragma once" << std::endl
        << std::endl
        << "#include \"Exception.h\"" << std::endl
        << "#include \"CpuState.h\"" << std::endl
        << "#include \"CpuAddressMode.h\"" << std::endl
        << "#include \"CpuOperator.h\"" << std::endl
        << std::endl
        << "namespace CPU {" << std::endl
        << std::endl
        << "namespace Opcode {" << std::endl
        << std::endl
        << "EXCEPTION(NotYetImplementedException, ::NotYetImplementedException)" << std::endl
        << std::endl;

    for (Instruction& instruction : instructions)
    {
        std::string flag = "";
        if (instruction.sizeRemark == "17" || instruction.sizeRemark == "19")
        {
            generateOpcode(output, instruction, opcodeMap[instruction.code], true);
            flag = instruction.sizeRemark == "17" ? "m" : "x";
        }
        generateOpcode(output, instruction, opcodeMap[instruction.code], false);
    }

    output << "}" << std::endl
        << std::endl
        << "}" << std::endl;
}

void generateOpcodeMap(const std::vector<Instruction>& instructions)
{
    std::ofstream output("..\\..\\..\\src\\SnesEmulator\\CPU\\CpuOpcodeMap.cpp");

    output << "#include \"CpuOpcodeMap.h\"" << std::endl
        << std::endl
        << "#include <stdint.h>" << std::endl
        << std::endl
        << "#include \"CpuOpcode.h\"" << std::endl
        << std::endl
        << "namespace CPU {" << std::endl
        << std::endl;

    output << "Instruction* OpcodeMap::getNextInstruction(const State& state) const" << std::endl
        << "{" << std::endl
        << "    Byte opcode = state.readProgramByte();" << std::endl
        << "    if (state.is16Bit(State::m) && instructions16BitM[opcode]) {" << std::endl
        << "        return instructions16BitM[opcode].get();" << std::endl
        << "    } else if (state.is16Bit(State::x) && instructions16BitX[opcode]) {" << std::endl
        << "        return instructions16BitX[opcode].get();" << std::endl
        << "    } else {" << std::endl
        << "        return instructions[opcode].get();" << std::endl
        << "    }" << std::endl
        << "}" << std::endl << std::endl;


    output << "OpcodeMap::OpcodeMap(State& state)" << std::endl
        << "{" << std::endl;
    for (const Instruction& instruction : instructions)
    {
        output << "    instructions[0x" << instruction.code << "] = std::make_unique<Opcode::" << instruction.classname << ">(state);" << std::endl;
        if (instruction.sizeRemark == "17")
        {
            output << "    instructions16BitM[0x" << instruction.code << "] = std::make_unique<Opcode::" << instruction.classname << "_16Bit>(state);" << std::endl;
        }
        else if (instruction.sizeRemark == "19")
        {
            output << "    instructions16BitX[0x" << instruction.code << "] = std::make_unique<Opcode::" << instruction.classname << "_16Bit>(state);" << std::endl;
        }
    }
    output << "}" << std::endl
        << std::endl
        << "}";
}

void generateAddressMode(std::ofstream& output, const std::string& name, const AddressModeClassArgs& args, bool is16Bit = false)
{
    output << "// " << args.comment << std::endl << "template <typename Operator";
    if (args.registerTemplate)
    {
        output << ", typename Register";
    }
    output << ">" << std::endl;

    output << "class " << name << " : public ";

    int actualSize = args.instructionSize + (is16Bit ? 1 : 0);

    std::ostringstream superclassStream;
    superclassStream << "Instruction" << actualSize << "Byte";

    output << superclassStream.str() << std::endl << "{" << std::endl;

    output << "    using " << superclassStream.str() << "::" << superclassStream.str() << std::endl;

    for (int cycleRemark : args.cycleRemarks)
    {
        output << "    // " << getRemark(cycleRemark) << std::endl;
    }

    output << "    int invokeOperator(State& state";
    if (actualSize >= 2)
    {
        output << ", Byte lowByte";
        if (actualSize >= 3)
        {
            output << ", Byte highByte";
            if (actualSize >= 4)
            {
                output << ", Byte bankByte";
            }
        }
    }
    output << ") override" << std::endl
        << "    {" << std::endl
        << "        throw std::runtime_error(\"" + name + " is not implemented\");" << std::endl;
    if (hasCycleModification(args.cycleRemarks))
    {
        output << "        int cycles = 0;" << std::endl;
        addCycleModifications(output, args.cycleRemarks);
    }

    if (name != "Implied")
    {
        output << "        Byte* data = nullptr;" << std::endl;
    }
    output << "        return ";
    if (hasCycleModification(args.cycleRemarks))
    {
        output << "cycles + ";
    }
    output << "Operator::invoke(state";
    if (name != "Implied")
    {
        output << ", data";
    }
    output << ");" << std::endl
        << "    }" << std::endl
        << std::endl;

    output << "    std::string toString(const State& state) const override" << std::endl
        << "    {" << std::endl
        << "        return Operator::toString()";
    if (actualSize > 1)
    {
        output << " + \" $\" + " << "operandToString(state)";
    }
    output << " + \" TODO\";" << std::endl
        << "    }" << std::endl
        << "};" << std::endl
        << std::endl;
}

typedef std::map<std::string, AddressModeClassArgs> AddressModeClassMap;
void generateAddressModes(const AddressModeClassMap& addressModeClassMap)
{
    std::ofstream output("..\\..\\..\\src\\WDC65816\\CpuAddressMode.h");

    output << "#pragma once" << std::endl
        << std::endl
        << "#include <stdint.h>" << std::endl
        << std::endl
        << "#include \"CpuState.h\"" << std::endl
        << "#include \"..\\Instruction.h\"" << std::endl
        << std::endl
        << "namespace CPU {" << std::endl
        << std::endl
        << "typedef InstructionBase<State> Instruction1Byte;" << std::endl
        << "typedef InstructionBase<State, Byte> Instruction2Byte;" << std::endl
        << "typedef InstructionBase<State, Byte, Byte> Instruction3Byte;" << std::endl
        << "typedef InstructionBase<State, Byte, Byte, Byte> Instruction4Byte;" << std::endl
        << std::endl
        << std::endl
        << "namespace AddressMode {" << std::endl
        << std::endl;

    for (const AddressModeClassMap::value_type& kvp : addressModeClassMap)
    {
        generateAddressMode(output, kvp.first, kvp.second);
        if (kvp.first == "Immediate")
        {
            generateAddressMode(output, kvp.first + "16Bit", kvp.second, true);
        }
    }

    output << "}" << std::endl;
}

typedef std::map<std::string, OperatorArgs> OperatorMap;
void generateOperators(const OperatorMap& operatorMap)
{
    std::ofstream output("..\\..\\..\\src\\SnesEmulator\\CPU\\CpuOperator.h");

    output << "#pragma once" << std::endl
        << std::endl
        << "#include \"State.h\"" << std::endl
        << std::endl
        << "namespace Operator {" << std::endl
        << std::endl;

    for (const OperatorMap::value_type& kvp : operatorMap)
    {

        output << "// " << kvp.second.comment << std::endl;

        output << "class " << kvp.first << std::endl
            << "{" << std::endl
            << "public:" << std::endl;

        for (int cycleRemark : kvp.second.cycleRemarks)
        {
            output << "    // " << getRemark(cycleRemark) << std::endl;
        }

        output << "    static int invoke(State& state";
        if (kvp.second.hasOperand)
        {
            output << ", Byte* data";
        }
        output << ")" << std::endl
            << "    {" << std::endl
            << "        throw std::runtime_error(\"" + kvp.first + " is not implemented\");" << std::endl;
        if (hasCycleModification(kvp.second.cycleRemarks))
        {
            output << "        int cycles = 0;" << std::endl;
            addCycleModifications(output, kvp.second.cycleRemarks);
        }

        output << "        return ";
        if (hasCycleModification(kvp.second.cycleRemarks))
        {
            output << "cycles";
        }
        else
        {
            output << "0";
        }
        output << ";" << std::endl;

        output << "    }" << std::endl
            << std::endl
            << "    static std::string toString() { return \"" << kvp.first << "\"; }" << std::endl
            << "};" << std::endl
            << std::endl;
    }
    output << "}" << std::endl;
}

}

void generateCpu()
{
    std::ifstream instructionsFile("..\\..\\..\\src\\CodeGenerator\\cpuInstructions.txt");

    if (!instructionsFile)
    {
        throw std::runtime_error("Cannot find instruction definitions");
    }

    std::vector<std::vector<std::string>> lines;

    std::string line;
    while (std::getline(instructionsFile, line))
    {

        std::istringstream stream(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(stream, token, '\t'))
        {
            tokens.push_back(token);
        }

        lines.push_back(tokens);
    }

    std::vector<Instruction> instructions;
    std::string comment;

    typedef std::map<std::string, std::vector<std::string>> AddressModeMap;
    AddressModeMap addressModeMap;

    AddressModeClassMap addressModeClassMap;

    OperatorMap operatorMap;

    for (std::vector<std::string> line : lines)
    {
        if (line.size() == 1)
        {
            std::cout << line[0] << std::endl;
            comment = line[0];
        }
        else if (line.size() == 5)
        {
            for (int i = 0; i < 5; ++i)
            {
                std::cout << line[i] << '\t';
            }
            std::cout << std::endl;

            std::string name = line[0];

            std::string mnemonic = name.substr(0, 3);

            std::string addressModeCode = name.substr(3);

            std::string opcode = line[1];
            if (opcode.size() == 1)
            {
                opcode = "0" + opcode;
            }

            std::string classname = mnemonic + "_" + opcode;

            std::string addressMode = line[2];

            std::string sizeToken = line[3];
            std::string size = sizeToken.substr(0, 1);

            std::string sizeRemark = sizeToken.substr(1);

            std::string addressModeClass = addressMode;
            addressModeClass.erase(std::remove(addressModeClass.begin(), addressModeClass.end(), ' '), addressModeClass.end());
            addressModeClass.erase(std::remove(addressModeClass.begin(), addressModeClass.end(), ','), addressModeClass.end());
            addressModeClass.erase(std::remove(addressModeClass.begin(), addressModeClass.end(), '('), addressModeClass.end());
            addressModeClass.erase(std::remove(addressModeClass.begin(), addressModeClass.end(), ')'), addressModeClass.end());
            addressModeClass.erase(std::remove(addressModeClass.begin(), addressModeClass.end(), '/'), addressModeClass.end());

            std::string addressModeComment = addressMode;

            int instructionSize = stoi(size);

            if (sizeRemark == "17" || sizeRemark == "19")
            {
                addressModeComment += "\n// " + getRemark(stoi(sizeRemark));
            }

            std::string cyclesToken = line[4];
            std::string cycles = cyclesToken.substr(0, 1);

            std::string cyclesRemark = cyclesToken.substr(1);

            std::set<int> cyclesRemarks;
            OperatorArgs& operatorArgs = operatorMap[mnemonic];
            std::set<int> operatorIntersection;

            std::string addressModeClassSubstr = addressModeClass.substr(0, addressModeClass.size() - 1);
            std::string addressModeClassArg;
            bool registerTemplate = false;
            if (addressModeClassSubstr == "AbsoluteIndexed" || addressModeClassSubstr == "DirectPageIndexed")
            {
                addressModeClassArg = "State::IndexRegister::" + addressModeClass.substr(addressModeClass.size() - 1, 1);
                registerTemplate = true;
                addressModeClass = addressModeClassSubstr;
            }
            AddressModeClassArgs& addressModeClassArgs = addressModeClassMap[addressModeClass];
            std::set<int> addressModeIntersection;

            bool extraCycleForPageBoundary = false;

            if (!cyclesRemark.empty())
            {
                std::istringstream stream(cyclesRemark);
                std::string token;
                std::cout << "Parsing cycles remarks: " << cyclesRemark << std::endl;
                while (std::getline(stream, token, ','))
                {
                    int cycleRemark = stoi(token);
                    cyclesRemarks.insert(cycleRemark);
                    if (cycleRemark == 3)
                    {
                        extraCycleForPageBoundary = true;
                    }
                }
                for (int cycleRemark : cyclesRemarks)
                {
                    if (operatorArgs.cycleRemarks.find(cycleRemark) != operatorArgs.cycleRemarks.end())
                    {
                        operatorIntersection.insert(cycleRemark);
                    }
                    if (addressModeClassArgs.cycleRemarks.find(cycleRemark) != addressModeClassArgs.cycleRemarks.end())
                    {
                        addressModeIntersection.insert(cycleRemark);
                    }
                }
            }

            bool hasOperand = true;
            if (addressMode == "Implied")
            {
                hasOperand = false;
            }
            operatorArgs.cycleRemarks = operatorIntersection;
            operatorArgs.hasOperand = hasOperand;
            operatorArgs.comment = comment;

            addressModeClassArgs.cycleRemarks = addressModeIntersection;
            addressModeClassArgs.instructionSize = instructionSize;
            addressModeClassArgs.comment = addressModeComment;
            addressModeClassArgs.registerTemplate = registerTemplate;

            Instruction instruction{ name, mnemonic, comment, opcode, classname, addressMode, addressModeClass, size, sizeRemark, cycles, cyclesRemarks, addressModeClassArg, extraCycleForPageBoundary };
            instruction.validate();
            instructions.push_back(instruction);

            // TMP
            //addressModeMap[addressModeCode].push_back(addressMode + ", " + name + ", code=" + code + ", cycles=" + cycles + ", size=" + size);
            //addressModeMap[addressMode].push_back(name + ", code=" + code + ", cycles=" + cycles + ", size=" + size + ", sizeRemark=" + sizeRemark);
            addressModeMap[mnemonic].push_back(opcode + ": " + name + ", " + addressMode + ", cycles=" + cycles + ", size=" + size);
        }
    }

    for (Instruction& instruction : instructions)
    {
        //std::cout << "Instruction: " << instruction.classname;
        std::set<int> removedRemarks;
        for (const AddressModeClassMap::value_type& kvp : addressModeClassMap)
        {
            if (kvp.first == instruction.addressModeClass)
            {
                for (int remark : kvp.second.cycleRemarks)
                {
                    if (instruction.cyclesRemarks.erase(remark))
                    {
                        removedRemarks.insert(remark);
                        //std::cout << std::endl << remark << " goes to address mode";
                    }
                }
            }
        }
        for (const OperatorMap::value_type& kvp : operatorMap)
        {
            if (kvp.first == instruction.mnemonic)
            {
                for (int remark : kvp.second.cycleRemarks)
                {
                    instruction.cyclesRemarks.erase(remark);
                    //std::cout << std::endl << remark << " goes to operator";
                    if (removedRemarks.find(remark) != removedRemarks.end())
                    {
                        std::cout << "Nope, remark removed twice from " << instruction.classname << ": " << remark << ", " << instruction.mnemonic << ", " << instruction.addressModeClass << std::endl;
                    }
                }
            }
        }
        //std::cout << std::endl;
    }

    generateOpcodes(instructions);
    //generateOpcodeMap(instructions);
    //generateAddressModes(addressModeClassMap);
    //generateOperators(operatorMap);

    int i = 0;
    for (const AddressModeMap::value_type kvp : addressModeMap)
    {
//std::cout << ++i << ": " << kvp.first << std::endl;
        for (std::string info : kvp.second)
        {
//std::cout << "\t\t" << info << std::endl;
        }
        //std::getchar();
    }

}