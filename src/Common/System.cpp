#include "System.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#define SHARED __declspec(dllexport)
#else
#define SHARED
#endif

namespace System {

void focusConsoleWindow()
{
#ifdef _WIN32
    if (HWND window = GetConsoleWindow()) {
        SetForegroundWindow(window);
    }
#endif
}

}