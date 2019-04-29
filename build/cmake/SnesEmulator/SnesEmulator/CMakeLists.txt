# CMakeList.txt : CMake project for SnesEmulator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories ("../../../../src/include/" "../../../../src/include/Common/")

# Add source to this project's executable.
add_executable (SnesEmulator
    "../../../../src/SnesEmulator/Main.cpp"
    "../../../../src/SnesEmulator/SnesEmulator.cpp"
    "../../../../src/SnesEmulator/SnesRenderer.cpp"
)

target_link_libraries (SnesEmulator WDC65816 SPC700)

# TODO: Add tests and install targets if needed.
