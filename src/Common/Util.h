#pragma once

#include <sstream>

#ifndef _WIN32
#define min(a,b) std::min(a,b)
#define max(a,b) std::max(a,b)
#endif
 
namespace Util {

template<typename T>
std::string toString(const T& value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

}