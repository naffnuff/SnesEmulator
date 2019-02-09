#include <iostream>

#include "Emulator.h"

int main(int argc, char* argv[])
{
    try {

        Emulator emulator;
        emulator.run();

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
