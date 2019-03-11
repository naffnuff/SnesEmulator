#include <iostream>

#include "Emulator.h"

int main(int, char*)
{
    std::ostream& output = std::cout << std::hex;
    std::istream& input = std::cin;
    std::ostream& error = std::cerr << std::hex;

    try {
        Emulator emulator(output, input, error);
        emulator.run();

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
