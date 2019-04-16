# CMakeList.txt : CMake project for SnesEmulator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories ("../../../../src/include/SPC700/" "../../../../src/include/Common/")

# Add source to this project's executable.
add_library (SPC700 STATIC "../../../../src/SPC700/SpcInstructionDecoder.cpp")

# TODO: Add tests and install targets if needed.
