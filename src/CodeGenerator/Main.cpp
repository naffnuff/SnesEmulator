#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>

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

        if (sizeRemark != "" && sizeRemark != "16" && sizeRemark != "17" && sizeRemark != "18" && sizeRemark != "19") {
            throw std::runtime_error("Instruction " + name + ": remark is invalid: " + sizeRemark);
        }

        if (cycles != "0" && cycles != "1" && cycles != "2" && cycles != "3" && cycles != "4" && cycles != "5" && cycles != "6" && cycles != "7" && cycles != "8") {
            throw std::runtime_error("Instruction " + name + ": cycles out of range: " + cycles);
        }
    }
};

std::string getRemark(int remarkIndex)
{
    switch (remarkIndex) {
    case 1: return "1: Add 1 cycle if m=0 (16-bit memory/accumulator)";
    case 2: return "2: Add 1 cycle if low byte of Direct Page Register is non-zero";
    case 3: return "3: Add 1 cycle if adding index crosses a page boundary";
    case 5: return "5: Add 2 cycles if m=0 (16-bit memory/accumulator)";
    case 7: return "7: Add 1 cycle if branch is taken";
    case 8: return "8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) ";
    case 9: return "9: Add 1 cycle for 65816 native mode (e=0)";
    case 10: return "10: Add 1 cycle if x=0 (16-bit index registers)";
    case 13: return "13: 7 cycles per byte moved";
    case 14: return "14: Uses 3 cycles to shut the processor down; additional cycles are required by reset to restart it";
    case 15: return "15: Uses 3 cycles to shut the processor down; additional cycles are required by interrupt to restart it";
    case 16: return "16: Byte and cycle counts subject to change in future processors which expand WDM into 2-byte opcode portions of instructions of varying lengths";
    case 17: return "17: Add 1 byte if m=0 (16-bit memory/accumulator)";
    case 18: return "18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte";
    case 19: return "19: Add 1 byte if x=0 (16-bit index registers)";
    case 20: return "20: Needs manual removal of cycle calculation";
    default: return "";
    }
}

std::string getCycleModification(int remarkIndex)
{
    switch (remarkIndex) {
    case 1: return "state.is16Bit(State::m) ? 1 : 0"; // Add 1 cycle if m=0 (16-bit memory / accumulator)
    case 2: return "(uint8_t)state.getDirectPage() ? 1 : 0"; // Add 1 cycle if low byte of Direct Page Register is non-zero
    case 3: return "0 /* TODO03 */"; // Add 1 cycle if adding index crosses a page boundary
    case 5: return "state.is16Bit(State::m) ? 2 : 0"; // Add 2 cycles if m=0 (16-bit memory / accumulator)
    case 7: return "0 /* TODO07 */"; // Add 1 cycle if branch is taken
    case 8: return "0 /* TODO08 */"; // Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1)
    case 9: return "state.isNativeMode() ? 1 : 0"; // Add 1 cycle for 65816 native mode (e=0)
    case 10: return "state.is16Bit(State::x) ? 1 : 0"; // Add 1 cycle if x=0 (16-bit index registers)
    case 13: return "0 /* TODO13 */"; // 7 cycles per byte moved
    case 14: return ""; // Uses 3 cycles to shut the processor down; additional cycles are required by reset to restart it
    case 15: return ""; // Uses 3 cycles to shut the processor down; additional cycles are required by interrupt to restart it
    case 20: return "0 /* TODO20 */"; // Needs manual removal of cycle calculation
    default: return "";
    }
}

struct OperatorArgs
{
    OperatorArgs()
    {
        cycleRemarks = { 7, 8, 13 };
    }
    std::set<int> cycleRemarks;
    bool hasOperand;
    std::string comment;
};

struct AddressModeClassArgs
{
    AddressModeClassArgs()
    {
        cycleRemarks = { 3 };
    }
    std::set<int> cycleRemarks;
    int instructionSize;
    std::string comment;
};

void generateOpcodes(const std::vector<Instruction>& instructions)
{
    std::ifstream opcodeTableFile("..\\..\\..\\src\\CodeGenerator\\opcodeTable.txt");
    typedef std::map<std::string, std::string> OpcodeMap;
    OpcodeMap opcodeMap;
    std::string line;
    while (std::getline(opcodeTableFile, line)) {
        std::istringstream stream(line);
        std::string opcode;
        std::getline(stream, opcode, ':');
        std::string comment;
        std::getline(stream, comment);
        opcodeMap[opcode] = comment;
    }

    std::ofstream hOutput("..\\..\\..\\src\\SnesEmulator\\Opcode.h");

    hOutput << "#pragma once" << std::endl
        << std::endl
        << "#include <stdint.h>" << std::endl
        << std::endl
        << "#include \"State.h\"" << std::endl
        << "#include \"Instruction.h\"" << std::endl
        << "#include \"AddressMode.h\"" << std::endl
        << "#include \"Operator.h\"" << std::endl
        << std::endl
        << "namespace Opcode {" << std::endl
        << std::endl;

    for (const Instruction& instruction : instructions) {
        int operandSize = stoi(instruction.size) - 1;

        if (!instruction.comment.empty()) {
            hOutput << "// " << instruction.comment << std::endl;
        }

        hOutput << "// " << instruction.name << std::endl
            << "// " << instruction.addressMode << std::endl
            << "// " << instruction.size << "<" << instruction.sizeRemark << ">" << std::endl;

        int sizeRemark = 0;

        std::string addressModeClass = instruction.addressModeClass;
        addressModeClass += "<Operator::" + instruction.mnemonic;

        if (!instruction.sizeRemark.empty()) {
            sizeRemark = stoi(instruction.sizeRemark);
            hOutput << "// " << getRemark(sizeRemark) << std::endl;

            if (sizeRemark == 17) {
                addressModeClass += ", State::m";
                operandSize = 17;
            } else if (sizeRemark == 19) {
                addressModeClass += ", State::x";
                operandSize = 19;
            }
        }

        addressModeClass += ">";

        hOutput << "class " << instruction.classname << " : public AddressMode::" << addressModeClass << std::endl
            << "{" << std::endl
            << "    // " << opcodeMap[instruction.code] << std::endl;
        for (int remark : instruction.cyclesRemarks) {
            if (!getRemark(remark).empty()) {
                hOutput << "    // " << getRemark(remark) << std::endl;
            }
        }
        hOutput << "    int calculateCycles(const State& state) const override" << std::endl
            << "    {" << std::endl;
        hOutput << "        int cycles = " << instruction.cycles << ";" << std::endl;
        for (int remark : instruction.cyclesRemarks) {
            if (!getCycleModification(remark).empty()) {
                hOutput << "        cycles += " << getCycleModification(remark) << ";" << std::endl;
            }
        }
        hOutput << "        return cycles;" << std::endl
            << "    }" << std::endl
            << std::endl
            << "    std::string opcodeToString() const override { return \"" << instruction.code << ": " << instruction.name << "\"; }" << std::endl
            << "};" << std::endl
            << std::endl;
    }

    hOutput << "}" << std::endl;
}

void generateOpcodeMap(const std::vector<Instruction>& instructions)
{
    std::ofstream output("..\\..\\..\\src\\SnesEmulator\\OpcodeMap.cpp");

    output << "#include \"OpcodeMap.h\"" << std::endl
        << std::endl
        << "#include <stdint.h>" << std::endl
        << std::endl
        << "#include \"Opcode.h\"" << std::endl
        << "#include \"State.h\"" << std::endl
        << std::endl;

    output << "Instruction* OpcodeMap::getInstruction(uint8_t code) const" << std::endl
        << "{" << std::endl
        << "    return instructions[code].get();" << std::endl
        << "}" << std::endl << std::endl;


    output << "OpcodeMap::OpcodeMap()" << std::endl
        << "{" << std::endl;
    for (const Instruction& instruction : instructions) {
        output << "    instructions[0x" << instruction.code << "] = std::make_unique<Opcode::" << instruction.classname << ">();" << std::endl;
    }
    output << "}" << std::endl;
}

typedef std::map<std::string, AddressModeClassArgs> AddressModeClassMap;
void generateAddressModes(const AddressModeClassMap& addressModeClassMap)
{
    std::ofstream output("..\\..\\..\\src\\SnesEmulator\\AddressMode.h");

    output << "#pragma once" << std::endl
        << std::endl
        << "#include <stdint.h>" << std::endl
        << std::endl
        << "#include \"State.h\"" << std::endl
        << "#include \"Instruction.h\"" << std::endl
        << std::endl
        << "namespace AddressMode {" << std::endl
        << std::endl;

    for (const AddressModeClassMap::value_type& kvp : addressModeClassMap) {

        output << "// " << kvp.second.comment << std::endl << "template <typename Operator";

        if (kvp.second.instructionSize == -1) {
            output << ", State::Flag Flag";
        }

        output << ">" << std::endl;
        output << "class " << kvp.first << " : public ";

        std::ostringstream superclassStream;
        if (kvp.second.instructionSize == -1) {
            superclassStream << "InstructionVariableSize<Flag>";
        } else {
            superclassStream << "Instruction" << kvp.second.instructionSize << "Byte";
        }

        output << superclassStream.str() << std::endl << "{" << std::endl
            << "    int ";

        output << "invokeOperator(State& state";
        if (kvp.second.instructionSize == -1) {
            output << ", uint8_t lowByte, uint8_t highByte";
        } else {
            if (kvp.second.instructionSize >= 2) {
                output << ", uint8_t lowByte";
                if (kvp.second.instructionSize >= 3) {
                    output << ", uint8_t highByte";
                    if (kvp.second.instructionSize == 4) {
                        output << ", uint8_t bankByte";
                    }
                }
            }
        }
        output << ") const" << " override" << std::endl
            << "    {" << std::endl
            << "        throw std::runtime_error(\"Not implemented\");" << std::endl
            << "        int cycles = 0;" << std::endl;
        for (int cycleRemark : kvp.second.cycleRemarks) {
            output << "        // " << getRemark(cycleRemark) << std::endl;
            if (!getCycleModification(cycleRemark).empty()) {
                output << "        cycles += " << getCycleModification(cycleRemark) << ";" << std::endl;
            }
        }
        if (kvp.first != "Implied") {
            output << "        uint8_t* data = nullptr;" << std::endl;
        }
        output << "        return cycles + Operator::invoke(state";
        if (kvp.first != "Implied") {
            output << ", data";
        }
        output << ");" << std::endl
            << "    }" << std::endl
            << std::endl
            << "    std::string toString(const State& state) const override" << std::endl
            << "    {" << std::endl
            << "        return Operator::toString()";
        if (kvp.second.instructionSize == -1 || kvp.second.instructionSize > 1) {
            output << " + \" $\" + " << superclassStream.str() << "::operandToString(state)";
        }
        output << " + \" TODO\";" << std::endl
            << "    }" << std::endl
            << "};" << std::endl
            << std::endl;
    }

    output << "}" << std::endl;
}

typedef std::map<std::string, OperatorArgs> OperatorMap;
void generateOperators(const OperatorMap& operatorMap)
{
    std::ofstream hOutput("..\\..\\..\\src\\SnesEmulator\\Operator.h");

    hOutput << "#pragma once" << std::endl
        << std::endl
        << "#include \"State.h\"" << std::endl
        << std::endl
        << "namespace Operator {" << std::endl
        << std::endl;

    for (const OperatorMap::value_type& kvp : operatorMap) {

        hOutput << "// " << kvp.second.comment << std::endl;

        hOutput << "class " << kvp.first << std::endl
            << "{" << std::endl
            << "public:" << std::endl
            << "    static int invoke(State& state";
        if (kvp.second.hasOperand) {
            hOutput << ", uint8_t* data";
        }
        hOutput << ")" << std::endl
            << "    {" << std::endl
            << "        throw std::runtime_error(\"Not implemented\");" << std::endl
            << "        int cycles = 0;" << std::endl;
        for (int cycleRemark : kvp.second.cycleRemarks) {
            hOutput << "        // " << getRemark(cycleRemark) << std::endl;
            if (!getCycleModification(cycleRemark).empty()) {
                hOutput << "        cycles += " << getCycleModification(cycleRemark) << ";" << std::endl;
            }
        }
        hOutput << "        return cycles;" << std::endl
            << "    }" << std::endl
            << std::endl
            << "    static std::string toString() { return \"" << kvp.first << "\"; }" << std::endl
            << "};" << std::endl
            << std::endl;
    }
    hOutput << "}" << std::endl;
}

int main(int argc, char* argv[])
{
    try {
        std::ifstream instructionsFile("..\\..\\..\\src\\CodeGenerator\\instructions.txt");

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
        std::string comment;

        typedef std::map<std::string, std::vector<std::string>> AddressModeMap;
        AddressModeMap addressModeMap;

        AddressModeClassMap addressModeClassMap;

        OperatorMap operatorMap;

        for (std::vector<std::string> line : lines) {
            if (line.size() == 1) {
                std::cout << line[0] << std::endl;
                comment = line[0];
            } else if (line.size() == 5) {
                for (int i = 0; i < 5; ++i)
                {
                    std::cout << line[i] << '\t';
                }
                std::cout << std::endl;

                std::string name = line[0];

                std::string mnemonic = name.substr(0, 3);

                std::string addressModeCode = name.substr(3);

                std::string code = line[1];
                if (code.size() == 1) {
                    code = "0" + code;
                }

                std::string classname = mnemonic + "_" + code;

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

                if (sizeRemark == "17" || sizeRemark == "19") {
                    addressModeClass += "VariableSize";
                    instructionSize = -1;
                    addressModeComment += "\n// " + getRemark(stoi(sizeRemark));
                }

                std::string cyclesToken = line[4];
                std::string cycles = cyclesToken.substr(0, 1);

                std::string cyclesRemark = cyclesToken.substr(1);

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
                if (addressMode == "Implied") {
                    hasOperand = false;
                }
                operatorArgs.cycleRemarks = operatorIntersection;
                operatorArgs.hasOperand = hasOperand;
                operatorArgs.comment = comment;

                addressModeClassArgs.cycleRemarks = addressModeIntersection;
                addressModeClassArgs.instructionSize = instructionSize;
                addressModeClassArgs.comment = addressModeComment;

                Instruction instruction { name, mnemonic, comment, code, classname, addressMode, addressModeClass, size, sizeRemark, cycles, cyclesRemarks };
                instruction.validate();
                instructions.push_back(instruction);

                // TMP
                //addressModeMap[addressModeCode].push_back(addressMode + ", " + name + ", code=" + code + ", cycles=" + cycles + ", size=" + size);
                //addressModeMap[addressMode].push_back(name + ", code=" + code + ", cycles=" + cycles + ", size=" + size + ", sizeRemark=" + sizeRemark);
                addressModeMap[mnemonic].push_back(code + ": " + name + ", " + addressMode + ", cycles=" + cycles + ", size=" + size);
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

    } catch (const std::exception& e) {

        std::cout << "Caught std::exception: " << e.what() << std::endl;
        std::cout << "Failure";
        std::getchar();
        return 1;
    }

    std::cout << "Success";
    std::getchar();
    return 0;

}