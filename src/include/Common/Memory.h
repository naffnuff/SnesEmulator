#pragma once

#include <memory>
#include <functional>
#include <vector>
#include <sstream>

#include "Types.h"

class MemoryAccessException : public std::logic_error
{
    using std::logic_error::logic_error;
};

class LocationVisitor
{
public:
    virtual void visit(const class Location&) = 0;
    virtual void visit(const class ReadOnlyMemory&) = 0;
    virtual void visit(const class ReadWriteMemory&) = 0;
    virtual void visit(const class ReadRegister&) = 0;
    virtual void visit(const class WriteRegister&) = 0;
    virtual void visit(const class ReadWriteRegister&) = 0;
};

class Location
{
public:
    Location() = default;

    Location(const Location&) = delete;
    Location& operator=(const Location&) = delete;

protected:
    virtual void write(Byte)
    {
        throwAccessException(__FUNCTION__, "writing not allowed");
    }

    virtual Byte read()
    {
        throwAccessException(__FUNCTION__, "reading not allowed");
        return Byte();
    }

    virtual Byte apply()
    {
        throwAccessException(__FUNCTION__, "application not allowed");
        return Byte();
    }

    virtual void reset()
    {
        //throwAccessException(__FUNCTION__, "reset not allowed");
    }

private:
    virtual void accept(LocationVisitor& visitor) const
    {
        visitor.visit(*this);
    }

    virtual void print(std::ostream& out) const
    {
        out << "--";
    }

    virtual int getApplicationCount() const
    {
        throwAccessException(__FUNCTION__, "no application count");
        return 0;
    }

    void throwAccessException(const std::string& function, const std::string& message) const
    {
        throw MemoryAccessException(std::string(typeid(this).name()) + ": " + function + ": Bad memory access: " + message);
    }

    friend class LocationAccess;
};

class ReadOnlyMemory : public Location
{
public:
    ReadOnlyMemory(Byte value)
        : value(value)
    {
    }

    int getApplicationCount() const override
    {
        return applicationCount;
    }

private:
    Byte read() override
    {
        return value;
    }

    Byte apply() override
    {
        ++applicationCount;
        return value;
    }

    void reset() override
    {
        applicationCount = 0;
    }

    void accept(LocationVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    void print(std::ostream& out) const override
    {
        out << value;
    }

private:
    const Byte value;
    int applicationCount = 0;
};

class ReadWriteMemory : public Location
{
public:
    ReadWriteMemory(Byte value)
        : value(value)
    {
    }

    int getApplicationCount() const override
    {
        return applicationCount;
    }

private:
    void write(Byte newValue) override
    {
        value = newValue;
    }

    Byte read() override
    {
        return value;
    }

    Byte apply() override
    {
        ++applicationCount;
        return value;
    }

    void reset() override
    {
        applicationCount = 0;
    }

    void accept(LocationVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    void print(std::ostream& out) const override
    {
        out << value;
    }

private:
    Byte value;
    int applicationCount = 0;
};

class Register : public Location
{
protected:
    Register()
    {
    }
};

class ReadRegister : public Register
{
public:
    ReadRegister(std::function<void(Byte&)> onRead)
        : onRead(onRead)
    {
    }

private:
    Byte read() override
    {
        if (onRead == nullptr) {
            return Register::read();
        } else {
            onRead(lastValue);
            return lastValue;
        }
    }

    void accept(LocationVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    void print(std::ostream& out) const override
    {
        out << lastValue;
    }

private:
    std::function<void(Byte&)> onRead;
    Byte lastValue;
};

class WriteRegister : public Register
{
public:
    WriteRegister(std::function<void(Byte, Byte)> onWrite)
        : onWrite(onWrite)
    {
    }

private:
    void write(Byte value) override
    {
        if (onWrite == nullptr) {
            Register::write(value);
        } else {
            onWrite(lastValue, value);
            lastValue = value;
        }
    }

    void accept(LocationVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    void print(std::ostream& out) const override
    {
        out << lastValue;
    }

private:
    std::function<void(Byte, Byte)> onWrite;
    Byte lastValue;
};

class ReadWriteRegister : public Register
{
public:
    ReadWriteRegister(std::function<void(Byte&)> onRead, std::function<void(Byte, Byte)> onWrite, Byte lastValue = Byte())
        : onRead(onRead)
        , onWrite(onWrite)
        , lastValue(lastValue)
    {
    }

    /*ReadWriteRegister(std::function<void(Byte&)> onRead, std::function<void(Byte, Byte)> onWrite)
        : onRead(onRead)
        , onWrite(onWrite)
    {
    }*/

private:
    Byte read() override
    {
        if (onRead == nullptr) {
            return Register::read();
        } else {
            Byte value;
            onRead(value);
            return value;
        }
    }

    void write(Byte value) override
    {
        if (onWrite == nullptr) {
            Register::write(value);
        } else {
            onWrite(lastValue, value);
            lastValue = value;
        }
    }

    void accept(LocationVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    void print(std::ostream& out) const override
    {
        out << lastValue;
    }

private:
    std::function<void(Byte&)> onRead;
    std::function<void(Byte, Byte)> onWrite;
    Byte lastValue;
};

class Access
{
public:
    Access() = default;

    Access(const Access&) = delete;
    Access& operator=(const Access&) = delete;

    virtual Byte readByte() = 0;
    virtual Word readWord() = 0;
    virtual Long readLong()
    {
        throw MemoryAccessException("Long read access is not implemented");
    }

    virtual void writeByte(Byte value) = 0;
    virtual void writeWord(Word value) = 0;
};

class LocationAccess : public Access
{
public:
    enum Operation
    {
        Read,
        Write,
        Apply
    };

    typedef std::function<void(Operation operation, Byte value, uint64_t applicationCount)> BreakpointCallback;

    virtual void accept(LocationVisitor& visitor) const = 0;

    virtual void print(std::ostream& out) const = 0;

    bool hasBreakpoint() const
    {
        return false;
    }

    void setBreakpoint(BreakpointCallback value)
    {

    }

protected:
    void writeLocation(Location* location, Byte newValue) const
    {
        location->write(newValue);
    }

    Byte readLocation(Location* location) const
    {
        return location->read();
    }

    Byte applyLocation(Location* location) const
    {
        return location->apply();
    }

    int getLocationApplicationCount(Location* location) const
    {
        return location->getApplicationCount();
    }

    void resetLocation(Location* location) const
    {
        location->reset();
    }

    void acceptLocation(Location* location, LocationVisitor& visitor) const
    {
        location->accept(visitor);
    }

    void printLocation(Location* location, std::ostream& out) const
    {
        return location->print(out);
    }
};

inline std::ostream& operator<<(std::ostream& out, const LocationAccess& access)
{
    access.print(out);
    return out;
}

template<typename AddressType>
class Memory : private LocationAccess
{
public:
    enum WrappingMask
    {
        Page = Byte::bitMask,
        Bank = Word::bitMask,
        Full = AddressType::bitMask
    };

    Memory()
        : Memory(AddressType::spaceSize)
    {
    }

    Memory(uint32_t size)
        : memory(size)
        , memorySize(size)
    {
    }

    uint32_t size() const
    {
        return memorySize;
    }

    template<typename LocationType, typename... Args>
    void createLocation(AddressType address, Args... args)
    {
        checkIsInitialized(address, false, __FUNCTION__);
        memory[address] = std::make_shared<LocationType>(args...);
    }

    void createMirror(AddressType mirror, AddressType origin)
    {
        checkIsInitialized(mirror, false, __FUNCTION__);
        if (std::shared_ptr<Location> location = memory[origin]) {
            memory[mirror] = location;
        }
    }

    void finalize()
    {
        for (std::shared_ptr<Location>& location : memory) {
            if (location.get() == nullptr) {
                location = std::make_shared<Location>();
            }
        }
    }

    template<WrappingMask Wrapping = Full, typename AccessType = Access>
    AccessType& getAccess(AddressType address)
    {
        currentWrappingMask = Wrapping;
        currentAddress = address;
        return static_cast<AccessType&>(*this);
    }

    Byte readByte(AddressType address)
    {
        Byte result;
        checkIsInitialized(address, true, __FUNCTION__);
        try {
            result = readLocation(memory[address].get());
        } catch (const MemoryAccessException& e) {
            handleAccessException(e, address);
        }
        return result;
    }

    template<WrappingMask Wrapping = Full>
    Word readWord(AddressType address)
    {
        return readWord(address, Wrapping);
    }

    Word readWord(AddressType lowAddress, uint32_t wrappingMask)
    {
        Byte lowByte = readByte(lowAddress);
        AddressType highAddress = getNextAddress(lowAddress, wrappingMask);
        Byte highByte = readByte(highAddress);
        return Word(lowByte, highByte);
    }

    template<WrappingMask Wrapping = Full>
    Long readLong(AddressType address)
    {
        return readLong(address, Wrapping);
    }

    Long readLong(AddressType lowAddress, uint32_t wrappingMask)
    {
        Byte lowByte = readByte(lowAddress);
        AddressType highAddress = getNextAddress(lowAddress, wrappingMask);
        Byte highByte = readByte(highAddress);
        AddressType bankAddress = getNextAddress(highAddress, wrappingMask);
        Byte bankByte = readByte(bankAddress);
        return Long(lowByte, highByte, bankByte);
    }

    void writeByte(Byte value, AddressType address)
    {
        checkIsInitialized(address, true, __FUNCTION__);
        try {
            return writeLocation(memory[address].get(), value);
        }
        catch (const MemoryAccessException& e) {
            handleAccessException(e, address);
        }
    }

    template<WrappingMask Wrapping = Full>
    void writeWord(Word value, AddressType address)
    {
        writeWord(value, address, Wrapping);
    }

    void writeWord(Word value, AddressType lowAddress, uint32_t wrappingMask)
    {
        writeByte(value.getLowByte(), lowAddress);
        AddressType highAddress = getNextAddress(lowAddress, wrappingMask);
        writeByte(value.getHighByte(), highAddress);
    }

    Byte applyByte(AddressType address) const
    {
        Byte result;
        checkIsInitialized(address, true, __FUNCTION__);
        try {
            result = applyLocation(memory[address].get());
        } catch (const MemoryAccessException& e) {
            handleAccessException(e, address);
        }
        return result;
    }

    void reset(AddressType address)
    {
        checkIsInitialized(address, true, __FUNCTION__);
        try {
            return resetLocation(memory[address].get());
        } catch (const MemoryAccessException& e) {
            handleAccessException(e, address);
        }
    }

    int getApplicationCount(AddressType address) const
    {
        checkIsInitialized(address, true, __FUNCTION__);
        return getLocationApplicationCount(memory[address].get());
    }

private:
    static AddressType getNextAddress(AddressType address, uint32_t wrappingMask)
    {
        return (address & ~wrappingMask) + ((address + 1) & wrappingMask);
    }

    Byte readByte() override
    {
        return readByte(currentAddress);
    }

    Word readWord() override
    {
        return readWord(currentAddress, currentWrappingMask);
    }

    Long readLong() override
    {
        return readLong(currentAddress, currentWrappingMask);
    }

    void writeByte(Byte value) override
    {
        writeByte(value, currentAddress);
    }

    void writeWord(Word value) override
    {
        writeWord(value, currentAddress, currentWrappingMask);
    }

    void accept(LocationVisitor& visitor) const override
    {
        checkIsInitialized(currentAddress, true, __FUNCTION__);
        acceptLocation(memory[currentAddress].get(), visitor);
    }

    void print(std::ostream& out) const override
    {
        checkIsInitialized(currentAddress, true, __FUNCTION__);
        printLocation(memory[currentAddress].get(), out);
    }

    void checkBounds(AddressType address, const char* operation) const
    {
        if (address >= memorySize) {
            std::ostringstream ss;
            ss << operation << ": ";
            ss << address << " is out of bounds, memory size is " << memorySize;
            throw MemoryAccessException(ss.str());
        }
    }

    void checkIsInitialized(AddressType address, bool shouldBeInitialized, const char* operation) const
    {
        checkBounds(address, operation);
        bool isInitialized = memory[address].get() != nullptr;
        if (isInitialized != shouldBeInitialized) {
            std::ostringstream ss;
            ss << operation << ": ";
            ss << "memory @" << address << " ";
            if (isInitialized) {
                ss << "is aready initialized";
            }
            else {
                ss << "is not initialized";
            }
            throw MemoryAccessException(ss.str());
        }
    }

    void handleAccessException(const MemoryAccessException& e, AddressType address) const
    {
        std::ostringstream ss;
        ss << " @" << address;
        throw MemoryAccessException(e.what() + ss.str());
    }

private:
    std::vector<std::shared_ptr<Location>> memory;
    uint32_t memorySize;
    AddressType currentAddress;
    uint32_t currentWrappingMask = 0;
};