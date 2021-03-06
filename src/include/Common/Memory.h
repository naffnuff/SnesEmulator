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
    virtual void visit(const class InvalidLocation&) = 0;
    virtual void visit(const class ReadOnlyMemory&) = 0;
    virtual void visit(const class ReadWriteMemory&) = 0;
    virtual void visit(const class ReadRegister&) = 0;
    virtual void visit(const class WriteRegister&) = 0;
    virtual void visit(const class ReadWriteRegister&) = 0;
};

class Location
{
public:
    enum Operation
    {
        Read,
        Write,
        Apply
    };

    typedef std::function<void(Operation operation, Byte value, uint64_t applicationCount)> BreakpointCallback;

    Location() = delete;

    Location(Byte& bus)
        : bus(bus)
    {
    }

    Location(const Location&) = delete;
    Location& operator=(const Location&) = delete;

public:
    Byte read()
    {
        readImpl(bus);
        if (breakpoint) {
            breakpoint(Read, bus, 0);
        }
        return bus;
    }

    Byte apply()
    {
        readImpl(bus);
        ++applicationCount;
        return bus;
    }

    void write(Byte value)
    {
        writeImpl(value);
        if (breakpoint) {
            breakpoint(Write, value, 0);
        }
    }

    uint64_t getApplicationCount() const
    {
        return applicationCount;
    }

    void reset()
    {
        applicationCount = 0;
    }

    bool hasBreakpoint() const
    {
        return breakpoint.operator bool();
    }

    void applyBreakpoint() const
    {
        if (breakpoint) {
            breakpoint(Apply, 0, applicationCount + 1);
        }
    }

    bool setBreakpoint(BreakpointCallback callback)
    {
        breakpoint = callback;
        return true;
    }

    virtual Byte inspect() const
    {
        throwAccessException(__FUNCTION__, "inspection not allowed");
        return Byte();
    }

    virtual void accept(LocationVisitor& visitor) const = 0;
    virtual void print(std::ostream& out) const = 0;

protected:
    virtual void readImpl(Byte& bus)
    {
        std::stringstream ss;
        ss << "reading not allowed, bus value=" << bus;
        throwAccessException(__FUNCTION__, ss.str());
    }

    virtual void writeImpl(Byte)
    {
        throwAccessException(__FUNCTION__, "writing not allowed");
    }

    void throwAccessException(const std::string& function, const std::string& message) const
    {
        throw MemoryAccessException(std::string(typeid(this).name()) + ": " + function + ": Bad memory access: " + message);
    }

private:
    Byte& bus;
    uint64_t applicationCount = 0;
    BreakpointCallback breakpoint;
};

class InvalidLocation : public Location
{
public:
    InvalidLocation(Byte& bus)
        : Location(bus)
    {
    }

private:
    void accept(LocationVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    void print(std::ostream& out) const override
    {
        out << "--";
    }
};

// Memory

class MemoryLocationX : public Location
{
public:
    MemoryLocationX(Byte& bus, Byte value)
        : Location(bus)
        , value(value)
    {
    }

private:
    void readImpl(Byte& bus) override
    {
        bus = value;
    }

    Byte inspect() const override
    {
        return value;
    }

    void print(std::ostream& out) const override
    {
        out << value;
    }

protected:
    Byte value;
};

class ReadOnlyMemory : public MemoryLocationX
{
public:
    ReadOnlyMemory(Byte& bus, Byte value)
        : MemoryLocationX(bus, value)
    {
    }

private:
    void accept(LocationVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

class ReadWriteMemory : public MemoryLocationX
{
public:
    ReadWriteMemory(Byte& bus, Byte value)
        : MemoryLocationX(bus, value)
    {
    }

private:
    void writeImpl(Byte newValue) override
    {
        value = newValue;
    }

    void accept(LocationVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

// Registers

class Register : public Location
{
protected:
    Register(Byte& bus)
        : Location(bus)
    {
    }
};

class ReadRegister : public Register
{
public:
    ReadRegister(Byte& bus, std::function<void(Byte&)> onRead)
        : Register(bus)
        , onRead(onRead)
    {
    }

private:
    void readImpl(Byte& bus) override
    {
        if (onRead == nullptr) {
            Register::readImpl(bus);
        } else {
            onRead(bus);
        }
        lastValue = bus;
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
    WriteRegister(Byte& bus, std::function<void(Byte, Byte)> onWrite)
        : Register(bus)
        , onWrite(onWrite)
    {
    }

private:
    void writeImpl(Byte value) override
    {
        if (onWrite == nullptr) {
            Register::writeImpl(value);
        } else {
            onWrite(lastValue, value);
        }
        lastValue = value;
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

class OpenBusWriteRegister : public WriteRegister
{
    using WriteRegister::WriteRegister;

private:
    void readImpl(Byte&) override
    {
    }
};

class VideoOpenBusWriteRegister : public WriteRegister
{
    using WriteRegister::WriteRegister;

private:
    void readImpl(Byte& bus) override
    {
        std::stringstream ss;
        ss << "VIDEO OPEN BUS REGISTER, bus value=" << bus;
        throwAccessException(__FUNCTION__, ss.str());
    }
};

class ReadWriteRegister : public Register
{
public:
    ReadWriteRegister(Byte& bus, std::function<void(Byte&)> onRead, std::function<void(Byte, Byte)> onWrite, Byte lastValue = Byte())
        : Register(bus)
        , onRead(onRead)
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
    void readImpl(Byte& bus) override
    {
        if (onRead == nullptr) {
            Register::readImpl(bus);
        } else {
            onRead(bus);
        }
    }

    void writeImpl(Byte value) override
    {
        if (onWrite == nullptr) {
            Register::writeImpl(value);
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
    virtual void accept(LocationVisitor& visitor) const = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual bool hasBreakpoint() const = 0;
    virtual bool setBreakpoint(Location::BreakpointCallback callback) = 0;
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
        memory[address] = std::make_shared<LocationType>(bus, args...);
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
                location = std::make_shared<InvalidLocation>(bus);
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
            result = memory[address]->read();
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
            return memory[address]->write(value);
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
            result = memory[address]->apply();
        } catch (const MemoryAccessException& e) {
            handleAccessException(e, address);
        }
        return result;
    }

    void reset(AddressType address)
    {
        checkIsInitialized(address, true, __FUNCTION__);
        try {
            return memory[address]->reset();
        } catch (const MemoryAccessException& e) {
            handleAccessException(e, address);
        }
    }

    uint64_t getApplicationCount(AddressType address) const
    {
        checkIsInitialized(address, true, __FUNCTION__);
        return memory[address]->getApplicationCount();
    }

    bool hasBreakpoint(AddressType address) const
    {
        checkIsInitialized(address, true, __FUNCTION__);
        return memory[address]->hasBreakpoint();
    }

    void applyBreakpoint(AddressType address) const
    {
        checkIsInitialized(address, true, __FUNCTION__);
        return memory[address]->applyBreakpoint();
    }

    Byte inspect(AddressType address)
    {
        Byte result;
        checkIsInitialized(address, true, __FUNCTION__);
        try {
            result = memory[address]->inspect();
        } catch (const MemoryAccessException& e) {
            handleAccessException(e, address);
        }
        return result;
    }

    void print(AddressType address, std::ostream& out) const
    {
        checkIsInitialized(address, true, __FUNCTION__);
        memory[address]->print(out);
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

    bool hasBreakpoint() const override
    {
        return hasBreakpoint(currentAddress);
    }

    bool setBreakpoint(Location::BreakpointCallback callback) override
    {
        checkIsInitialized(currentAddress, true, __FUNCTION__);
        return memory[currentAddress]->setBreakpoint(callback);
    }

    void accept(LocationVisitor& visitor) const override
    {
        checkIsInitialized(currentAddress, true, __FUNCTION__);
        memory[currentAddress]->accept(visitor);
    }

    void print(std::ostream& out) const override
    {
        print(currentAddress, out);
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
        if (shouldBeInitialized) {
            return;
        }
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
    
public:
    Byte bus;

private:
    std::vector<std::shared_ptr<Location>> memory;
    uint32_t memorySize;
    AddressType currentAddress;
    uint32_t currentWrappingMask = 0;
};