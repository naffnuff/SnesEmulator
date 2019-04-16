# CMakeList.txt : CMake project for SnesEmulator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories ("../../../../src/include/WDC65816/" "../../../../src/include/Common/")

# Add source to this project's executable.
add_library (WDC65816 STATIC "../../../../src/WDC65816/CpuInstructionDecoder.cpp")

set_target_properties (WDC65816 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# TODO: Add tests and install targets if needed.
