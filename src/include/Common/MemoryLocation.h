#pragma once

#include <iostream>
#include <functional>

#include "Types.h"

class MemoryLocation
{
public:
    class AccessException : public std::runtime_error
    {
        using std::runtime_error::runtime_error;
    };

    enum Type
    {
        Invalid,
        ReadOnly,
        ReadWrite,
        WriteOnly,
        Mapped
    };

    enum Operation
    {
        Read,
        Write,
        Access,
        Apply
    };

    MemoryLocation()
    {
    }

    MemoryLocation(Byte value)
        : value(value)
    {
    }

    Type getType() const
    {
        return type;
    }

    bool isMirror() const
    {
        return mirroredMemory;
    }

    bool isReadProtected() const
    {
        return type != ReadOnly && type != ReadWrite && type != Mapped;
    }

    bool isWriteProtected() const
    {
        return type != ReadWrite && type != WriteOnly && type != Mapped;
    }

    void setValue(Byte byte)
    {
        if (isWriteProtected()) {
            ThrowAccessException(__FUNCTION__);
        }

        if (mirroredMemory) {
            mirroredMemory->value = byte;
        }
        else if (mapping) {
            mapping->value = byte;
        }
        else {
            value = byte;
        }

        if (trap) {
            trap(Write, byte);
        }
    }

    Byte getValue() const
    {
        if (isReadProtected()) {
            ThrowAccessException(__FUNCTION__);
        }

        if (trap) {
            trap(Read, value);
        }

        if (mirroredMemory) {
            return mirroredMemory->value;
        }
        else {
            return value;
        }
    }

    Byte apply()
    {
        if (isReadProtected() || type == Mapped) {
            ThrowAccessException(__FUNCTION__);
        }

        ++applicationCount;

        if (trap) {
            trap(Apply, value);
        }

        if (mirroredMemory) {
            return mirroredMemory->value;
        }
        else {
            return value;
        }
    }

    Byte& get()
    {
        if (isReadProtected() || isWriteProtected() || type == Mapped) {
            ThrowAccessException(__FUNCTION__);
        }

        if (trap) {
            trap(Access, value);
        }

        if (mirroredMemory) {
            return mirroredMemory->value;
        }
        else {
            return value;
        }
    }

    void setWordValue(Word value)
    {
        this[0].setValue(Byte(value));
        this[1].setValue(Byte(value >> 8));
    }

    Word getWordValue() const
    {
        return Word(this[0].getValue(), this[1].getValue());
    }

    void setMapping(MemoryLocation* memory)
    {
        if (type != Invalid) {
            ThrowAccessException(__FUNCTION__);
        }
        type = Mapped;
        mapping = memory;
    }

    void setMirror(MemoryLocation* memory, Type mirrorType)
    {
        if (type != Invalid) {
            ThrowAccessException(__FUNCTION__);
        }
        type = mirrorType;
        mirroredMemory = memory;
    }

    void setReadOnlyValue(Byte byte)
    {
        if (type != Invalid) {
            ThrowAccessException(__FUNCTION__);
        }
        type = ReadOnly;
        value = byte;
    }

    void setReadWrite()
    {
        if (type != Invalid) {
            ThrowAccessException(__FUNCTION__);
        }
        type = ReadWrite;
    }

    void setWriteOnly()
    {
        if (type != Invalid) {
            ThrowAccessException(__FUNCTION__);
        }
        type = WriteOnly;
    }

    int getApplicationCount() const
    {
        return applicationCount;
    }

private:
    static void ThrowAccessException(const std::string& function)
    {
        throw AccessException(function + ": Bad memory access");
    }

private:
    Byte value = 0;
    MemoryLocation* mapping = nullptr;
    MemoryLocation* mirroredMemory = nullptr;
    Type type = Invalid;
    int applicationCount = 0;

public:
    std::function<void(Operation, Byte)> trap;

    friend std::ostream& operator<<(std::ostream&, const MemoryLocation&);
};

inline std::ostream& operator<<(std::ostream& output, const MemoryLocation& memory)
{
    if (memory.mirroredMemory) {
        return output << memory.mirroredMemory->value << std::dec;
    }
    return output << memory.value << std::dec;
}
