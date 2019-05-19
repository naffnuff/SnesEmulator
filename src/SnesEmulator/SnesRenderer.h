#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderer
{
public:
    typedef uint16_t Pixel;

    Renderer(int width, int height, float scale, bool syncUpdate, std::ostream& output)
        : width(width)
        , height(height)
        , scale(scale)
        , syncUpdate(syncUpdate)
        , pixelBuffer(height * width)
        , output(output)
    {
    }

    ~Renderer()
    {
        output << "Renderer " << title << " destructor" << std::endl;
        glfwTerminate();
    }

    Renderer(Renderer&) = delete;
    Renderer& operator=(Renderer&) = delete;

    void initialize(const std::string& windowTitle);
    void setScanline(int lineIndex, const std::vector<Pixel>& pixels);
    void setPixel(int row, int column, Pixel pixel);
    void setGrayscalePixel(int row, int column, uint8_t white);
    void setGrayscaleTile(int startRow, int startColumn, const std::array<std::array<uint8_t, 8>, 8>& tile, int bitsPerPixel);
    void update();
    bool isRunning() const;

    double getTime()
    {
        return glfwGetTime();
    }

    void clearDisplay(uint16_t clearColor)
    {
        std::fill(pixelBuffer.begin(), pixelBuffer.end(), clearColor);
    }

public:
    bool pause = false;
    
    const int width;
    const int height;

private:
    std::ostream& output;

    GLFWwindow* window;

    std::string title;

    const float scale;
    const bool syncUpdate;

    std::vector<Pixel> pixelBuffer;
};