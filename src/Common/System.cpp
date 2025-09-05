#include "System.h"

#include <iostream>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#define SHARED __declspec(dllexport)
#else
#define SHARED
#endif

namespace System {

namespace {
std::filesystem::path romLibraryPath;
std::filesystem::path workingDirectory = ".";
}

void focusConsoleWindow()
{
#ifdef _WIN32
    if (HWND window = GetConsoleWindow()) {
        SetForegroundWindow(window);
    }
#endif
}

const std::filesystem::path& getRomLibraryPath()
{
    if (romLibraryPath.empty())
    {
        std::filesystem::path path = workingDirectory;

        while (!std::filesystem::exists(path / "SnesRoms"))
        {
            if (path == path.root_path())
            {
                return workingDirectory;
            }

            path = std::filesystem::absolute(path / "..");
        }

        romLibraryPath = path / "SnesRoms";
    }

    return romLibraryPath;
}

}