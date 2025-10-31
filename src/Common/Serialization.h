#pragma once

#include <iostream>

// Bool

inline void serializeOne(std::ostream& out, const bool& value)
{
	const uint8_t intValue = value ? 1 : 0;
	out.write(reinterpret_cast<const char*>(&intValue), sizeof(intValue));
}

inline void deserializeOne(std::istream& in, bool& value)
{
	uint8_t intValue;
	in.read(reinterpret_cast<char*>(&intValue), sizeof(intValue));
	value = intValue != 0;
}

// Arithmetic types

template <typename Type>
requires std::is_arithmetic_v<Type>
void serializeOne(std::ostream& out, const Type& value)
{
	out.write(reinterpret_cast<const char*>(&value), sizeof(Type));
}

template <typename Type>
requires std::is_arithmetic_v<Type>
void deserializeOne(std::istream& in, Type& value)
{
	in.read(reinterpret_cast<char*>(&value), sizeof(Type));
}

// Recursive types

template<typename Type, typename = std::void_t<>>
struct hasSave : std::false_type {};

template<typename Type>
struct hasSave<Type, std::void_t<
	decltype(std::declval<const Type&>().save(std::declval<std::ostream&>()))
>> : std::true_type {};

template<typename Type>
requires hasSave<Type>::value
inline auto serializeOne(std::ostream& out, const Type& object)
{
	object.save(out);
}

template<typename Type, typename = std::void_t<>>
struct hasLoad : std::false_type {};

template<typename Type>
struct hasLoad<Type, std::void_t<
	decltype(std::declval<Type&>().load(std::declval<std::istream&>()))
	>> : std::true_type {};

template<typename Type>
requires hasLoad<Type>::value
inline auto deserializeOne(std::istream& in, Type& object)
{
	object.load(in);
}

// Entry point

template <typename... Types>
inline void serialize(std::ostream& out, const Types&... fields)
{
	(serializeOne(out, fields), ...);
}

template <typename... Types>
inline void deserialize(std::istream& in, Types&... fields)
{
	(deserializeOne(in, fields), ...);
}

#define SAVE(...) \
public: \
	void save(std::ostream& out) const { serialize(out, __VA_ARGS__); } \
	void load(std::istream& in) { deserialize(in, __VA_ARGS__); }