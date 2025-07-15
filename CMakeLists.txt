cmake_minimum_required(VERSION 3.20)
project(SnesEmulator VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(portaudio CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Common
)

# Platform-specific portaudio linking
if(WIN32)
    # Windows uses portaudio (dynamic) or portaudio_static if available
    if(TARGET portaudio_static)
        set(PORTAUDIO_TARGET portaudio_static)
        message(STATUS "Using portaudio_static on Windows")
    else()
        set(PORTAUDIO_TARGET portaudio)
        message(STATUS "Using portaudio on Windows")
    endif()
else()
    # Linux uses portaudio_static
    set(PORTAUDIO_TARGET portaudio_static)
    message(STATUS "Using portaudio_static on Linux")
endif()

target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    glfw
    ${PORTAUDIO_TARGET}
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})