#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <mutex>

#include "Common/Output.h"

#include "Shader.h"

struct GLFWmonitor;
struct GLFWwindow;
struct GLFWvidmode;

namespace Video {

class Renderer
{
public:
    typedef uint16_t Pixel;

    Renderer(int windowXPosition, int windowYPosition, int width, int height, float scale, bool syncUpdate, Output& output);

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    ~Renderer();

    double getTime() const;
    void focusWindow(bool value);
    void swapPixelBuffers();
    unsigned int getTexture() const { return texture; }

private:
    // setup
    void initialize(bool fullscreen = false);

    // GLFW setup
    void setupGlfw(bool fullscreen);
    GLFWmonitor* getMonitorForPoint(int x, int y);
    void getConsoleWindowPosition(int& left, int& top, int& right, int& bottom);
    void calculateScale(const GLFWvidmode* mode);
    float getAspectCorrectionFactor() const;
    void setWindowProperties(bool fullscreen);
    void getWindowPosition(GLFWwindow* window, int& x, int& y);

    // OpenGL setup
    void setupOpenGL();
    void setViewportSize();
    void createShaders();
    void createBuffers();
    void createTextures();

    // interface
    void setPixel(int row, int column, Pixel pixel);
    void setGrayscalePixel(int row, int column, uint8_t white);
    void clearDisplay(uint16_t clearColor);
    void clearScanline(int vCounter, uint16_t clearColor);
    bool isRunning() const;
    bool isPressed(int key) const;

    // update
public:
    void update();
    void handleInput();
    void uploadTexture();

    // teardown
    void terminate();


public:
    bool toggleFullscreenRequested = false;
    bool pauseRequested = false;

    const int width;
    const int height;

private:
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

    const size_t pixelBufferSize = size_t(height) * size_t(width);
    std::array<std::vector<Pixel>, 3> pixelBuffers;

    int drawBufferIndex = 0;
    int writeBufferIndex = 1;

    std::mutex pixelBufferMutex;

    Output output;

    GLFWwindow* window = nullptr;

    std::string title;

    float scale;
    float xScale = 0.0f;
    float yScale = 0.0f;
    float xScreenCoverage = 0.0f;
    float yScreenCoverage = 0.0f;
    const bool syncUpdate;

    unsigned int screenQuadVertexArray = 0;
    unsigned int screenQuadVertexBuffer = 0;
    unsigned int screenQuadIndexBuffer = 0;
    unsigned int texture = 0;

    SimpleShader simpleShader;
    ScanlineShader scanlineShader;
    std::array<Shader*, 2> shaders = { &simpleShader, &scanlineShader };
    int currentShaderIndex = 0;

    double pressKeyTimeout = 0.f;
    bool focusWindowRequested = false;
    bool textureNeedsUpdate = false;

    friend class Processor;
    friend class Registers;
    friend class OamViewer;
    friend class BackgroundViewer;
    friend class SpriteLayerViewer;
    friend class Mode7Viewer;

    friend void framebufferSizeCallback(GLFWwindow*, int width, int height);
};

}