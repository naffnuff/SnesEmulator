#include "Renderer.h"

#include <cmath>

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>

#include "Common/System.h"

void Renderer::initialize(const std::string& windowTitle)
{
    title = windowTitle;

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
    window = glfwCreateWindow(width * int(scale), height * int(scale), windowTitle.c_str(), NULL, NULL);
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

    if (syncUpdate) {
        glfwSwapInterval(1);
    }

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void Renderer::setScanline(int lineIndex, const std::vector<Pixel>& pixels)
{
    for (int i = 0; i < pixels.size(); ++i) {
        setPixel(lineIndex, i, pixels[i]);
    }
}

void Renderer::setPixel(int row, int column, Pixel pixel)
{
    row = height - 1 - row;
    pixelBuffer[row * width + column] = pixel;
}

void Renderer::setGrayscalePixel(int row, int column, uint8_t white)
{
    uint8_t white5Bit = white >> 3;
    Pixel pixel = white5Bit << 0 | white5Bit << 5 | white5Bit << 10;
    setPixel(row, column, pixel);
}

void Renderer::setGrayscaleTile(int startRow, int startColumn, const std::array<std::array<uint8_t, 8>, 8>& tile, int bitsPerPixel)
{
    for (int row = 0; row < 8; ++row) {
        for (int column = 0; column < 8; ++column) {
            setGrayscalePixel(startRow + row, startColumn + column, tile[row][column] * (bitsPerPixel == 2 ? 85 : 17));
        }
    }
}

void Renderer::update()
{
    if (!syncUpdate) {
        static double previousTime = glfwGetTime();
        static int frameCount = 0;

        // Measure speed
        double currentTime = glfwGetTime();
        frameCount++;
        // If a second has passed.
        if (currentTime - previousTime >= 1.0) {
            output << frameCount << std::endl;

            frameCount = 0;
            previousTime = currentTime;
        }
    }

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos2i(-1, -1);
    glPixelZoom(scale, scale);
    glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, pixelBuffer.data());
    glFlush();

    // Swap buffers
    glfwSwapBuffers(window);
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        pause = true;
    }
}

bool Renderer::isRunning() const
{
    return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0;
}
