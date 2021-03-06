#include "System.h"
#include "MemoryLocation.h"

uint64_t MemoryLocation::maxApplicationCount;

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

}