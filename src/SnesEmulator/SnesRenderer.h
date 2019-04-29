#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "SnesEmulator.h"

namespace Nox {

class Renderer
{
public:
    Renderer(Emulator& emulator);
    ~Renderer();
    void initialize();
    void update();
    bool isRunning() const;

private:
    void setPixel(int row, int column, GLubyte red, GLubyte green, GLubyte blue);

private:
    GLFWwindow* window;

    Emulator& emulator;
    std::map<Word, MemoryLocation> registers;

    static const int width = 256;
    static const int height = 224;
    static const int scale = 3;

    std::vector<GLubyte> pixelBuffer;
};

}