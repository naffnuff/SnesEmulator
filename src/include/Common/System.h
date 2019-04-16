#pragma once

#ifdef _WIN32
#define SHARED __declspec(dllexport)
#else
#define SHARED
#endif
