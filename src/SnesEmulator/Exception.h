#pragma once

#include <stdexcept>

class OpcodeNotYetImplementedException : public std::logic_error
{
public:
    OpcodeNotYetImplementedException(const std::string& name)
        : std::logic_error("Opcode not yet implemented: " + name)
    {
    }
};

class AddressModeNotYetImplementedException : public std::logic_error
{
public:
    AddressModeNotYetImplementedException(const std::string& name)
        : std::logic_error("Address mode not yet implemented: " + name)
    {
    }
};

class OperatorNotYetImplementedException : public std::logic_error
{
public:
    OperatorNotYetImplementedException(const std::string& name)
        : std::logic_error("Operator not yet implemented: " + name)
    {
    }
};
