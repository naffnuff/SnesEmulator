#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "SnesEmulator.h"

namespace Nox {

class Renderer
{
public:
    Renderer(Emulator& emulator, std::ostream& output, std::istream& input, std::ostream& error)
        : emulator(emulator)
        , pixelBuffer(height * 3 * scale * width * 3 * scale)
        , output(output)
        , input(input)
        , error(error)
    {
        emulator.initializeSPPURegisters(registers);
    }

    ~Renderer()
    {
        output << "Renderer destructor start" << std::endl;
        glfwTerminate();
        output << "Renderer destructor end" << std::endl;
    }

    Renderer(Renderer&) = delete;
    Renderer& operator=(Renderer&) = delete;

    void initialize();
    void update();
    bool isRunning() const;

private:
    void setPixel(int row, int column, GLubyte red, GLubyte green, GLubyte blue);

private:
    std::ostream& output;
    std::istream& input;
    std::ostream& error;

    GLFWwindow* window;

    Emulator& emulator;
    std::map<Word, MemoryLocation> registers;

    static const int width = 256;
    static const int height = 224;
    int scale = 1;

    std::vector<GLubyte> pixelBuffer;
};

}