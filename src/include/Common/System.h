#pragma once

#include <filesystem>

#ifdef _WIN32
#define SHARED __declspec(dllexport)
#else
#define SHARED
#endif

namespace System {

void focusConsoleWindow();

const std::filesystem::path& getRomLibraryPath();

}