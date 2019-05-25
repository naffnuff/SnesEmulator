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
        WriteOnly
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
        if (mirroredMemory) {
            return mirroredMemory->getType();
        }
        else {
            return type;
        }
    }

    bool isMirror() const
    {
        return false;
    }

    bool isReadProtected() const
    {
        return type != ReadOnly && type != ReadWrite;
    }

    bool isWriteProtected() const
    {
        return type != ReadWrite && type != WriteOnly;
    }

    void setValue(Byte newValue)
    {
        if (mirroredMemory) {
            mirroredMemory->setValue(newValue);
            return;
        }

        if (isWriteProtected()) {
            ThrowAccessException(__FUNCTION__);
        }

        Byte oldValue;
        if (writeMapping) {
            oldValue = writeMapping->value;
            writeMapping->value = newValue;
        } else {
            oldValue = value;
            value = newValue;
        }
        if (onWrite) {
            onWrite(oldValue, newValue);
        }
    }

    Byte getValue() const
    {
        if (mirroredMemory) {
            return mirroredMemory->getValue();
        }

        if (isReadProtected()) {
            ThrowAccessException(__FUNCTION__);
        }

        Byte result = value;
        if (readMapping) {
            result = readMapping->value;
        }
        if (onRead) {
            onRead(result);
        }

        return result;
    }

    Byte apply()
    {
        if (mirroredMemory) {
            return mirroredMemory->apply();
        }

        if (isReadProtected() || readMapping || writeMapping) {
            ThrowAccessException(__FUNCTION__);
        }

        ++applicationCount;

        if (onApply) {
            onApply(value);
        }

        return value;
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

    void setMappings(MemoryLocation* readMapping, MemoryLocation* writeMapping, Type type)
    {
        if (this->type != Invalid) {
            ThrowAccessException(__FUNCTION__);
        }
        this->readMapping = readMapping;
        this->writeMapping = writeMapping;
        this->type = type;
    }

    void setMirrorOf(MemoryLocation* memory)
    {
        if (type != Invalid) {
            ThrowAccessException(__FUNCTION__);
        }
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
    MemoryLocation* readMapping = nullptr;
    MemoryLocation* writeMapping = nullptr;
    MemoryLocation* mirroredMemory = nullptr;
    Type type = Invalid;
    int applicationCount = 0;

public:
    std::function<void(Byte value)> onRead;
    std::function<void(Byte oldValue, Byte newValue)> onWrite;
    std::function<void(Byte value)> onApply;

    friend std::ostream& operator<<(std::ostream&, const MemoryLocation&);
};

inline std::ostream& operator<<(std::ostream& output, const MemoryLocation& memory)
{
    if (memory.mirroredMemory) {
        return output << memory.mirroredMemory->value << std::dec;
    }
    else {
        return output << memory.value << std::dec;
    }
}
