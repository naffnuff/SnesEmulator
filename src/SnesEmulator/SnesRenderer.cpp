#include "SnesRenderer.h"

#include <cmath>

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>

#include "Common/System.h"

namespace Nox {

//typedef std::vector<std::vector<float>> Float4x4;

//GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
//Float4x4 rotationZ(float angle);

void Renderer::initialize()
{
    // Initialise GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    //glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    // Open a window and create its OpenGL context
    std::string romTitle = emulator.getRomTitle();
    window = glfwCreateWindow(width * scale, height * scale, romTitle.c_str(), NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to open GLFW window.");
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowPos(window, 1000, 40);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLEW");
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glfwSwapInterval(1);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void Renderer::setPixel(int row, int column, GLubyte red, GLubyte green, GLubyte blue)
{
    row = height - 1 - row;
    for (int i = 0; i < scale; ++i) {
        for (int j = 0; j < scale; ++j) {
            int index = (row * scale + i) * width * scale * 3 + (column * scale + j) * 3;
            pixelBuffer[index] = red;
            pixelBuffer[index + 1] = green;
            pixelBuffer[index + 2] = blue;
        }
    }
}

void Renderer::update()
{
    static double previousTime = glfwGetTime();
    static int frameCount = 0;

    // Measure speed
    double currentTime = glfwGetTime();
    frameCount++;
    // If a second has passed.
    if (currentTime - previousTime >= 1.0) {
        // Display the frame count here any way you want.
        output << frameCount << std::endl;

        frameCount = 0;
        previousTime = currentTime;
    }

    if (registers[0x4200].getValue().getBit(7)) {
        output << "Initiating VBlank" << std::endl;
        double before = glfwGetTime();
        emulator.initiateVBlank();
        double after = glfwGetTime();
        output << "VBlank ended after" << after - before << " seconds" << std::endl;
    }

    static int row = 0;
    static int col = 0;
    static Byte color = 255;
    static bool ascending = false;
    while (true) {
        if (col >= width) {
            ++row;
            col = 0;
            if (row >= height) {
                row = 0;
                if (ascending) {
                    ++color;
                    if (color == 255) {
                        ascending = false;
                    }
                }
                else {
                    --color;
                    if (color == 0) {
                        ascending = true;
                    }
                }
                break;
            }
        }
        setPixel(row, col, row, col, color);
        ++col;
    }

    static float angle = 0.0f;

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos2i(-1, -1);
    glDrawPixels(width * scale, height * scale, GL_RGB, GL_UNSIGNED_BYTE, pixelBuffer.data());
    glFlush();

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        emulator.pause();
    }
}

bool Renderer::isRunning() const
{
    return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0;
}

}