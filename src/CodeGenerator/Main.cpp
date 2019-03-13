#include <iostream>

void generateSpc();

int main(int argc, char* argv[])
{
    try {
        generateSpc();

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