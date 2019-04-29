#include <iostream>
#include <bitset>
#include <thread>

#include "SnesEmulator.h"
#include "SnesRenderer.h"

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

    try {
        while (true) {
            Emulator emulator(output, input, error);
            emulator.initialize();
            {
                std::thread thread([&emulator, &output, &input, &error]() {
                    Nox::Renderer renderer(emulator, output, input, error);
                    renderer.initialize();
                    while (renderer.isRunning()) {
                        renderer.update();
                    }
                    });

                emulator.run();

                thread.join();
            }
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
