#include <iostream>

#include "Emulator.h"

int main(int argc, char* argv[])
{
    std::ostream& output = std::cout << std::hex;
    std::istream& input = std::cin;
    std::ostream& error = std::cerr << std::hex;

    try {

        Emulator emulator;
        emulator.run(output, input, error);

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
