#include "VideoRenderer.h"

#include <cmath>

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

#include <GLFW/glfw3.h>

#include "Common/System.h"

#ifndef GL_UNSIGNED_SHORT_1_5_5_5_REV
#define GL_UNSIGNED_SHORT_1_5_5_5_REV 0x8366
#endif

namespace {

void getConsoleWindowPosition(int& left, int& top, int& right, int& bottom);

GLFWmonitor* getMonitorForPoint(int x, int y)
{
    int monitorCount;
    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
    GLFWmonitor* result = nullptr;
    for (int i = 0; i < monitorCount; ++i) {
        GLFWmonitor* monitor = monitors[i];
        int monitorX, monitorY;
        glfwGetMonitorPos(monitor, &monitorX, &monitorY);
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        int relativeX = x - monitorX;
        int relativeY = y - monitorY;
        if (relativeX >= 0 && relativeX < mode->width && relativeY >= 0 && relativeY < mode->height) {
            result = monitor;
        }
    }
    return result;
}

void getWindowPosition(GLFWwindow* window, int& x, int& y)
{
    glfwGetWindowPos(window, &x, &y);
    int left, top, right, bottom;
    glfwGetWindowFrameSize(window, &left, &top, &right, &bottom);
    x -= left;
    y -= top;
}

#ifdef _WIN32
void getConsoleWindowPosition(int& left, int& top, int& right, int& bottom)
{
    if (HWND window = GetConsoleWindow()) {
        RECT rect;
        GetWindowRect(window, &rect);
        left = rect.left;
        top = rect.top;
        right = rect.right;
        bottom = rect.bottom;
    }
    else {
        left = 0;
        top = 0;
        right = 0;
        bottom = 0;
    }
}
#else
void getConsoleWindowPosition(int& x, int& y)
{
    x = 0;
    y = 0;
}
#endif

}

namespace Video {

Renderer::~Renderer()
{
    output.debug("Renderer ", title, " destructor");
    terminate();
}

void Renderer::initialize(bool fullscreen, bool aspectCorrection)
{
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    int left, top, right, bottom;
    getConsoleWindowPosition(left, top, right, bottom);
    windowXPosition = right;
    windowYPosition = top;

    GLFWmonitor* monitor = getMonitorForPoint(left, top);
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    window = glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, nullptr);

    output.debug("Created renderer with dimensions ", int(float(width) * xScale + 0.5), ":", int(float(height) * yScale + 0.5));

    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to open GLFW window.");
    }
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    if (syncUpdate) {
        glfwSwapInterval(1);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    if (fullscreen) {
        calculateScale(mode, aspectCorrection);
    } else {
        setWindowProperties(fullscreen, aspectCorrection);
    }
}

void Renderer::terminate()
{
    glfwTerminate();
}

float Renderer::getAspectCorrectionFactor(bool aspectCorrection) const
{
    return aspectCorrection ? (float(height) / float(width)) * (4.f / 3.f) : 1.f;
}

void Renderer::calculateScale(const GLFWvidmode* mode, bool aspectCorrection)
{
    yScale = float(mode->height) / float(height);
    xScale = yScale * getAspectCorrectionFactor(aspectCorrection);
    float screenWidth = float(width) * xScale;
    xScreenCoverage = screenWidth / float(mode->width);
    yScreenCoverage = 1.f;
    if (xScreenCoverage > 1.f) {
        float scaleFactor = 1.f / xScreenCoverage;
        xScale *= scaleFactor;
        yScale *= scaleFactor;
        xScreenCoverage *= scaleFactor;
        yScreenCoverage *= scaleFactor;
    }
}

void Renderer::setWindowProperties(bool fullscreen, bool aspectCorrection)
{
    if (fullscreen) {
        int x, y;
        getWindowPosition(window, x, y);
        GLFWmonitor* fullscreenMonitor = getMonitorForPoint(x, y);
        if (!fullscreenMonitor) {
            fullscreenMonitor = glfwGetPrimaryMonitor();
        }
        const GLFWvidmode* mode = glfwGetVideoMode(fullscreenMonitor);
        calculateScale(mode, aspectCorrection);
        glfwSetWindowMonitor(window, fullscreenMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    } else {
        yScale = scale;
        xScale = yScale * getAspectCorrectionFactor(aspectCorrection);
        xScreenCoverage = 1.f;
        yScreenCoverage = 1.f;
        glfwSetWindowMonitor(window, nullptr, windowXPosition, windowYPosition, int(float(width) * xScale + .5f), int(float(height) * yScale + .5f), 0);
    }
}

void Renderer::update()
{
    if (focusWindowRequested) {
        glfwFocusWindow(window);
        focusWindowRequested = false;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos2f(-xScreenCoverage, -yScreenCoverage);
    glPixelZoom(xScale, yScale);
    {
        std::scoped_lock lock(pixelBufferMutex);
        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, pixelBuffer.data());
        if (!syncUpdate)
        {
            static double previousTime = glfwGetTime();
            static int frameCount = 0;

            double currentTime = glfwGetTime();
            frameCount++;
            if (currentTime - previousTime >= 1.0) {
                output.debug(frameCount);

                frameCount = 0;
                previousTime = currentTime;
            }
        }
    }
    glFlush();

    glfwSwapBuffers(window);
    glfwPollEvents();

    bool spacePressed = isPressed(GLFW_KEY_SPACE);
    bool escapePressed = isPressed(GLFW_KEY_ESCAPE);
    if (pressKeyTimeout == 0) {
        if (escapePressed) {
            pauseRequested = true;
            pressKeyTimeout = 30;
        }
        if (spacePressed) {
            toggleFullscreenRequested = true;
            pressKeyTimeout = 30;
        }
    } else {
        --pressKeyTimeout;
    }

    buttonStart = isPressed(GLFW_KEY_COMMA);
    buttonSelect = isPressed(GLFW_KEY_PERIOD);
    buttonA = isPressed(GLFW_KEY_L);
    buttonB = isPressed(GLFW_KEY_K);
    buttonX = isPressed(GLFW_KEY_I);
    buttonY = isPressed(GLFW_KEY_J);
    buttonL = isPressed(GLFW_KEY_U);
    buttonR = isPressed(GLFW_KEY_O);
    buttonUp = isPressed(GLFW_KEY_W);
    buttonDown = isPressed(GLFW_KEY_S);
    buttonLeft = isPressed(GLFW_KEY_A);
    buttonRight = isPressed(GLFW_KEY_D);

    for (int joystick = GLFW_JOYSTICK_1; joystick <= GLFW_JOYSTICK_LAST; ++joystick) {
        if (glfwJoystickIsGamepad(joystick)) {
            GLFWgamepadstate state;
            if (glfwGetGamepadState(joystick, &state)) {
                buttonStart |= state.buttons[GLFW_GAMEPAD_BUTTON_START] == GLFW_PRESS;
                buttonSelect |= state.buttons[GLFW_GAMEPAD_BUTTON_BACK] == GLFW_PRESS;
                buttonA |= state.buttons[GLFW_GAMEPAD_BUTTON_B] == GLFW_PRESS;
                buttonB |= state.buttons[GLFW_GAMEPAD_BUTTON_A] == GLFW_PRESS;
                buttonX |= state.buttons[GLFW_GAMEPAD_BUTTON_Y] == GLFW_PRESS;
                buttonY |= state.buttons[GLFW_GAMEPAD_BUTTON_X] == GLFW_PRESS;
                buttonL |= state.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER] == GLFW_PRESS;
                buttonR |= state.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER] == GLFW_PRESS;
                buttonUp |= state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP] == GLFW_PRESS;
                buttonDown |= state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN] == GLFW_PRESS;
                buttonLeft |= state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT] == GLFW_PRESS;
                buttonRight |= state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT] == GLFW_PRESS;

                float axisX = state.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
                float axisY = state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];

                static const float thresholdSquared = .25f * .25f;
                if (axisX * axisX + axisY * axisY > thresholdSquared) {
                    float angle = std::atan2f(axisY, axisX);
                    static const float pi8 = std::atanf(1.f) / 2.f;

                    if (angle > pi8 * 5 || angle < -pi8 * 5) {
                        buttonLeft = true;
                    } else if (angle > -pi8 * 3 && angle < pi8 * 3) {
                        buttonRight = true;
                    }

                    if (angle > -pi8 * 7 && angle < -pi8) {
                        buttonUp = true;
                    } else if (angle > pi8 && angle < pi8 * 7) {
                        buttonDown = true;
                    }
                }
            }
        }
    }
}

bool Renderer::isRunning() const
{
    return glfwWindowShouldClose(window) == 0;
}

double Renderer::getTime() const
{
    return glfwGetTime();
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
    int index = row * width + column;
    if (index < 0 || index >= pixelBuffer.size()) {
        throw std::logic_error("Renderer: Index out of bounds in pixel buffer");
    }
    pixelBuffer[index] = pixel;
}

void Renderer::setGrayscalePixel(int row, int column, uint8_t white)
{
    uint8_t white5Bit = white >> 3;
    Pixel pixel = white5Bit << 0 | white5Bit << 5 | white5Bit << 10;
    setPixel(row, column, pixel);
}

void Renderer::setGrayscaleTile(int startRow, int startColumn, const std::array<std::array<uint8_t, 8>, 8> & tile, int bitsPerPixel)
{
    for (int row = 0; row < 8; ++row) {
        for (int column = 0; column < 8; ++column) {
            setGrayscalePixel(startRow + row, startColumn + column, tile[row][column] * (bitsPerPixel == 2 ? 85 : 17));
        }
    }
}

void Renderer::clearDisplay(uint16_t clearColor)
{
    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            setPixel(row, column, clearColor);
        }
    }
}

void Renderer::clearScanline(int vCounter, uint16_t clearColor)
{
    for (int column = 0; column < width; ++column) {
        setPixel(vCounter, column, clearColor);
    }
}

bool Renderer::isPressed(int key) const
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

void Renderer::focusWindow(bool value)
{
    focusWindowRequested = value;
}

}
