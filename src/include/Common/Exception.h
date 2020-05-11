#pragma once

#include <stdexcept>
#include <sstream>

#define EXCEPTION(NAME, BASE) \
class NAME : public BASE \
{ \
public: \
    template<typename... Ts> \
    NAME(const Ts&... message) \
        : BASE(__FUNCTION__, message...) \
    { \
    } \
};

class Exception : public std::runtime_error
{
protected:
    template<typename... Ts>
    Exception(const Ts&... message)
        : std::runtime_error(toString(message...))
    {
    }

    Exception() = delete;

    Exception(const Exception&) = delete;
    Exception& operator=(const Exception&) = delete;

    template<typename... Ts>
    std::string toString(const Ts&... message)
    {
        std::stringstream ss;
        (ss << ... << message);
        return ss.str();
    }
};

EXCEPTION(AccessException, Exception)
EXCEPTION(NotYetImplementedException, Exception)
EXCEPTION(RuntimeError, Exception)
