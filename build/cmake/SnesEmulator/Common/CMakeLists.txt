# CMakeList.txt : CMake project for SnesEmulator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories ("../../../../src/include/Common/")

# Add source to this project's executable.
add_library (Common STATIC "../../../../src/Common/System.cpp")

# TODO: Add tests and install targets if needed.
