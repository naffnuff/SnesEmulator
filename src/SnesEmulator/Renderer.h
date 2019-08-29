#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <mutex>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderer
{
public:
    typedef uint16_t Pixel;

    Renderer(int windowXPosition, int windowYPosition, int width, int height, float scale, bool syncUpdate, std::ostream& output)
        : windowXPosition(windowXPosition)
        , windowYPosition(windowYPosition)
        , width(width)
        , height(height)
        , scale(scale)
        , syncUpdate(syncUpdate)
        , pixelBuffer(height* width)
        , output(output)
        , title("SNES Emulator")
    {
    }

    ~Renderer()
    {
        output << "Renderer " << title << " destructor" << std::endl;
        glfwTerminate();
    }

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    void initialize(bool fullscreen = false, bool aspectCorrection = false);
    void setWindowProperties(bool fullscreen, bool aspectCorrection);
    void update();
    bool isRunning() const;

    double getTime() const
    {
        return glfwGetTime();
    }

    void setScanline(int lineIndex, const std::vector<Pixel>& pixels)
    {
        for (int i = 0; i < pixels.size(); ++i) {
            setPixel(lineIndex, i, pixels[i]);
        }
    }

    void setPixel(int row, int column, Pixel pixel)
    {
        row = height - 1 - row;
        int index = row * width + column;
        if (index < 0 || index >= pixelBuffer.size()) {
            throw std::logic_error("Renderer: Index out of bounds in pixel buffer");
        }
        pixelBuffer[index] = pixel;
    }

    void setGrayscalePixel(int row, int column, uint8_t white)
    {
        uint8_t white5Bit = white >> 3;
        Pixel pixel = white5Bit << 0 | white5Bit << 5 | white5Bit << 10;
        setPixel(row, column, pixel);
    }

    void setGrayscaleTile(int startRow, int startColumn, const std::array<std::array<uint8_t, 8>, 8>& tile, int bitsPerPixel)
    {
        for (int row = 0; row < 8; ++row) {
            for (int column = 0; column < 8; ++column) {
                setGrayscalePixel(startRow + row, startColumn + column, tile[row][column] * (bitsPerPixel == 2 ? 85 : 17));
            }
        }
    }

    void clearDisplay(uint16_t clearColor)
    {
        for (int row = 0; row < height; ++row) {
            for (int column = 0; column < width; ++column) {
                setPixel(row, column, clearColor);
            }
        }
    }

    void clearScanline(int vCounter, uint16_t clearColor)
    {
        for (int column = 0; column < width; ++column) {
            setPixel(vCounter, column, clearColor);
        }
    }

    bool isPressed(int key) const
    {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }

    void focusWindow() const
    {
        glfwFocusWindow(window);
    }

public:
    bool pauseRequested = false;
    bool toggleFullscreenRequested = false;

    bool buttonStart = false;
    bool buttonSelect = false;
    bool buttonA = false;
    bool buttonB = false;
    bool buttonX = false;
    bool buttonY = false;
    bool buttonL = false;
    bool buttonR = false;
    bool buttonUp = false;
    bool buttonDown = false;
    bool buttonLeft = false;
    bool buttonRight = false;

    int windowXPosition;
    int windowYPosition;
    
    const int width;
    const int height;

    std::vector<Pixel> pixelBuffer;
    std::mutex pixelBufferMutex;

    std::ostream& output;

    GLFWwindow* window;

    std::string title;

    float scale;
    float xScale;
    float yScale;
    float xScreenCoverage;
    const bool syncUpdate;

    int pressKeyTimeout = 0;
};