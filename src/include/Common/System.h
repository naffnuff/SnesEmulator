#pragma once

#include <ostream>

#ifdef _WIN32
#include <windows.h>
#define SHARED __declspec(dllexport)
#else
#define SHARED
#endif

namespace System {

#ifdef _WIN32
enum Color
{
    Red = FOREGROUND_RED,
    Green = FOREGROUND_GREEN,
    Yellow = FOREGROUND_RED | FOREGROUND_GREEN,
    Blue = FOREGROUND_BLUE,
    Magenta = FOREGROUND_RED | FOREGROUND_BLUE,
    Cyan = FOREGROUND_BLUE | FOREGROUND_GREEN,
    DefaultColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
};
#else
enum Color
{
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    DefaultColor = 0
};
#endif

void setOutputColor(std::ostream& output, Color color, bool bright);
void focusConsoleWindow();

}