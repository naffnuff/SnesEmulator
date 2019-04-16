# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("SnesEmulator")

# Include sub-projects.
add_subdirectory ("WDC65816")
add_subdirectory ("SPC700")
add_subdirectory ("SnesEmulator")
