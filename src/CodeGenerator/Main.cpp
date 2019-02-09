#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

struct Instruction
{
    std::string name;
    std::string shortname;
    std::string comment;
    std::string code;
    std::string handlername;
    std::string addressMode;
    std::string size;
    std::string sizeRemark;
    std::string cycles;
    std::vector<int> cyclesRemarks;

    void validate()
    {
        if (name.empty()) {
            throw std::runtime_error("Instruction name is empty");
        }

        if (shortname.empty()) {
            throw std::runtime_error("Instruction " + name + ": shortname is empty");
        }

        if (handlername.empty()) {
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

void generateHeader(const std::vector<Instruction>& instructions)
{
    std::ofstream output("..\\..\\..\\src\\SnesEmulator\\InstructionImplementations.h");

    output << "#pragma once" << std::endl
        << std::endl
        << "#include <stdint.h>" << std::endl
        << std::endl
        << "#include \"State.h\"" << std::endl
        << std::endl
        << "#include \"Instruction.h\"" << std::endl
        << std::endl;

    for (const Instruction& instruction : instructions) {
        int valueSize = stoi(instruction.size) - 1;

        if (!instruction.comment.empty()) {
            output << "// " << instruction.comment << std::endl << std::endl;
        }

        output << "// " << instruction.name << std::endl
            << "// " << instruction.addressMode << std::endl;

        int nSizeRemark = 0;

        if (!instruction.sizeRemark.empty()) {
            nSizeRemark = stoi(instruction.sizeRemark);
            output << "// " << getRemark(nSizeRemark) << std::endl;
        }

        std::ostringstream baseclass;
        std::ostringstream valueArg;
        std::string baseclassInstatiation;
        if (nSizeRemark == 17) {
            baseclassInstatiation = "<State::m>";
        } else if (nSizeRemark == 19) {
            baseclassInstatiation = "<State::x>";
        }

        if (nSizeRemark == 17 || nSizeRemark == 19) {
            baseclass << "InstructionFlagSize";
            valueArg << ", uint16_t value";
        } else {
            baseclass << "Instruction" << instruction.size << "Byte";
            if (valueSize > 0) {
                valueArg << ", uint" << (valueSize == 3 ? 32 : valueSize * 8) << "_t value";
            }
        }

        output << "class " << instruction.handlername << " : public " << baseclass.str() << baseclassInstatiation << " {" << std::endl
            << "    using " << baseclass.str() << "::" << baseclass.str() << ";" << std::endl
            << "public:" << std::endl
            << "    int apply(State& state" << valueArg.str() << ") const override;" << std::endl
            << "};" << std::endl
            << std::endl;
    }
}

void generateHandlers(const std::vector<Instruction>& instructions)
{
    std::ofstream output("..\\..\\..\\src\\SnesEmulator\\InstructionImplementations.cpp");

    output << "#include \"InstructionImplementations.h\"" << std::endl
        << std::endl;

    for (const Instruction& instruction : instructions) {

        if (!instruction.comment.empty()) {
            output << "// " << instruction.comment << std::endl << std::endl;
        }

        output << "// " << instruction.name << std::endl
            << "// " << instruction.addressMode << std::endl;

        int nSizeRemark = 0;

        if (!instruction.sizeRemark.empty()) {
            nSizeRemark = stoi(instruction.sizeRemark);
            output << "// " << getRemark(nSizeRemark) << std::endl;
        }

        int valueSize = stoi(instruction.size) - 1;

        output << "int " << instruction.handlername << "::apply(State& state";

        if (nSizeRemark == 17 || nSizeRemark == 19) {
            output << ", uint16_t value";
        } else if (valueSize > 0) {
            output << ", uint" << (valueSize == 3 ? 32 : valueSize * 8) << "_t value";
        }

        output << ") const" << std::endl;

        output << "{" << std::endl;

        for (int remark : instruction.cyclesRemarks) {
            output << "    // " << getRemark(remark) << std::endl;
        }

        output << "    return " << instruction.cycles;

        for (int cycleRemark : instruction.cyclesRemarks) {
            output << getCycleModification(cycleRemark);
        }

        output << ";" << std::endl
            << "}" << std::endl
            << std::endl;
    }
}

void generateMap(const std::vector<Instruction>& instructions)
{
    std::ofstream output("..\\..\\..\\src\\SnesEmulator\\InstructionMap.cpp");

    output << "#include \"InstructionMap.h\"" << std::endl
        << std::endl
        << "#include <stdint.h>" << std::endl
        << std::endl
        << "#include \"InstructionImplementations.h\"" << std::endl
        << "#include \"State.h\"" << std::endl
        << std::endl;

    output << "Instruction* InstructionMap::getInstruction(uint8_t code) const" << std::endl
        << "{" << std::endl
        << "    return instructions[code].get();" << std::endl
        << "}" << std::endl << std::endl;


    output << "InstructionMap::InstructionMap()" << std::endl
        << "{" << std::endl;
    for (const Instruction& instruction : instructions) {
        output << "    instructions[0x" << instruction.code << "] = std::make_unique<" << instruction.handlername << ">(\"" << instruction.name << "\", \"" << instruction.addressMode << "\");";
        if (!instruction.sizeRemark.empty()) {
            output << " // " << getRemark(stoi(instruction.sizeRemark));
        }
        output << std::endl;
    }
    output << "}" << std::endl;
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

        for (std::vector<std::string> line : lines) {
            if (line.size() == 1) {
                std::cout << line[0] << std::endl;
                comment = line[0];
            } else if (line.size() == 8) {
                for (int i = 0; i < 8; ++i)
                {
                    std::cout << line[i] << '\t';
                }
                std::cout << std::endl;

                std::string name = line[0];

                std::string shortname = name.substr(0, 3);

                std::string code = line[1];
                if (code.size() == 1) {
                    code = "0" + code;
                }

                std::string handlername = shortname + "_" + code;

                std::string addressMode = line[2];

                std::string sizeToken = line[6];
                std::string size = sizeToken.substr(0, 1);

                std::string sizeRemark = sizeToken.substr(1);

                std::string cyclesToken = line[7];
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

                Instruction instruction { name, shortname, comment, code, handlername, addressMode, size, sizeRemark, cycles, cyclesRemarks };
                instruction.validate();
                instructions.push_back(instruction);

                comment.clear();
            }
        }

        generateHeader(instructions);
        generateHandlers(instructions);
        generateMap(instructions);

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