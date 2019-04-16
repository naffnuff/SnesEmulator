# CMakeList.txt : CMake project for SnesEmulator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories ("../../../../src/include/SPC700/" "../../../../src/include/Common/")

# Add source to this project's executable.
add_library (SPC700 STATIC "../../../../src/SPC700/SpcInstructionDecoder.cpp")

set_target_properties (SPC700 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# TODO: Add tests and install targets if needed.
