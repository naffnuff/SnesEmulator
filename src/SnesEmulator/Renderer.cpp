#include "Renderer.h"

#include <cmath>

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>

#include "Common/System.h"

void Renderer::initialize(bool fullscreen, bool aspectCorrection)
{
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    const float aspectCorrectionFactor = aspectCorrection ? (float(height) / float(width)) * (4.f / 3.f) : 1.f;
    if (fullscreen) {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        window = glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, nullptr);
        yScale = float(mode->height) / float(height);
        xScale = yScale * aspectCorrectionFactor;
        float correctedWidth = float(width) * xScale;
        xScreenCoverage = correctedWidth / float(mode->width);
    }
    else {
        yScale = scale;
        xScale = yScale * aspectCorrectionFactor;
        window = glfwCreateWindow(int(float(width) * xScale + 0.5), int(float(height) * yScale + 0.5), title.c_str(), nullptr, nullptr);
        glfwSetWindowPos(window, windowXPosition, windowYPosition);
        xScreenCoverage = 1.0;
    }

    output << "Created renderer with dimensions " << int(float(width) * xScale + 0.5) << ":" << int(float(height) * yScale + 0.5) << std::endl;

    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to open GLFW window.");
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLEW");
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    if (syncUpdate) {
        glfwSwapInterval(1);
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void Renderer::setWindowProperties(bool fullscreen, bool aspectRatioCorrection)
{
    if (fullscreen) {

    }
    else {
        yScale = scale;
        const float aspectCorrectionFactor = aspectRatioCorrection ? (float(height) / float(width)) * (4.f / 3.f) : 1.f;
        xScale = yScale * aspectCorrectionFactor;
        xScreenCoverage = 1.0;
        glfwSetWindowMonitor(window, nullptr, windowXPosition, windowYPosition, int(float(width) * xScale + .5f), int(float(height) * yScale + .5f), 0);
    }
}

void Renderer::update()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos2f(-xScreenCoverage, -1.0);
    glPixelZoom(xScale, yScale);
    {
        std::lock_guard lock(pixelBufferMutex);
        glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, pixelBuffer.data());
        if (!syncUpdate)
        {
            static double previousTime = glfwGetTime();
            static int frameCount = 0;

            double currentTime = glfwGetTime();
            frameCount++;
            if (currentTime - previousTime >= 1.0) {
                output << frameCount << std::endl;

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
            pressKeyTimeout = 60;
        }
        if (spacePressed) {
            toggleFullscreenRequested = true;
            pressKeyTimeout = 60;
        }
    }
    else {
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
        if (glfwJoystickIsGamepad(joystick))
        {
            GLFWgamepadstate state;
            if (glfwGetGamepadState(joystick, &state))
            {
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
                    }
                    else if (angle > -pi8 * 3 && angle < pi8 * 3) {
                        buttonRight = true;
                    }

                    if (angle > -pi8 * 7 && angle < -pi8) {
                        buttonUp = true;
                    }
                    else if (angle > pi8 && angle < pi8 * 7) {
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
