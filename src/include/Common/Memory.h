#pragma once

#include <memory>
#include <functional>
#include <vector>
#include <sstream>

#include "Exception.h"
#include "Types.h"

class LocationVisitor
{
public:
    virtual void visit(const class InvalidLocation&) = 0;
    virtual void visit(const class ReadOnlyMemory&) = 0;
    virtual void visit(const class ReadWriteMemory&) = 0;
    virtual void visit(const class ReadRegister&) = 0;
    virtual void visit(const class WriteRegister&) = 0;
    virtual void visit(const class ReadWriteRegister&) = 0;
    virtual void visit(const class BootRomLocation&) = 0;
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
        const Byte value = readImpl(bus);
        if (breakpoint) {
            breakpoint(Read, value, 0);
        }
        return value;
    }

    Byte apply()
    {
        const Byte value = readImpl(bus);
        ++applicationCount;
        return value;
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
    virtual Byte readImpl(Byte& bus)
    {
        throwAccessException(__FUNCTION__, "reading not allowed, bus value=", bus);
        return bus;
    }

    virtual void writeImpl(Byte)
    {
        throwAccessException(__FUNCTION__, "writing not allowed");
    }

    template<typename... Ts>
    void throwAccessException(const std::string& function, const Ts&... message) const
    {
        throw AccessException(typeid(this).name(), ": ", function, ": Bad memory access: ", message...);
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

class MemoryLocation : public Location
{
public:
    MemoryLocation(Byte& bus, Byte value)
        : Location(bus)
        , value(value)
    {
    }

private:
    Byte readImpl(Byte& bus) override
    {
        bus = value;
        return value;
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

class ReadOnlyMemory : public MemoryLocation
{
public:
    ReadOnlyMemory(Byte& bus, Byte value)
        : MemoryLocation(bus, value)
    {
    }

private:
    void accept(LocationVisitor& visitor) const override
    {
        visitor.visit(*this);
    }
};

class ReadWriteMemory : public MemoryLocation
{
public:
    ReadWriteMemory(Byte& bus, Byte value)
        : MemoryLocation(bus, value)
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
    ReadRegister(Byte& bus, std::function<void(Byte&)> onRead, bool throwOnWrite)
        : Register(bus)
        , onRead(onRead)
        , throwOnWrite(throwOnWrite)
    {
    }

private:
    Byte readImpl(Byte& bus) override
    {
        Byte value;
        if (onRead == nullptr) {
            value = Register::readImpl(bus);
        } else {
            onRead(value);
        }
        lastValue = value;
        bus = value;
        return value;
    }

    void writeImpl(Byte) override
    {
        if (throwOnWrite) {
            throwAccessException(__FUNCTION__, "writing not allowed");
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
    const bool throwOnWrite = true;
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
    Byte readImpl(Byte& bus) override
    {
        return bus;
    }
};

class VideoOpenBusWriteRegister : public WriteRegister
{
    using WriteRegister::WriteRegister;

private:
    Byte readImpl(Byte& bus) override
    {
        std::stringstream ss;
        ss << "VIDEO OPEN BUS REGISTER, bus value=" << bus;
        throwAccessException(__FUNCTION__, ss.str());
        return bus;
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

private:
    Byte readImpl(Byte& bus) override
    {
        Byte value;
        if (onRead == nullptr) {
            value = Register::readImpl(bus);
        } else {
            value = 0xfa;
            onRead(value);
        }
        bus = value;
        return value;
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

class BootRomLocation : public Location
{
public:
    BootRomLocation(Byte& bus, Byte ramValue, Byte bootRomValue, bool& bootRomDataEnabled)
        : Location(bus)
        , ramValue(ramValue)
        , bootRomValue(bootRomValue)
        , bootRomDataEnabled(bootRomDataEnabled)
    {
    }

private:
    Byte readImpl(Byte& bus) override
    {
        Byte value;
        if (bootRomDataEnabled) {
            value = bootRomValue;
        } else {
            value = ramValue;
        }
        bus = value;
        return value;
    }

    void writeImpl(Byte newValue) override
    {
        ramValue = newValue;
    }

    Byte inspect() const override
    {
        if (bootRomDataEnabled) {
            return bootRomValue;
        } else {
            return ramValue;
        }
    }

    void accept(LocationVisitor& visitor) const override
    {
        visitor.visit(*this);
    }

    void print(std::ostream& out) const override
    {
        if (bootRomDataEnabled) {
            out << bootRomValue;
        } else {
            out << ramValue;
        }
    }

public:
    bool& bootRomDataEnabled;
private:
    Byte bootRomValue;
    Byte ramValue;
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
        throw AccessException("Long read access is not implemented");
    }

    virtual void writeByte(Byte value) = 0;
    virtual void writeWord(Word value) = 0;
};

class LocationAccess : public Access
{
public:
    virtual bool setBreakpoint(Location::BreakpointCallback callback) = 0;
    virtual bool hasBreakpoint() const = 0;
};

class ConstLocationAccess
{
public:
    virtual void accept(LocationVisitor& visitor) const = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual bool hasBreakpoint() const = 0;
};

inline std::ostream& operator<<(std::ostream& out, const ConstLocationAccess& access)
{
    access.print(out);
    return out;
}

template<typename AddressType>
class Memory
{
public:
    typedef AddressType AddressType;

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

    Memory(const Memory&) = delete;
    Memory& operator=(const Memory&) = delete;

    uint32_t size() const
    {
        return memorySize;
    }

    template<typename LocationType, typename... Args>
    void createLocation(AddressType address, Args&&... args)
    {
        checkIsInitialized(address, false, __FUNCTION__);
        memory[address] = std::make_shared<LocationType>(bus, std::forward<Args>(args)...);
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

    Byte readByte(AddressType address)
    {
        Byte result;
        checkIsInitialized(address, true, __FUNCTION__);
        try {
            result = memory[address]->read();
        } catch (const AccessException& e) {
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
        catch (const AccessException& e) {
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
        } catch (const AccessException& e) {
            handleAccessException(e, address);
        }
        return result;
    }

    void reset(AddressType address)
    {
        checkIsInitialized(address, true, __FUNCTION__);
        try {
            return memory[address]->reset();
        } catch (const AccessException& e) {
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

    Byte inspect(AddressType address) const
    {
        Byte result;
        checkIsInitialized(address, true, __FUNCTION__);
        try {
            result = memory[address]->inspect();
        } catch (const AccessException& e) {
            handleAccessException(e, address);
        }
        return result;
    }

    bool setBreakpoint(AddressType address, Location::BreakpointCallback callback)
    {
        checkIsInitialized(address, true, __FUNCTION__);
        return memory[address]->setBreakpoint(callback);
    }

    void accept(AddressType address, LocationVisitor& visitor) const
    {
        checkIsInitialized(address, true, __FUNCTION__);
        memory[address]->accept(visitor);
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

    void checkBounds(AddressType address, const char* operation) const
    {
        if (address >= memorySize) {
            std::ostringstream ss;
            ss << operation << ": ";
            ss << address << " is out of bounds, memory size is " << memorySize;
            throw AccessException(ss.str());
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
            throw AccessException(ss.str());
        }
    }

    void handleAccessException(const AccessException& e, AddressType address) const
    {
        std::ostringstream ss;
        ss << " @" << address;
        throw AccessException(e.what() + ss.str());
    }
    
public:
    Byte bus;

private:
    std::vector<std::shared_ptr<Location>> memory;
    const uint32_t memorySize;
};

template<typename Memory>
class MemoryAccess : public LocationAccess
{
public:
    //typedef typename Memory::AddressType AddressType;
    //typedef typename Memory::WrappingMask WrappingMask;
    using AddressType = typename Memory::AddressType;
    using WrappingMask = typename Memory::WrappingMask;

    MemoryAccess() = delete;

    MemoryAccess(Memory& memory, AddressType address, WrappingMask wrapping = Memory::Full)
        : memory(memory)
        , address(address)
        , wrapping(wrapping)
    {
    }

    Byte readByte() override
    {
        return memory.readByte(address);
    }

    Word readWord() override
    {
        return memory.readWord(address, wrapping);
    }

    Long readLong() override
    {
        return memory.readLong(address, wrapping);
    }

    void writeByte(Byte value) override
    {
        memory.writeByte(value, address);
    }

    void writeWord(Word value) override
    {
        memory.writeWord(value, address, wrapping);
    }

    bool setBreakpoint(Location::BreakpointCallback callback) override
    {
        return memory.setBreakpoint(address, callback);
    }

    bool hasBreakpoint() const override
    {
        return memory.hasBreakpoint(address);
    }

private:
    Memory& memory;
    const AddressType address;
    const WrappingMask wrapping;
};

template<typename Memory>
class ConstMemoryAccess : public ConstLocationAccess
{
public:
    //typedef typename Memory::AddressType AddressType;
    //typedef typename Memory::WrappingMask WrappingMask;
    using AddressType = typename Memory::AddressType;
    using WrappingMask = typename Memory::WrappingMask;

    ConstMemoryAccess() = delete;

    ConstMemoryAccess(const Memory& memory, AddressType address, WrappingMask wrapping = Memory::Full)
        : memory(memory)
        , address(address)
        , wrapping(wrapping)
    {
    }

    bool hasBreakpoint() const override
    {
        return memory.hasBreakpoint(address);
    }

    void accept(LocationVisitor& visitor) const override
    {
        memory.accept(address, visitor);
    }

    void print(std::ostream& out) const override
    {
        memory.print(address, out);
    }

private:
    const Memory& memory;
    const AddressType address;
    const WrappingMask wrapping;
};
