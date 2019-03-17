#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>

namespace {

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
    std::string cycles;
    std::set<int> cyclesRemarks;
    std::string addressModeClassArg;

    void validate()
    {
        if (name.empty()) {
            throw std::runtime_error("Instruction name is empty");
        }

        if (mnemonic.empty()) {
            throw std::runtime_error("Instruction " + name + ": shortname is empty");
        }

        if (classname.empty()) {
            throw std::runtime_error("Instruction " + name + ": handlername is empty");
        }

        if (code.size() != 2) {
            throw std::runtime_error("Instruction " + name + ": code out of range: " + code);
        }

        if (size != "1" && size != "2" && size != "3" && size != "4") {
            throw std::runtime_error("Instruction " + name + ": size out of range: " + size);
        }

        if (cycles != "0" && cycles != "1" && cycles != "2" && cycles != "3" && cycles != "4" && cycles != "5" && cycles != "6" && cycles != "7" && cycles != "8") {
            throw std::runtime_error("Instruction " + name + ": cycles out of range: " + cycles);
        }
    }
};

struct AddressMode
{
    std::string name;
    std::string templateArg;
};

static int miau = 0;

AddressMode getAddressMode(const std::string& code)
{
    AddressMode mode;
    if (code == "(X), (Y)") {
        mode.name = "X Indirect Y Indirect";
    } else if (code == "A, #i") {
        mode.name = "Accumulator Immediate";
    } else if (code == "A, (X)") {
        mode.name = "Accumulator X Indirect";
    } else if (code == "A, [d]+Y") {
        mode.name = "Accumulator Direct Indirect Indexed, Y";
    } else if (code == "A, [d+X]") {
        mode.name = "Accumulator Direct Indexed, X Indirect";
    } else if (code == "A, d") {
        mode.name = "Accumulator Direct";
    } else if (code == "A, d+X") {
        mode.name = "Accumulator Direct Indexed, X";
    } else if (code == "A, !a") {
        mode.name = "Accumulator Absolute";
    } else if (code == "A, !a+X") {
        mode.name = "Accumulator Absolute Indexed, X";
    } else if (code == "A, !a+Y") {
        mode.name = "Accumulator Absolute Indexed, Y";
    } else if (code == "dd, ds") {
        mode.name = "Direct Direct";
    } else if (code == "d, #i") {
        mode.name = "Direct Immediate";
    } else if (code == "YA, d") {
        mode.name = "Y Accumulator Direct";
    } else if (code == "C, /m.b") {
        mode.name = "Carry Not Memory Bit";
    } else if (code == "C, m.b") {
        mode.name = "Carry Memory Bit";
    } else if (code == "A") {
        mode.name = "Accumulator";
    } else if (code == "d") {
        mode.name = "Direct";
    } else if (code == "d+X") {
        mode.name = "Direct Indexed, X";
    } else if (code == "!a") {
        mode.name = "Absolute";
    } else if (code.substr(0, 2) == "d.") {
        mode.templateArg = "1 << " + code.substr(2, 1);
        if (code.size() == 3) {
            mode.name = "Direct Bit";
        } else {
            mode.name = "Direct Bit Program Counter Relative";
        }
    } else if (code == "r") {
        mode.name = "Program Counter Relative";
    } else if (code == "") {
        mode.name = "Implied";
    } else if (code == "d+X, r") {
        mode.name = "Direct Indexed, X Program Counter Relative";
    } else if (code == "d, r") {
        mode.name = "Direct Program Counter Relative";
    } else if (code == "X, #i") {
        mode.name = "Index X Immediate";
    } else if (code == "X, d") {
        mode.name = "Index X Direct";
    } else if (code == "X, !a") {
        mode.name = "Index X Absolute";
    } else if (code == "Y, #i") {
        mode.name = "Index Y Immediate";
    } else if (code == "Y, d") {
        mode.name = "Index Y Direct";
    } else if (code == "Y, !a") {
        mode.name = "Index Y Absolute";
    } else if (code == "Y, r") {
        mode.name = "Index Y Program Counter Relative";
    } else if (code == "X") {
        mode.name = "Index X";
    } else if (code == "Y") {
        mode.name = "Index Y";
    } else if (code == "YA, X") {
        mode.name = "Y Accumulator Index X";
    } else if (code == "[!a+X]") {
        mode.name = "Absolute Indexed, X Indirect";
    } else if (code == "(X)+, A") {
        mode.name = "X Indirect Plus Accumulator";
    } else if (code == "(X), A") {
        mode.name = "X Indirect Accumulator";
    } else if (code == "[d]+Y, A") {
        mode.name = "Direct Indirect Indexed, Y Accumulator";
    } else if (code == "[d+X], A") {
        mode.name = "Direct Indexed, X Indirect Accumulator";
    } else if (code == "A, (X)+") {
        mode.name = "Accumulator X Indirect Plus";
    } else if (code == "A, X") {
        mode.name = "Accumulator Index X";
    } else if (code == "A, Y") {
        mode.name = "Accumulator Index Y";
    } else if (code == "SP, X") {
        mode.name = "Stack Pointer Index X";
    } else if (code == "X, A") {
        mode.name = "Index X Accumulator";
    } else if (code == "X, SP") {
        mode.name = "Index X Stack Pointer";
    } else if (code == "X, d+Y") {
        mode.name = "Index X Direct Indexed, Y";
    } else if (code == "Y, A") {
        mode.name = "Index Y Accumulator";
    } else if (code == "Y, d+X") {
        mode.name = "Index Y Direct Indexed, X";
    } else if (code == "d+X, A") {
        mode.name = "Direct Indexed, X Accumulator";
    } else if (code == "d+X, Y") {
        mode.name = "Direct Indexed, X Index Y";
    } else if (code == "d+Y, X") {
        mode.name = "Direct Indexed, Y Index X";
    } else if (code == "d, A") {
        mode.name = "Direct Accumulator";
    } else if (code == "d, X") {
        mode.name = "Direct Index X";
    } else if (code == "d, Y") {
        mode.name = "Direct Index Y";
    } else if (code == "!a+X, A") {
        mode.name = "Absolute Indexed, X Accumulator";
    } else if (code == "!a+Y, A") {
        mode.name = "Absolute Indexed, Y Accumulator";
    } else if (code == "!a, A") {
        mode.name = "Absolute Accumulator";
    } else if (code == "!a, X") {
        mode.name = "Absolute Index X";
    } else if (code == "!a, Y") {
        mode.name = "Absolute Index Y";
    } else if (code == "m.b, C") {
        mode.name = "Memory Bit Carry";
    } else if (code == "d, YA") {
        mode.name = "Direct Y Accumulator";
    } else if (code == "YA") {
        mode.name = "Index Y Accumulator";
    } else if (code == "m.b") {
        mode.name = "Memory Bit";
    } else if (code == "u") {
        mode.name = "U Page";
    } else if (code == "PSW") {
        mode.name = "State Flags";
    } else if (code == "miau") {
        mode.name = "suge";
    } else {
        mode.name = "Table";
        mode.templateArg = code;
    }
    return mode;
}

std::string getRemark(int remarkIndex)
{
    switch (remarkIndex) {
    case 1: return "§1: Add 1 cycle if m=0 (16-bit memory/accumulator)";
    case 2: return "§2: Add 1 cycle if low byte of Direct Page Register is non-zero";
    case 3: return "§3: Add 1 cycle if adding index crosses a page boundary";
    case 5: return "§5: Add 2 cycles if m=0 (16-bit memory/accumulator)";
    case 7: return "§7: Add 1 cycle if branch is taken";
    case 8: return "§8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) ";
    case 9: return "§9: Add 1 cycle for 65816 native mode (e=0)";
    case 10: return "§10: Add 1 cycle if x=0 (16-bit index registers)";
    case 13: return "§13: 7 cycles per byte moved";
    case 14: return "§14: Uses 3 cycles to shut the processor down; additional cycles are required by reset to restart it";
    case 15: return "§15: Uses 3 cycles to shut the processor down; additional cycles are required by interrupt to restart it";
    case 16: return "§16: Byte and cycle counts subject to change in future processors which expand WDM into 2-byte opcode portions of instructions of varying lengths";
    case 17: return "¤17: Add 1 byte if m=0 (16-bit memory/accumulator)";
    case 18: return "¤18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte";
    case 19: return "¤19: Add 1 byte if x=0 (16-bit index registers)";
    case 20: return "§20: TODO manually add exception for 3";
    case 21: return "§21: Remove 2 cycles for the special case of Accumulator";
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
    switch (remarkIndex) {
    case 1: return { "state.is16Bit(State::m)", "cycles += 1" }; // Add 1 cycle if m=0 (16-bit memory / accumulator)
    case 2: return { "(uint8_t)state.getDirectPage()", "cycles += 1" }; // Add 1 cycle if low byte of Direct Page Register is non-zero
    case 3: return { "true /*index added crosses page boundary*/", "cycles += 1;\n            throw std::runtime_error(\"TODO03\")" }; // Add 1 cycle if adding index crosses a page boundary
    case 5: return { "state.is16Bit(State::m)", "cycles += 2" }; // Add 2 cycles if m=0 (16-bit memory / accumulator)
    case 7: return { "true /*branch taken*/", "cycles += 1;\n            throw std::runtime_error(\"TODO07\")" }; // Add 1 cycle if branch is taken
    case 8: return { "true /*branch taken crosses page boundary*/", "cycles += 1;\n            throw std::runtime_error(\"TODO08\")" }; // Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1)
    case 9: return { "state.isNativeMode()", "cycles += 1" }; // Add 1 cycle for 65816 native mode (e=0)
    case 10: return { "state.is16Bit(State::x)", "cycles += 1" }; // Add 1 cycle if x=0 (16-bit index registers)
    case 20: return { "", "throw std::runtime_error(\"TODO20\")" }; // Needs specialization in address mode
    case 21: return { "state.is16Bit(State::m)", "cycles -= 2" }; // Removed 2 cycles for the special case of Accumulator
    default: return {};
    }
}

struct OperatorArgs
{
    OperatorArgs()
        : hasOperand(0)
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
        , bitMaskTemplate(false)
        , indexTemplate(false)
    {
        cycleRemarks = { 2, 3, 21 };
    }
    std::set<int> cycleRemarks;
    int instructionSize;
    std::string comment;
    bool bitMaskTemplate;
    bool indexTemplate;
};

bool hasCycleModification(const std::set<int>& remarks)
{
    for (int remark : remarks) {
        if (!getCycleModification(remark).condition.empty()) {
            return true;
        }
    }
    return false;
}

void addCycleModifications(std::ostream& output, const std::set<int>& remarks)
{
    for (int remark : remarks) {
        CycleModification cycleModification = getCycleModification(remark);
        if (cycleModification.condition.empty()) {
            if (!cycleModification.modification.empty()) {
                output << "        " << cycleModification.modification << ";" << std::endl;
            }
        } else {
            output << "        if (" << cycleModification.condition << ") {" << std::endl;
            if (!cycleModification.modification.empty()) {
                output << "            " << cycleModification.modification << ";" << std::endl;
            }
            output << "        }" << std::endl;
        }
    }
}

void generateOpcode(std::ostream& output, const Instruction& instruction, bool is16Bit)
{
    int operandSize = stoi(instruction.size) - 1;

    output << "// " << instruction.name << std::endl
        << "// " << instruction.comment << std::endl
        << "// " << instruction.addressMode << " (" << instruction.size << "-Byte";
    output << ")" << std::endl;

    int sizeRemark = 0;

    std::string classname = instruction.classname + (is16Bit ? "_16Bit" : "");

    std::string addressModeClass = instruction.addressModeClass;
    if (is16Bit) {
        addressModeClass += "16Bit";
    }

    output << "class " << classname;
    output << " : public AddressMode::" << addressModeClass;
    output << "<Operator::" << instruction.mnemonic;
    if (!instruction.addressModeClassArg.empty()) {
        output << ", " << instruction.addressModeClassArg;
    }
    output << ">" << std::endl
        << "{" << std::endl
        << "    using " << addressModeClass << "::" << addressModeClass << ";" << std::endl << std::endl;
    for (int remark : instruction.cyclesRemarks) {
        if (!getRemark(remark).empty()) {
            output << "    // " << getRemark(remark) << std::endl;
        }
    }
    output << "    int execute() override" << std::endl
        << "    {" << std::endl
        << "        throw std::runtime_error(\"" + classname + " is not implemented\");" << std::endl;
    if (hasCycleModification(instruction.cyclesRemarks)) {
        output << "        int cycles = " << instruction.cycles << ";" << std::endl;
        addCycleModifications(output, instruction.cyclesRemarks);
        output << "        return cycles";
    } else {
        addCycleModifications(output, instruction.cyclesRemarks);
        output << "        return " << instruction.cycles;
    }
    output << " + applyOperand();" << std::endl
        << "    }" << std::endl
        << std::endl
        << "    std::string opcodeToString() const override { return \"" << instruction.code << ": " << instruction.name;
    if (is16Bit) {
        output << " (16-bit)";
    }
    output << "\"; }" << std::endl
        << "};" << std::endl
        << std::endl;
}

void generateOpcodes(const std::vector<Instruction>& instructions)
{
    std::ofstream output("..\\..\\..\\src\\SnesEmulator\\SPC\\SpcOpcode.h");

    output << "#pragma once" << std::endl
        << std::endl
        << "#include <stdint.h>" << std::endl
        << std::endl
        << "#include \"../Instruction.h\"" << std::endl
        << "#include \"SpcState.h\"" << std::endl
        << "#include \"SpcAddressMode.h\"" << std::endl
        << "#include \"SpcOperator.h\"" << std::endl
        << std::endl
        << "namespace SPC {" << std::endl
        << std::endl
        << "namespace Opcode {" << std::endl
        << std::endl;

    for (const Instruction& instruction : instructions) {
        std::string flag = "";
        generateOpcode(output, instruction, false);
    }

    output << "}" << std::endl
        << std::endl
        << "}" << std::endl;
}

void generateOpcodeMap(const std::vector<Instruction>& instructions)
{
    std::ofstream output("..\\..\\..\\src\\SnesEmulator\\SPC\\SpcOpcodeMap.cpp");

    output << "#include \"SpcOpcodeMap.h\"" << std::endl
        << std::endl
        << "#include <stdint.h>" << std::endl
        << std::endl
        << "#include \"SpcState.h\"" << std::endl
        << "#include \"SpcOpcode.h\"" << std::endl
        << std::endl
        << "namespace SPC {" << std::endl
        << std::endl;

    output << "Instruction* OpcodeMap::getNextInstruction(const State& state) const" << std::endl
        << "{" << std::endl
        << "    return instructions[state.readProgramByte()].get();" << std::endl
        << "}" << std::endl << std::endl;


    output << "OpcodeMap::OpcodeMap(State& state)" << std::endl
        << "{" << std::endl;
    for (const Instruction& instruction : instructions) {
        output << "    instructions[0x" << instruction.code << "] = std::make_unique<Opcode::" << instruction.classname << ">(state);" << std::endl;
    }
    output << "}" << std::endl
        << std::endl
        << "}";
}

void generateAddressMode(std::ofstream& output, const std::string& name, const AddressModeClassArgs& args, bool is16Bit = false)
{
    output << "// " << args.comment << std::endl << "template <typename Operator";
    if (args.bitMaskTemplate) {
        output << ", uint8_t bitMask";
    } else if (args.indexTemplate) {
        output << ", uint8_t index";
    }
    output << ">" << std::endl;

    output << "class " << name << " : public ";

    int actualSize = args.instructionSize + (is16Bit ? 1 : 0);

    std::ostringstream superclassStream;
    superclassStream << "Instruction" << actualSize << "Byte";

    output << superclassStream.str() << std::endl << "{" << std::endl;

    output << "    using " << superclassStream.str() << "::" << superclassStream.str() << ";" << std::endl << std::endl;

    for (int cycleRemark : args.cycleRemarks) {
        output << "    // " << getRemark(cycleRemark) << std::endl;
    }

    output << "    int invokeOperator(";
    if (actualSize >= 2) {
        output << "uint8_t lowByte";
        if (actualSize >= 3) {
            output << ", uint8_t highByte";
            if (actualSize >= 4) {
                output << ", uint8_t bankByte";
            }
        }
    }
    output << ") override" << std::endl
        << "    {" << std::endl
        << "        throw std::runtime_error(\"" + name + " is not implemented\");" << std::endl;
    if (hasCycleModification(args.cycleRemarks)) {
        output << "        int cycles = 0;" << std::endl;
        addCycleModifications(output, args.cycleRemarks);
    }

    if (name != "Implied") {
        output << "        uint8_t* data = nullptr;" << std::endl;
    }
    output << "        return ";
    if (hasCycleModification(args.cycleRemarks)) {
        output << "cycles + ";
    }
    output << "Operator::invoke(state";
    if (name != "Implied") {
        output << ", data";
    }
    output << ");" << std::endl
        << "    }" << std::endl
        << std::endl;

    output << "    std::string toString() const override" << std::endl
        << "    {" << std::endl
        << "        return Operator::toString()";
    if (actualSize > 1) {
        output << " + \" $\" + " << "operandToString()";
    }
    output << " + \" TODO\";" << std::endl
        << "    }" << std::endl
        << "};" << std::endl
        << std::endl;
}

typedef std::map<std::string, AddressModeClassArgs> AddressModeClassMap;
void generateAddressModes(const AddressModeClassMap& addressModeClassMap)
{
    std::ofstream output("..\\..\\..\\src\\SnesEmulator\\SPC\\SpcAddressMode.h");

    output << "#pragma once" << std::endl
        << std::endl
        << "#include <stdint.h>" << std::endl
        << std::endl
        << "#include \"../Instruction.h\"" << std::endl
        << "#include \"SpcState.h\"" << std::endl
        << std::endl
        << "namespace SPC {" << std::endl
        << std::endl
        << "typedef InstructionBase<State> Instruction1Byte;" << std::endl
        << "typedef InstructionBase<State, uint8_t> Instruction2Byte;" << std::endl
        << "typedef InstructionBase<State, uint8_t, uint8_t> Instruction3Byte;" << std::endl
        << std::endl
        << "namespace AddressMode {" << std::endl
        << std::endl;

    for (const AddressModeClassMap::value_type& kvp : addressModeClassMap) {
        generateAddressMode(output, kvp.first, kvp.second);
        if (kvp.first == "Immediate") {
            generateAddressMode(output, kvp.first + "16Bit", kvp.second, true);
        }
    }

    output << "}" << std::endl
        << std::endl
        << "}" << std::endl
        << std::endl;
}

typedef std::map<std::string, OperatorArgs> OperatorMap;
void generateOperators(const OperatorMap& operatorMap)
{
    std::ofstream output("..\\..\\..\\src\\SnesEmulator\\SPC\\SpcOperator.h");

    output << "#pragma once" << std::endl
        << std::endl
        << "#include \"SpcState.h\"" << std::endl
        << std::endl
        << "namespace SPC {" << std::endl
        << std::endl
        << "namespace Operator {" << std::endl
        << std::endl;

    for (const OperatorMap::value_type& kvp : operatorMap) {

        output << "// " << kvp.first << kvp.second.comment << std::endl;

        output << "class " << kvp.first << std::endl
            << "{" << std::endl
            << "public:" << std::endl;

        for (int cycleRemark : kvp.second.cycleRemarks) {
            output << "    // " << getRemark(cycleRemark) << std::endl;
        }

        output << "    static int invoke(State& state";
        if (kvp.second.hasOperand) {
            output << ", uint8_t* data";
        }
        output << ")" << std::endl
            << "    {" << std::endl
            << "        throw std::runtime_error(\"" + kvp.first + " is not implemented\");" << std::endl;
        if (hasCycleModification(kvp.second.cycleRemarks)) {
            output << "        int cycles = 0;" << std::endl;
            addCycleModifications(output, kvp.second.cycleRemarks);
        }

        output << "        return ";
        if (hasCycleModification(kvp.second.cycleRemarks)) {
            output << "cycles";
        } else {
            output << "0";
        }
        output << ";" << std::endl;

        output << "    }" << std::endl
            << std::endl
            << "    static std::string toString() { return \"" << kvp.first << "\"; }" << std::endl
            << "};" << std::endl
            << std::endl;
    }
    output << "}" << std::endl
        << std::endl
        << "}" << std::endl;
}

}

void generateSpc()
{
    std::ifstream instructionsFile("..\\..\\..\\src\\CodeGenerator\\spcInstructions.txt");

    if (!instructionsFile) {
        throw std::runtime_error("Cannot find instruction definitions");
    }

    std::vector<std::vector<std::string>> lines;

    std::string line;
    while (std::getline(instructionsFile, line)) {

        std::istringstream stream(line);
        std::string token;
        std::vector<std::string> tokens;
        while (std::getline(stream, token, '\t')) {
            tokens.push_back(token);
        }

        lines.push_back(tokens);
    }

    std::vector<Instruction> instructions;

    typedef std::map<std::string, std::vector<std::string>> AddressModeMap;
    AddressModeMap addressModeMap;

    AddressModeClassMap addressModeClassMap;

    OperatorMap operatorMap;

    std::string previousMnemonic;
    std::string comment;

    for (std::vector<std::string> line : lines) {
        if (line.size() == 7) {
            for (int i = 0; i < 7; ++i) {
                std::cout << line[i] << '\t';
            }
            std::cout << std::endl;

            std::string mnemonic = line[0];

            std::string addressModeCode = line[1];

            std::string name = mnemonic + " " + addressModeCode;

            std::string opcode = line[2];
            if (opcode.size() == 1) {
                opcode = "0" + opcode;
            }

            std::string classname = mnemonic + "_" + opcode;

            AddressMode addressMode = getAddressMode(addressModeCode);

            comment = line[5];

            std::string size = line[3];

            std::string addressModeClass = addressMode.name;
            addressModeClass.erase(std::remove(addressModeClass.begin(), addressModeClass.end(), ' '), addressModeClass.end());
            addressModeClass.erase(std::remove(addressModeClass.begin(), addressModeClass.end(), ','), addressModeClass.end());
            addressModeClass.erase(std::remove(addressModeClass.begin(), addressModeClass.end(), '('), addressModeClass.end());
            addressModeClass.erase(std::remove(addressModeClass.begin(), addressModeClass.end(), ')'), addressModeClass.end());
            addressModeClass.erase(std::remove(addressModeClass.begin(), addressModeClass.end(), '/'), addressModeClass.end());

            std::string addressModeComment = addressMode.name;
            addressModeComment += "\n// " + addressModeCode;

            int instructionSize = stoi(size);

            std::string cycles = "0";

            std::string cyclesRemark = "";

            std::set<int> cyclesRemarks;
            OperatorArgs& operatorArgs = operatorMap[mnemonic];
            std::set<int> operatorIntersection;
            AddressModeClassArgs& addressModeClassArgs = addressModeClassMap[addressModeClass];
            std::set<int> addressModeIntersection;

            if (!cyclesRemark.empty()) {
                std::istringstream stream(cyclesRemark);
                std::string token;
                std::cout << "Parsing cycles remarks: " << cyclesRemark << std::endl;
                while (std::getline(stream, token, ',')) {
                    int cycleRemark = stoi(token);
                    cyclesRemarks.insert(cycleRemark);
                    if (cycleRemark == 5) {
                        //cyclesRemarks.insert(1);
                    }
                }
                for (int cycleRemark : cyclesRemarks) {
                    if (operatorArgs.cycleRemarks.find(cycleRemark) != operatorArgs.cycleRemarks.end()) {
                        operatorIntersection.insert(cycleRemark);
                    }
                    if (addressModeClassArgs.cycleRemarks.find(cycleRemark) != addressModeClassArgs.cycleRemarks.end()) {
                        addressModeIntersection.insert(cycleRemark);
                    }
                }
            }

            bool hasOperand = true;
            if (addressMode.name == "Implied") {
                hasOperand = false;
            }
            operatorArgs.cycleRemarks = operatorIntersection;
            operatorArgs.hasOperand = hasOperand;
            operatorArgs.comment += "\n// " + addressModeCode + ": " + comment;

            if (addressModeClassArgs.instructionSize != 0 && addressModeClassArgs.instructionSize != instructionSize) {
                std::stringstream ss;
                ss << addressMode.name << " has conflicting sizes: size=" << instructionSize << ", previous size=" << addressModeClassArgs.instructionSize;
                throw std::runtime_error(ss.str());
            }

            addressModeClassArgs.cycleRemarks = addressModeIntersection;
            addressModeClassArgs.instructionSize = instructionSize;
            addressModeClassArgs.comment = addressModeComment;
            if (!addressMode.templateArg.empty()) {
                if (addressMode.name == "Table") {
                    addressModeClassArgs.indexTemplate = true;
                } else {
                    addressModeClassArgs.bitMaskTemplate = true;
                }
            }

            Instruction instruction { name, mnemonic, comment, opcode, classname, addressMode.name, addressModeClass, size, cycles, cyclesRemarks, addressMode.templateArg };
            instruction.validate();
            instructions.push_back(instruction);

            // TMP
            //addressModeMap[addressModeCode].push_back(addressMode + ", " + name + ", code=" + code + ", cycles=" + cycles + ", size=" + size);
            //addressModeMap[addressMode].push_back(name + ", code=" + code + ", cycles=" + cycles + ", size=" + size + ", sizeRemark=" + sizeRemark);
            addressModeMap[mnemonic].push_back(opcode + ": " + name + ", " + addressMode.name + ", cycles=" + cycles + ", size=" + size);
        }
    }

    for (Instruction& instruction : instructions) {
        std::set<int> removedRemarks;
        for (const AddressModeClassMap::value_type& kvp : addressModeClassMap) {
            if (kvp.first == instruction.addressModeClass) {
                for (int remark : kvp.second.cycleRemarks) {
                    if (instruction.cyclesRemarks.erase(remark)) {
                        removedRemarks.insert(remark);
                    }
                }
            }
        }
        for (const OperatorMap::value_type& kvp : operatorMap) {
            if (kvp.first == instruction.mnemonic) {
                for (int remark : kvp.second.cycleRemarks) {
                    instruction.cyclesRemarks.erase(remark);
                    if (removedRemarks.find(remark) != removedRemarks.end()) {
                        std::cout << "Nope, remark removed twice from " << instruction.classname << ": " << remark << ", " << instruction.mnemonic << ", " << instruction.addressModeClass << std::endl;
                    }
                }
            }
        }
    }

    generateOpcodes(instructions);
    generateOpcodeMap(instructions);
    generateAddressModes(addressModeClassMap);
    generateOperators(operatorMap);

    int i = 0;
    for (const AddressModeMap::value_type kvp : addressModeMap) {
        //std::cout << ++i << ": " << kvp.first << std::endl;
        for (std::string info : kvp.second) {
            //std::cout << "\t\t" << info << std::endl;
        }
        //std::getchar();
    }

}