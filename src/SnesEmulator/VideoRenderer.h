#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <mutex>

#include "Common/Output.h"

struct GLFWwindow;
struct GLFWvidmode;

namespace Video {

class Renderer
{
public:
    typedef uint16_t Pixel;

    Renderer(int windowXPosition, int windowYPosition, int width, int height, float scale, bool syncUpdate, Output& output)
        : output(output, "video")
        , windowXPosition(windowXPosition)
        , windowYPosition(windowYPosition)
        , width(width)
        , height(height)
        , scale(scale)
        , syncUpdate(syncUpdate)
        , pixelBuffer(size_t(height* width))
        , title("SNES Emulator")
    {
    }

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    ~Renderer();

    void initialize(bool fullscreen = false, bool aspectCorrection = false);
    void terminate();
    float getAspectCorrectionFactor(bool aspectCorrection) const;
    void calculateScale(const GLFWvidmode* mode, bool aspectCorrection);
    void setWindowProperties(bool fullscreen, bool aspectCorrection);
    void update();
    bool isRunning() const;
    double getTime() const;
    void setScanline(int lineIndex, const std::vector<Pixel>& pixels);
    void setPixel(int row, int column, Pixel pixel);
    void setGrayscalePixel(int row, int column, uint8_t white);
    void setGrayscaleTile(int startRow, int startColumn, const std::array<std::array<uint8_t, 8>, 8> & tile, int bitsPerPixel);
    void clearDisplay(uint16_t clearColor);
    void clearScanline(int vCounter, uint16_t clearColor);
    bool isPressed(int key) const;
    void focusWindow(bool value);



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

    Output output;

    GLFWwindow* window = nullptr;

    std::string title;

    float scale;
    float xScale;
    float yScale;
    float xScreenCoverage;
    float yScreenCoverage;
    const bool syncUpdate;

    int pressKeyTimeout = 0;

    bool focusWindowRequested = false;
};

}