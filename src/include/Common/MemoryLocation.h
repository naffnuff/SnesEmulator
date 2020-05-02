#pragma once

#include <iostream>
#include <functional>

#include "Types.h"

//#define DEBUGMEMORY

class MemoryLocation
{
public:
    class AccessException : public std::logic_error
    {
        using std::logic_error::logic_error;
    };

    enum Type
    {
        Invalid,
        ReadOnly,
        ReadWrite,
        WriteOnly
    };

    enum Operation
    {
        Read,
        Write,
        Apply
    };

    typedef std::function<std::string(const MemoryLocation*)> DebugNameQuery;

    /*MemoryLocation()
        : nextInMemory(&this[1])
        , nextInBank(&this[1])
        , nextInPage(&this[1])
    {
    }*/

    MemoryLocation(Byte value, DebugNameQuery debugNameQuery)
        : value(value)
        , debugNameQuery(debugNameQuery)
        , nextInMemory(&this[1])
        , nextInBank(&this[1])
        , nextInPage(&this[1])
    {
    }

    MemoryLocation(Type type, Byte value, DebugNameQuery debugNameQuery)
        : type(type)
        , value(value)
        , debugNameQuery(debugNameQuery)
        , nextInMemory(&this[1])
        , nextInBank(&this[1])
        , nextInPage(&this[1])
    {
    }

    MemoryLocation(const MemoryLocation& other)
        : debugNameQuery(other.debugNameQuery)
        , nextInMemory(&this[1])
        , nextInBank(&this[1])
        , nextInPage(&this[1])
    {
    }

    MemoryLocation& operator=(const MemoryLocation&) = delete;

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
            try {
                mirroredMemory->setValue(newValue);
            }
            catch (const AccessException& e) {
                throwAccessException(e.what());
            }
            return;
        }

        if (isWriteProtected()) {
            throwAccessException(__FUNCTION__);
        }

        Byte oldValue;
        if (writeMapping) {
            oldValue = writeMapping->value;
        } else {
            oldValue = value;
        }
        if (onWrite) {
            onWrite(oldValue, newValue);
        }
        if (writeMapping) {
            writeMapping->value = newValue;
        }
        else {
            value = newValue;
        }
        if (breakpoint) {
            breakpoint(Write, newValue, applicationCount);
        }
    }

    Byte getValue() const
    {
        if (mirroredMemory) {
            try {
                return mirroredMemory->getValue();
            }
            catch (const AccessException& e) {
                throwAccessException(e.what());
            }
        }

        if (isReadProtected()) {
            throwAccessException(__FUNCTION__);
        }

        Byte result = value;
        if (readMapping) {
            result = readMapping->value;
        }
        if (onRead) {
            onRead(result);
        }
        if (breakpoint) {
            breakpoint(Read, result, applicationCount);
        }

        return result;
    }

    static uint64_t maxApplicationCount;

    Byte apply()
    {
        if (mirroredMemory) {
            try {
                return mirroredMemory->apply();
            }
            catch (const AccessException& e) {
                throwAccessException(e.what());
            }
        }

        if (isReadProtected() || readMapping || writeMapping) {
            throwAccessException(__FUNCTION__);
        }

        ++applicationCount;
        if (applicationCount > maxApplicationCount) {
            maxApplicationCount = applicationCount;
        }

        Byte result = value;
        if (onApply) {
            onApply(result);
        }
        if (breakpoint) {
            breakpoint(Apply, result, applicationCount);
        }

        return result;
    }

    void setWordValue(Word value)
    {
        this[0].setValue(Byte(value));
        this[1].setValue(Byte(value >> 8));
    }

    Word getWordValue() const
    {
        Byte lowByte = this[0].getValue();
        Byte highByte = this[1].getValue();
        return Word(lowByte, highByte);
    }

    void setMappings(MemoryLocation* readMapping, MemoryLocation* writeMapping, Type type)
    {
        if (this->type != Invalid) {
            throwAccessException(__FUNCTION__);
        }
        this->readMapping = readMapping;
        this->writeMapping = writeMapping;
        this->type = type;
    }

    void setMappings(MemoryLocation* mapping)
    {
        setMappings(mapping, mapping, ReadWrite);
    }

    void setMirrorOf(MemoryLocation* memory)
    {
        if (memory == this) {
            throwAccessException(std::string("Mirror to this: ") + __FUNCTION__);
        }
        if (type != Invalid) {
            throwAccessException(std::string("Invalid memory: ") + __FUNCTION__);
        }
        mirroredMemory = memory;
    }

    void setReadOnlyValue(Byte byte)
    {
        if (type != Invalid) {
            throwAccessException(__FUNCTION__);
        }
        type = ReadOnly;
        value = byte;
        //resetValue = value;
    }

    void setReadWrite()
    {
        if (type != Invalid) {
            throwAccessException(__FUNCTION__);
        }
        type = ReadWrite;
    }

    void setWriteOnly()
    {
        if (type != Invalid) {
            throwAccessException(__FUNCTION__);
        }
        type = WriteOnly;
    }

    uint64_t getApplicationCount() const
    {
        if (mirroredMemory) {
            return mirroredMemory->getApplicationCount();
        }
        else {
            return applicationCount;
        }
    }

    void reset()
    {
        applicationCount = 0;
    }

    void setBreakpoint(std::function<void(Operation operation, Byte value, uint64_t applicationCount)> value)
    {
        if (mirroredMemory) {
            mirroredMemory->setBreakpoint(value);
        }
        else {
            breakpoint = value;
        }
    }

    bool hasBreakpoint() const
    {
        if (mirroredMemory) {
            return mirroredMemory->hasBreakpoint();
        }
        else {
            return breakpoint != nullptr;
        }
    }

private:
    void throwAccessException(const std::string& function) const
    {
        throw AccessException(function + ": Bad memory access @ " + debugNameQuery(this));
    }

private:
    Byte value = 0;
    //Byte resetValue = 0;
    MemoryLocation* readMapping = nullptr;
    MemoryLocation* writeMapping = nullptr;
    MemoryLocation* mirroredMemory = nullptr;
    Type type = Invalid;
    uint64_t applicationCount = 0;

    std::function<void(Operation operation, Byte value, uint64_t applicationCount)> breakpoint = nullptr;

    DebugNameQuery debugNameQuery = nullptr;

public:
    MemoryLocation* nextInMemory = nullptr;
    MemoryLocation* nextInBank = nullptr;
    MemoryLocation* nextInPage = nullptr;

    std::function<void(Byte& value)> onRead = nullptr;
    std::function<void(Byte oldValue, Byte& newValue)> onWrite = nullptr;
    std::function<void(Byte& value)> onApply = nullptr;

    friend std::ostream& operator<<(std::ostream&, const MemoryLocation&);
};

inline std::ostream& operator<<(std::ostream& output, const MemoryLocation& memory)
{
    if (MemoryLocation* mirroredMemory = memory.mirroredMemory) {
        while (mirroredMemory->mirroredMemory) {
            mirroredMemory = mirroredMemory->mirroredMemory;
        }
        return output << mirroredMemory->value << std::dec;
    }
    else if (memory.readMapping) {
        return output << memory.readMapping->value << std::dec;
    }
    else {
        return output << memory.value << std::dec;
    }
}
