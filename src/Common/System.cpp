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