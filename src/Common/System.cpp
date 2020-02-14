#include "System.h"

namespace System {

#ifdef _WIN32
void setOutputColor(std::ostream&, Color color, bool bright)
{
    int effectiveColor = color;
    if (bright) {
        effectiveColor |= FOREGROUND_INTENSITY;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), effectiveColor);
}

void focusConsoleWindow()
{
    if (HWND window = GetConsoleWindow()) {
        SetForegroundWindow(window);
    }
}
#else
void setOutputColor(std::ostream& output, Color color, bool bright)
{
    output << "\33[" << color;
    if (bright) {
        output << ";" << 1;
    }
    output << "m";
}
#endif

ScopedOutputColor::ScopedOutputColor(std::ostream& output)
    : output(output)
{
}

ScopedOutputColor::ScopedOutputColor(std::ostream& output, Color color, bool bright)
    : output(output)
{
    set(color, bright);
}

ScopedOutputColor::~ScopedOutputColor()
{
    setOutputColor(output, DefaultColor, false);
}

void ScopedOutputColor::set(Color color, bool bright)
{
    setOutputColor(output, color, bright);
}

}