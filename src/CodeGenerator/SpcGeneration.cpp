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
    std::string operatorName;
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

        if (operatorName.empty()) {
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

        //if (cycles != "0" && cycles != "1" && cycles != "2" && cycles != "3" && cycles != "4" && cycles != "5" && cycles != "6" && cycles != "7" && cycles != "8") {
        //    throw std::runtime_error("Instruction " + name + ": cycles out of range: " + cycles);
        //}
    }
};

struct OperatorArgs
{
    OperatorArgs()
        : hasOperand(false)
    {
        cycleRemarks = { 1 };
    }
    std::set<int> cycleRemarks;
    bool hasOperand;
    std::string comment;
};

struct TemplateConfig
{
    TemplateConfig()
        : bitMask(false)
        , index(false)
        , oneRegister(false)
        , twoRegister(false)
    { }
    bool bitMask;
    bool index;
    bool oneRegister;
    bool twoRegister;
};

struct AddressModeClassArgs
{
    AddressModeClassArgs()
        : instructionSize(0)
    {
        cycleRemarks = {};
    }
    std::set<int> cycleRemarks;
    int instructionSize;
    std::string comment;
    TemplateConfig config;
};

struct AddressMode
{
    AddressMode()
    {
    }
    std::string name;
    std::string templateArg;
    TemplateConfig config;
};

AddressMode getAddressMode(const std::string& code)
{
    AddressMode mode;

    if (code == "A, #i") {
        mode.name = "Register Immediate";
        mode.config.oneRegister = true;
        mode.templateArg = "State::A";
    }
    else if (code == "X, #i") {
        mode.name = "Register Immediate";
        mode.config.oneRegister = true;
        mode.templateArg = "State::X";
    }
    else if (code == "Y, #i") {
        mode.name = "Register Immediate";
        mode.config.oneRegister = true;
        mode.templateArg = "State::Y";
    }
    else if (code == "A, d") {
        mode.name = "Register Direct";
        mode.config.oneRegister = true;
        mode.templateArg = "State::A";
    }
    else if (code == "X, d") {
        mode.name = "Register Direct";
        mode.config.oneRegister = true;
        mode.templateArg = "State::X";
    }
    else if (code == "Y, d") {
        mode.name = "Register Direct";
        mode.config.oneRegister = true;
        mode.templateArg = "State::Y";
    }
    else if (code == "A, !a") {
        mode.name = "Register Absolute";
        mode.config.oneRegister = true;
        mode.templateArg = "State::A";
    }
    else if (code == "X, !a") {
        mode.name = "Register Absolute";
        mode.config.oneRegister = true;
        mode.templateArg = "State::X";
    }
    else if (code == "Y, !a") {
        mode.name = "Register Absolute";
        mode.config.oneRegister = true;
        mode.templateArg = "State::Y";
    }
    else if (code == "A") {
        mode.name = "Register";
        mode.config.oneRegister = true;
        mode.templateArg = "State::A";
    }
    else if (code == "X") {
        mode.name = "Register";
        mode.config.oneRegister = true;
        mode.templateArg = "State::X";
    }
    else if (code == "Y") {
        mode.name = "Register";
        mode.config.oneRegister = true;
        mode.templateArg = "State::Y";
    }
    else if (code == "PSW") {
        mode.name = "Register";
        mode.config.oneRegister = true;
        mode.templateArg = "State::PSW";
    }
    else if (code == "d, A") {
        mode.name = "Direct Register";
        mode.config.oneRegister = true;
        mode.templateArg = "State::A";
    }
    else if (code == "d, X") {
        mode.name = "Direct Register";
        mode.config.oneRegister = true;
        mode.templateArg = "State::X";
    }
    else if (code == "d, Y") {
        mode.name = "Direct Register";
        mode.config.oneRegister = true;
        mode.templateArg = "State::Y";
    }
    else if (code == "!a, A") {
        mode.name = "Absolute Register";
        mode.config.oneRegister = true;
        mode.templateArg = "State::A";
    }
    else if (code == "!a, X") {
        mode.name = "Absolute Register";
        mode.config.oneRegister = true;
        mode.templateArg = "State::X";
    }
    else if (code == "!a, Y") {
        mode.name = "Absolute Register";
        mode.config.oneRegister = true;
        mode.templateArg = "State::Y";
    }
    else if (code == "d+X") {
        mode.name = "Direct Indexed";
        mode.config.oneRegister = true;
        mode.templateArg = "State::X";
    }
    else if (code == "d+X, r") {
        mode.name = "Direct Indexed Program Counter Relative";
        mode.config.oneRegister = true;
        mode.templateArg = "State::X";
    }
    else if (code == "Y, r") {
        mode.name = "Register Program Counter Relative";
        mode.config.oneRegister = true;
        mode.templateArg = "State::Y";
    }
    else if (code == "YA, X") {
        mode.name = "Y Accumulator Index";
        mode.config.oneRegister = true;
        mode.templateArg = "State::X";
    }
    else if (code == "[!a+X]") {
        mode.name = "Absolute Indexed Indirect";
        mode.config.oneRegister = true;
        mode.templateArg = "State::X";
    }
    else if (code == "A, [d]+Y") {
        mode.name = "Register Direct Indirect Indexed";
        mode.config.twoRegister = true;
        mode.templateArg = "State::A, State::Y";
    }
    else if (code == "A, [d+X]") {
        mode.name = "Register Direct Indexed Indirect";
        mode.config.twoRegister = true;
        mode.templateArg = "State::A, State::X";
    }
    else if (code == "A, d+X") {
        mode.name = "Register Direct Indexed";
        mode.config.twoRegister = true;
        mode.templateArg = "State::A, State::X";
    }
    else if (code == "X, d+Y") {
        mode.name = "Register Direct Indexed";
        mode.config.twoRegister = true;
        mode.templateArg = "State::X, State::Y";
    }
    else if (code == "Y, d+X") {
        mode.name = "Register Direct Indexed";
        mode.config.twoRegister = true;
        mode.templateArg = "State::Y, State::X";
    }
    else if (code == "A, X") {
        mode.name = "Register Register";
        mode.config.twoRegister = true;
        mode.templateArg = "State::A, State::X";
    }
    else if (code == "A, Y") {
        mode.name = "Register Register";
        mode.config.twoRegister = true;
        mode.templateArg = "State::A, State::Y";
    }
    else if (code == "SP, X") {
        mode.name = "Register Register";
        mode.config.twoRegister = true;
        mode.templateArg = "State::SP, State::X";
    }
    else if (code == "X, A") {
        mode.name = "Register Register";
        mode.config.twoRegister = true;
        mode.templateArg = "State::X, State::A";
    }
    else if (code == "X, SP") {
        mode.name = "Register Register";
        mode.config.twoRegister = true;
        mode.templateArg = "State::X, State::SP";
    }
    else if (code == "Y, A") {
        mode.name = "Register Register";
        mode.config.twoRegister = true;
        mode.templateArg = "State::Y, State::A";
    }
    else if (code == "d+X, A") {
        mode.name = "Direct Indexed Register";
        mode.config.twoRegister = true;
        mode.templateArg = "State::X, State::A";
    }
    else if (code == "d+X, Y") {
        mode.name = "Direct Indexed Register";
        mode.config.twoRegister = true;
        mode.templateArg = "State::X, State::Y";
    }
    else if (code == "d+Y, X") {
        mode.name = "Direct Indexed Register";
        mode.config.twoRegister = true;
        mode.templateArg = "State::Y, State::X";
    }
    else if (code == "A, !a+X") {
        mode.name = "Register Absolute Indexed";
        mode.config.twoRegister = true;
        mode.templateArg = "State::A, State::X";
    }
    else if (code == "A, !a+Y") {
        mode.name = "Register Absolute Indexed";
        mode.config.twoRegister = true;
        mode.templateArg = "State::A, State::Y";
    }
    else if (code == "!a+X, A") {
        mode.name = "Absolute Indexed Register";
        mode.config.twoRegister = true;
        mode.templateArg = "State::X, State::A";
    }
    else if (code == "!a+Y, A") {
        mode.name = "Absolute Indexed Register";
        mode.config.twoRegister = true;
        mode.templateArg = "State::Y, State::A";
    }
    else if (code == "A, (X)") {
        mode.name = "Register Register Indirect";
        mode.config.twoRegister = true;
        mode.templateArg = "State::A, State::X";
    }
    else if (code == "(X)+, A") {
        mode.name = "Register Indirect Increment Register";
        mode.config.twoRegister = true;
        mode.templateArg = "State::X, State::A";
    }
    else if (code == "(X), A") {
        mode.name = "Register Indirect Register";
        mode.config.twoRegister = true;
        mode.templateArg = "State::X, State::A";
    }
    else if (code == "[d]+Y, A") {
        mode.name = "Direct Indirect Indexed Register";
        mode.config.twoRegister = true;
        mode.templateArg = "State::Y, State::A";
    }
    else if (code == "[d+X], A") {
        mode.name = "Direct Indexed Indirect Register";
        mode.config.twoRegister = true;
        mode.templateArg = "State::X, State::A";
    }
    else if (code == "A, (X)+") {
        mode.name = "Register Register Indirect Increment";
        mode.config.twoRegister = true;
        mode.templateArg = "State::A, State::X";
    }
    else if (code.substr(0, 2) == "d.") {
        mode.config.bitMask = true;
        mode.templateArg = "1 << " + code.substr(2, 1);
        if (code.size() == 3) {
            mode.name = "Direct Bit";
        }
        else {
            mode.name = "Direct Bit Program Counter Relative";
        }
    }
    else if (code == "(X), (Y)") {
        mode.name = "Indirect Indirect";
    }
    else if (code == "dd, ds") {
        mode.name = "Direct Direct";
    }
    else if (code == "d, #i") {
        mode.name = "Direct Immediate";
    }
    else if (code == "YA, d") {
        mode.name = "Y Accumulator Direct";
    }
    else if (code == "C, /m.b") {
        mode.name = "Carry Negated Memory Bit";
    }
    else if (code == "C, m.b") {
        mode.name = "Carry Memory Bit";
    }
    else if (code == "d") {
        mode.name = "Direct";
    }
    else if (code == "!a") {
        mode.name = "Absolute";
    }
    else if (code == "r") {
        mode.name = "Program Counter Relative";
    }
    else if (code == "") {
        mode.name = "Implied";
    }
    else if (code == "d, r") {
        mode.name = "Direct Program Counter Relative";
    }
    else if (code == "m.b, C") {
        mode.name = "Memory Bit Carry";
    }
    else if (code == "d, YA") {
        mode.name = "Direct Y Accumulator";
    }
    else if (code == "YA") {
        mode.name = "Y Accumulator";
    }
    else if (code == "m.b") {
        mode.name = "Memory Bit";
    }
    else if (code == "u") {
        mode.name = "U Page";
    }
    else {
        mode.name = "Table";
        mode.templateArg = code;
        mode.config.index = true;
    }
    return mode;
}

std::string getRemark(int remarkIndex)
{
    switch (remarkIndex) {
    case 1: return "§1: Add 1 cycle if branch is taken";
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
    case 1: return { "true /*branch taken*/", "cycles += 2;\n            throw std::runtime_error(\"TODO01\")" }; // Add 1 cycle if branch is taken
    default: return {};
    }
}

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

    output << "class " << classname
        << " : public AddressMode::" << addressModeClass
        << "<Operator::" << instruction.operatorName;
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
    if (args.config.bitMask) {
        output << ", uint8_t BitMask";
    }
    else if (args.config.index)
    {
        output << ", uint8_t Index";
    }
    else if (args.config.oneRegister)
    {
        output << ", State::Register RegisterIndex";
    }
    else if (args.config.twoRegister) {
        output << ", State::Register FirstRegister, State::Register SecondRegister";
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
        output << "Byte lowByte";
        if (actualSize >= 3) {
            output << ", Byte highByte";
            if (actualSize >= 4) {
                output << ", Byte bankByte";
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
        output << "        Byte* data = nullptr;" << std::endl;
    }
    output << "        return ";
    if (hasCycleModification(args.cycleRemarks)) {
        output << "cycles + ";
    }
    output << "Operator::invoke(state";
    if (name != "Implied") {
        output << ", *data, 0";
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
        << "typedef InstructionBase<State, Byte> Instruction2Byte;" << std::endl
        << "typedef InstructionBase<State, Byte, Byte> Instruction3Byte;" << std::endl
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
            output << ", Byte& leftOperand, const Byte& rightOperand";
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

            comment = line[5] + "    \t[" + line[6] + "]";

            std::string operatorName = mnemonic;
            if (operatorName == "MOV" && line[6] == "N.....Z.") {
                operatorName += "_SignedResult";
            }

            std::string size = line[3];

            std::string addressModeClass = addressMode.name;
            addressModeClass.erase(std::remove(addressModeClass.begin(), addressModeClass.end(), ' '), addressModeClass.end());
            addressModeClass.erase(std::remove(addressModeClass.begin(), addressModeClass.end(), ','), addressModeClass.end());
            addressModeClass.erase(std::remove(addressModeClass.begin(), addressModeClass.end(), '('), addressModeClass.end());
            addressModeClass.erase(std::remove(addressModeClass.begin(), addressModeClass.end(), ')'), addressModeClass.end());
            addressModeClass.erase(std::remove(addressModeClass.begin(), addressModeClass.end(), '/'), addressModeClass.end());

            int instructionSize = stoi(size);

            std::string cycles;
            std::string cyclesRemark;

            size_t pos = line[4].find('/');
            if (pos != std::string::npos) {
                cycles = line[4].substr(0, pos);
                cyclesRemark = "1";
            }
            else {
                cycles = line[4];
            }

            std::set<int> cyclesRemarks;
            OperatorArgs& operatorArgs = operatorMap[operatorName];
            std::set<int> operatorIntersection;
            AddressModeClassArgs& addressModeClassArgs = addressModeClassMap[addressModeClass];

            std::string addressModeComment = addressModeClassArgs.comment;
            if (addressModeComment.empty()) {
                addressModeComment = addressMode.name;
            }
            addressModeComment += "\n// " + mnemonic + " " + addressModeCode + ":     \t" + comment;

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
            addressModeClassArgs.config = addressMode.config;

            Instruction instruction { name, operatorName, comment, opcode, classname, addressMode.name, addressModeClass, size, cycles, cyclesRemarks, addressMode.templateArg };
            instruction.validate();
            instructions.push_back(instruction);

            // TMP
            //addressModeMap[addressModeCode].push_back(addressMode + ", " + name + ", code=" + code + ", cycles=" + cycles + ", size=" + size);
            //addressModeMap[addressMode].push_back(name + ", code=" + code + ", cycles=" + cycles + ", size=" + size + ", sizeRemark=" + sizeRemark);
            //addressModeMap[mnemonic].push_back(opcode + ": " + name + ", " + addressMode.name + ", cycles=" + cycles + ", size=" + size);
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
            if (kvp.first == instruction.operatorName) {
                for (int remark : kvp.second.cycleRemarks) {
                    instruction.cyclesRemarks.erase(remark);
                    if (removedRemarks.find(remark) != removedRemarks.end()) {
                        std::cout << "Nope, remark removed twice from " << instruction.classname << ": " << remark << ", " << instruction.operatorName << ", " << instruction.addressModeClass << std::endl;
                    }
                }
            }
        }
    }

    generateOpcodes(instructions);
    //generateOpcodeMap(instructions);
    //generateAddressModes(addressModeClassMap);
    //generateOperators(operatorMap);

    int i = 0;
    for (const AddressModeMap::value_type kvp : addressModeMap) {
        //std::cout << ++i << ": " << kvp.first << std::endl;
        for (std::string info : kvp.second) {
            //std::cout << "\t\t" << info << std::endl;
        }
        //std::getchar();
    }

}