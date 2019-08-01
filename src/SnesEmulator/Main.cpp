#include <iostream>
#include <bitset>
#include <thread>
#include <filesystem>

#include "Emulator.h"
#include "Renderer.h"

void test(std::ostream& output)
{
    auto hej = [&output](uint8_t a, uint8_t b) {
        output
            << "Unsigned: " << +uint8_t(a) << " + " << +uint8_t(b) << std::endl
            << "Signed:   " << +int8_t(a) << " + " << +int8_t(b) << std::endl
            << "Unsigned: " << uint16_t(uint8_t(a) + uint8_t(b)) << std::endl
            << "Signed:   " << int16_t(int8_t(a) + int8_t(b)) << " " << std::endl << std::endl;
    };
    uint8_t a = 0xaa;
    uint8_t b = 0xaa;
    output << std::hex;
    hej(a, b);
    output << std::dec;
    hej(a, b);

    int16_t c = int16_t(int8_t(a) + int8_t(b));
    uint16_t d = uint16_t(uint8_t(a) + uint8_t(b));
    output
        << "Unsigned: " << std::bitset<8>(uint8_t(a)) << " + " << std::bitset<8>(uint8_t(b)) << std::endl
        << "Signed:   " << std::bitset<8>(int8_t(a)) << " + " << std::bitset<8>(int8_t(b)) << std::endl;
    output
        << "Unsigned: " << std::bitset<16>(uint8_t(a)) << " + " << std::bitset<16>(uint8_t(b)) << std::endl
        << "Signed:   " << std::bitset<16>(int8_t(a)) << " + " << std::bitset<16>(int8_t(b)) << std::endl;
    output
        << "Unsigned: " << std::bitset<8>(d >> 8) << " " << std::bitset<8>(d) << std::endl
        << "Signed:   " << std::bitset<8>(c >> 8) << " " << std::bitset<8>(c) << std::endl;
}

int main(int, char**)
{
    std::ostream& output = std::cout;
    std::istream& input = std::cin;
    std::ostream& error = std::cerr;

    /*for (int i = 0; i < 256; i += 32) {
        for (int j = 0; j < 256; j += 32) {
            Byte a(i);
            Byte b(j);
            bool carry = false;
            bool overflow = false;
            output << +char(a) << " + " << +char(b) << " = " << +char(Types::binaryAdd(a, b, carry, overflow)) << ", carry=" << carry << ", overflow=" << overflow << std::endl;
        }
    }*/

    try {
        while (true) {
            Rom rom(output);

            output << "Welcome to Naffnuff's SNES emulator!" << std::endl;
            std::vector<std::string> titles;
            while (titles.empty()) {
                for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(".")) {
                    std::string extension = entry.path().extension().string();
                    if (entry.is_regular_file() && (extension == ".smc" || extension == ".sfc")) {
                        std::string filename = entry.path().filename().string();
                        titles.push_back(filename);
                        output << titles.size() << ". " << filename << std::endl;
                    }
                }
                if (titles.empty()) {
                    output << "Put some ROM images in the same folder as the application file and press enter!" << std::endl;
                    int dummy = std::getchar();
                }
            }
            std::string pickedTitle;
            while (pickedTitle.empty()) {
                int inputValue = -1;
                input >> inputValue;
                int dummy = std::getchar();
                output << "Input: " << inputValue << std::endl;
                --inputValue;
                if (inputValue >= 0 && inputValue < titles.size()) {
                    pickedTitle = titles[inputValue];
                }
            }
            rom.loadFromFile(pickedTitle);

            Emulator emulator(output, input, error, rom);
            emulator.initialize();
            emulator.run();
        }

    } catch (const std::exception& e) {
        error << "Caught std::exception: " << e.what() << std::endl;
        error << "Failure";
        std::getchar();
        return 1;
    }

    output << "Success";
    std::getchar();
    return 0;
}
