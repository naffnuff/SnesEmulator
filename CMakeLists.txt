cmake_minimum_required(VERSION 3.20)
project(SnesEmulator VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# --- PortAudio ---
FetchContent_Declare(
  portaudio
  GIT_REPOSITORY https://github.com/PortAudio/portaudio.git
  GIT_TAG        147dd722548358763a8b649b3e4b41dfffbcfbb6
)
set(PA_USE_ALSA ON CACHE BOOL "" FORCE)
set(PA_USE_PULSEAUDIO ON CACHE BOOL "" FORCE)
set(PA_BUILD_STATIC ON CACHE BOOL "" FORCE)

# --- GLFW ---
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.8
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# --- GLAD ---
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        v0.1.36
)

FetchContent_MakeAvailable(portaudio glfw glad)

# System dependencies
find_package(OpenGL REQUIRED)
find_package(ALSA REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Common
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    OpenGL::GL
    glad
    glfw
    portaudio_static
    ${ALSA_LIBRARIES}
)

# Symlink compile_commands.json to the project root
if(CMAKE_EXPORT_COMPILE_COMMANDS)
  set(SOURCE_CDB "${CMAKE_BINARY_DIR}/compile_commands.json")
  set(TARGET_CDB "${CMAKE_SOURCE_DIR}/compile_commands.json")

  message(STATUS "Linking compile_commands.json: ${TARGET_CDB} -> ${SOURCE_CDB}")

  execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink "${SOURCE_CDB}" "${TARGET_CDB}"
    )
endif()
