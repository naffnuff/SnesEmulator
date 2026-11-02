#include "Test.h"

#include "Types.h"

#include <random>
#include <iostream>

std::random_device randomDevice;
std::mt19937 generator(randomDevice());

int getRandomInt(int max)
{
    return generator() % (max + 1);
}

Byte toDecimalByte(int integer)
{
    return Byte((((integer % 100) / 10) << 4) | (integer % 10));
}

Word toDecimalWord(int integer)
{
    return Word((((integer % 10000) / 1000) << 12) | (((integer % 1000) / 100) << 8) | (((integer % 100) / 10) << 4) | (integer % 10));
}

template<typename T>
void testDecimalAdd(T augend, T addend, bool carry, T expectedSum, bool expectedCarry, bool expectedOverflow)
{
    bool carryIn = carry;
    bool overflow;
    T sum = Types::decimalAdd(augend, addend, carry, overflow);
    std::cout << augend << " + " << addend << " + carry " << carryIn << " = " << sum << " (carry = " << carry << ", overflow = " << overflow << ")" << std::endl;
    if (sum != expectedSum || carry != expectedCarry || overflow != expectedOverflow)
    {
        std::stringstream ss;
        ss << augend << " + " << addend << " + carry " << carryIn << " = " << std::endl;
        ss << sum << " (carry " << carry << ", overflow " << overflow << ") is not expected result: " << std::endl;
        ss << expectedSum << " (carry " << expectedCarry << ", overflow " << expectedOverflow << ")" << std::endl;
        throw std::runtime_error(ss.str());
    }
}

void testDecimalMode()
{
    int numberOfTests = 10;
    for (int i = 0; i < numberOfTests; ++i)
    {
        {
            int augend = getRandomInt(99);
            std::cout << "augend: " << augend << std::endl;
            int addend = getRandomInt(99);
            std::cout << "addend: " << addend << std::endl;
            bool carry = getRandomInt(1);
            std::cout << "carry: " << carry << std::endl;

            int expectedSum = augend + addend + carry;
            std::cout << "expectedSum: " << expectedSum << std::endl;
            bool expectedCarry = expectedSum > 99;

            int8_t signedSum = int8_t(augend) + int8_t(addend) + int8_t(carry);
            std::cout << "signedSum: " << int(signedSum) << std::endl;

            bool expectedOverflow = (((toDecimalByte(augend) ^ toDecimalByte(expectedSum)) & (toDecimalByte(addend) ^ toDecimalByte(expectedSum))) & 0x80) != 0;

            testDecimalAdd(toDecimalByte(augend), toDecimalByte(addend), carry, toDecimalByte(expectedSum), expectedCarry, expectedOverflow);
        }
        {
            int augend = getRandomInt(9999);
            std::cout << "augend: " << augend << std::endl;
            int addend = getRandomInt(9999);
            std::cout << "addend: " << addend << std::endl;
            bool carry = getRandomInt(1);
            std::cout << "carry: " << carry << std::endl;

            int expectedSum = augend + addend + carry;
            std::cout << "expectedSum: " << expectedSum << std::endl;
            bool expectedCarry = expectedSum > 9999;

            int16_t signedSum = int16_t(augend) + int16_t(addend) + int16_t(carry);
            std::cout << "signedSum: " << signedSum << std::endl;
            bool expectedOverflow = (((toDecimalWord(augend) ^ toDecimalWord(expectedSum)) & (toDecimalWord(addend) ^ toDecimalWord(expectedSum))) & 0x8000) != 0;

            testDecimalAdd(toDecimalWord(augend), toDecimalWord(addend), carry, toDecimalWord(expectedSum), expectedCarry, expectedOverflow);
        }
    }
}

void runTests()
{
    testDecimalMode();
}