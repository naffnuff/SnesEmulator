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
    std::vector<int> cyclesRemarks;

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
    case 1: return "1: Add 1 cycle if m = 0 (16 - bit memory / accumulator)";
    case 2: return "2: Add 1 cycle if low byte of Direct Page Register is non - zero";
    case 3: return "3: Add 1 cycle if adding index crosses a page boundary";
    case 4: return "4: Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)";
    case 5: return "5: Add 2 cycles if m = 0 (16 - bit memory / accumulator)";
    case 6: return "6: Subtract 1 cycle if 65C02 and no page boundary crossed";
    case 7: return "7: Add 1 cycle if branch is taken";
    case 8: return "8: Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) ";
    case 9: return "9: Add 1 cycle for 65816 native mode(e = 0)";
    case 10: return "10: Add 1 cycle if x = 0 (16 - bit index registers)";
    case 11: return "11: Add 1 cycle if 65C02";
    case 12: return "12: 6502: Yields incorrect results if low byte of operand is $FF(i.e., operand is $xxFF)";
    case 13: return "13: 7 cycles per byte moved";
    case 14: return "14: Uses 3 cycles to shut the processor down : additional cycles are required by reset to restart it";
    case 15: return "15: Uses 3 cycles to shut the processor down : additional cycles are required by interrupt to restart it";
    case 16: return "16: Byte and cycle counts subject to change in future processors which expand WDM into 2 - byte opcode portions of instructions of varying lengths";
    case 17: return "17: Add 1 byte if m = 0 (16 - bit memory / accumulator)";
    case 18: return "18: Opcode is 1 byte, but program counter value pushed onto stack is incremented by 2 allowing for optional signature byte";
    case 19: return "19: Add 1 byte if x = 0 (16 - bit index registers)";
    default: return "";
    }
}

std::string getCycleModification(int remarkIndex)
{
    switch (remarkIndex) {
    case 1: return " + (state.getFlag(State::m) ? 0 : 1) /* TODO01*/"; // Add 1 cycle if m = 0 (16 - bit memory / accumulator)
    case 2: return " /* TODO02 */"; // Add 1 cycle if low byte of Direct Page Register is non - zero
    case 3: return " /* TODO03 */"; // Add 1 cycle if adding index crosses a page boundary
    case 4: return " /* TODO04 */"; // Add 1 cycle if 65C02 and d = 1 (65C02 in decimal mode)
    case 5: return " + (state.getFlag(State::m) ? 0 : 2) /* TODO05 */"; // Add 2 cycles if m = 0 (16 - bit memory / accumulator)";
    case 6: return " /* TODO06 */"; // Subtract 1 cycle if 65C02 and no page boundary crossed";
    case 7: return " /* TODO07 */"; // Add 1 cycle if branch is taken";
    case 8: return " /* TODO08 */"; // Add 1 cycle if branch taken crosses page boundary on 6502, 65C02, or 65816's 6502 emulation mode (e=1) ";
    case 9: return " + (state.getFlag(State::m) ? 0 : 2) /* TODO09 */"; // Add 1 cycle for 65816 native mode(e = 0)";
    case 10: return " + (state.getFlag(State::x) ? 0 : 1) /* TODO10 */"; // Add 1 cycle if x = 0 (16 - bit index registers)";
    case 11: return " /* TODO11 */"; // Add 1 cycle if 65C02";
    case 12: return " /* TODO12 */"; // 6502: Yields incorrect results if low byte of operand is $FF(i.e., operand is $xxFF)";
    case 13: return " /* TODO13 */"; // 7 cycles per byte moved";
    case 14: return " /* TODO14 */"; // Uses 3 cycles to shut the processor down : additional cycles are required by reset to restart it";
    case 15: return " /* TODO15 */"; // Uses 3 cycles to shut the processor down : additional cycles are required by interrupt to restart it";
    case 16: return " /* TODO16 */"; // Byte and cycle counts subject to change in future processors which expand WDM into 2 - byte opcode portions of instructions of varying lengths";
    default: return " TODO";
    }
}

void generateOpcodes(const std::vector<Instruction>& instructions)
{
    std::ofstream hOutput("..\\..\\..\\src\\SnesEmulator\\Opcode.h");
    std::ofstream cppOutput("..\\..\\..\\src\\SnesEmulator\\Opcode.cpp");

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

    cppOutput << "#include \"Opcode.h\"" << std::endl
        << std::endl
        << "namespace Opcode {" << std::endl
        << std::endl;

    for (const Instruction& instruction : instructions) {
        int valueSize = stoi(instruction.size) - 1;

        if (!instruction.comment.empty()) {
            hOutput << "// " << instruction.comment << std::endl;
            cppOutput << "// " << instruction.comment << std::endl;
        }

        hOutput << "// " << instruction.name << std::endl
            << "// " << instruction.addressMode << std::endl;
        cppOutput << "// " << instruction.name << std::endl
            << "// " << instruction.addressMode << std::endl;

        int sizeRemark = 0;

        std::string addressModeClass = instruction.addressModeClass;
        addressModeClass += "<Operator::" + instruction.mnemonic;

        if (!instruction.sizeRemark.empty()) {
            sizeRemark = stoi(instruction.sizeRemark);
            hOutput << "// " << getRemark(sizeRemark) << std::endl;
            cppOutput << "// " << getRemark(sizeRemark) << std::endl;

            if (sizeRemark == 17) {
                addressModeClass += ", State::m";
                valueSize = 17;
            } else if (sizeRemark == 19) {
                addressModeClass += ", State::x";
                valueSize = 19;
            }
        }

        addressModeClass += ">";

        hOutput << "class " << instruction.classname << " : public AddressMode::" << addressModeClass << std::endl
            << "{" << std::endl
            << "    using " << instruction.addressModeClass << "::" << instruction.addressModeClass << ";" << std::endl
            << "    int calculateCycles(const State& state) const override;" << std::endl
            << "};" << std::endl
            << std::endl;

        cppOutput << "int " << instruction.classname << "::calculateCycles(const State& state) const" << std::endl
            << "{" << std::endl;

        for (int remark : instruction.cyclesRemarks) {
            cppOutput << "    // " << getRemark(remark) << std::endl;
        }

        cppOutput << "    return " << instruction.cycles;

        for (int cycleRemark : instruction.cyclesRemarks) {
            cppOutput << getCycleModification(cycleRemark);
        }

        cppOutput << ";" << std::endl
            << "}" << std::endl
            << std::endl;
    }

    hOutput << "}" << std::endl;
    cppOutput << "}" << std::endl;
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
        output << "    instructions[0x" << instruction.code << "] = std::make_unique<Opcode::" << instruction.classname << ">(\""
            << instruction.name << "\", \"" << instruction.comment << "\", \"" << instruction.addressMode << "\");"
            << std::endl;
    }
    output << "}" << std::endl;
}

typedef std::map<std::string, std::pair<int, std::string>> AddressModeClassMap;
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

        output << "// " << kvp.second.second << std::endl << "template <typename Operator";

        if (kvp.second.first == 999) {
            output << ", State::Flag Flag";
        }

        output << ">" << std::endl;
        output << "class " << kvp.first << " : public ";
        if (kvp.second.first > 4) {
            output << "InstructionFlagSize<Flag>";
        } else {
            output << "Instruction" << kvp.second.first << "Byte";
        }
        output << std::endl << "{" << std::endl
            << "    using " << kvp.first << "::" << kvp.first << ";" << std::endl
            << "    int ";

        std::stringstream ss;
        ss << "apply(State& state";
        
        if (kvp.second.first == 999) {
            ss << ", uint16_t value";
        } else if (kvp.second.first > 1) {
            ss << ", uint" << (kvp.second.first == 4 ? 32 : (kvp.second.first - 1) * 8) << "_t value";
        }
        ss << ") const";

        output << ss.str() << " override;" << std::endl
            << "};" << std::endl
            << std::endl;

        output << "template <typename Operator";

        if (kvp.second.first == 999) {
            output << ", State::Flag Flag";
        }

        output << ">" << std::endl;

        output << "int " << kvp.first << "<Operator";
        if (kvp.second.first == 999) {
            output << ", Flag";
        }
        output << ">::" << ss.str() << std::endl
            << "{" << std::endl
            << "    int data = 0;" << std::endl
            << "    return Operator::operate(state, &data);" << std::endl
            << "}" << std::endl
            << std::endl;
    }

    output << "}" << std::endl;
}

typedef std::map<std::string, std::string> MnemonicMap;
void generateOperators(const MnemonicMap& mnemonicMap)
{
    std::ofstream hOutput("..\\..\\..\\src\\SnesEmulator\\Operator.h");
    std::ofstream cppOutput("..\\..\\..\\src\\SnesEmulator\\Operator.cpp");

    hOutput << "#pragma once" << std::endl
        << std::endl
        << "#include \"State.h\"" << std::endl
        << std::endl
        << "namespace Operator {" << std::endl
        << std::endl;

    cppOutput << "#include \"Operator.h\"" << std::endl
        << std::endl
        << "namespace Operator {" << std::endl
        << std::endl;

    for (const MnemonicMap::value_type& kvp : mnemonicMap) {

        hOutput << "// " << kvp.second << std::endl;
        cppOutput << "// " << kvp.second << std::endl;

        hOutput << "class " << kvp.first << std::endl
            << "{" << std::endl
            << "public:" << std::endl
            << "    static int operate(State& state, int* address);" << std::endl
            << "};" << std::endl
            << std::endl;

        cppOutput << "int " << kvp.first << "::operate(State& state, int* address)" << std::endl
            << "{" << std::endl
            << "    return 0;" << std::endl
            << "}" << std::endl
            << std::endl;
    }

    hOutput << "}" << std::endl;
    cppOutput << "}" << std::endl;
}

int main(int argc, char* argv[])
{
    try {
        std::ifstream infile("..\\..\\..\\src\\CodeGenerator\\instructions.txt");

        if (!infile) {
            throw std::runtime_error("Cannot find instruction definitions");
        }

        std::vector<std::vector<std::string>> lines;

        std::string line;

        while (std::getline(infile, line)) {

            std::istringstream stream(line);
            std::string token;
            std::vector<std::string> tokens;
            while (std::getline(stream, token, '\t')) {
                tokens.push_back(token);
            }

            lines.push_back(tokens);
        }

        std::vector<std::string> switchCases;

        std::vector<Instruction> instructions;
        std::string comment;

        typedef std::map<std::string, std::vector<std::string>> AddressModeMap;
        AddressModeMap addressModeMap;

        AddressModeClassMap addressModeClassMap;

        MnemonicMap mnemonicMap;

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

                mnemonicMap[mnemonic] = comment;

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

                int valueSize = stoi(size);

                if (sizeRemark == "17" || sizeRemark == "19") {
                    addressModeClass += "FlagSize";
                    valueSize = 999;
                    addressModeComment += "\n// " + getRemark(stoi(sizeRemark));
                }

                addressModeClassMap[addressModeClass] = std::pair<int, std::string>(valueSize, addressModeComment);

                std::string cyclesToken = line[4];
                std::string cycles = cyclesToken.substr(0, 1);

                std::string cyclesRemark = cyclesToken.substr(1);

                std::vector<int> cyclesRemarks;

                if (!cyclesRemark.empty()) {
                    std::istringstream stream(cyclesRemark);
                    std::string token;
                    std::cout << "Parsing cycles remarks: " << cyclesRemark << std::endl;
                    while (std::getline(stream, token, ',')) {
                        cyclesRemarks.push_back(stoi(token));
                    }
                }

                Instruction instruction { name, mnemonic, comment, code, classname, addressMode, addressModeClass, size, sizeRemark, cycles, cyclesRemarks };
                instruction.validate();
                instructions.push_back(instruction);

                // TMP
                //addressModeMap[addressModeCode].push_back(addressMode + ", " + name + ", code=" + code + ", cycles=" + cycles + ", size=" + size);
                //addressModeMap[addressMode].push_back(name + ", code=" + code + ", cycles=" + cycles + ", size=" + size + ", sizeRemark=" + sizeRemark);
                addressModeMap[mnemonic].push_back(code + ": " + name + ", " + addressMode + ", cycles=" + cycles + ", size=" + size);
            }
        }

        generateOpcodes(instructions);
        generateOpcodeMap(instructions);
        generateAddressModes(addressModeClassMap);
        generateOperators(mnemonicMap);

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