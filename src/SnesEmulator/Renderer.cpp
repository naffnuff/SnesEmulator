#include "Renderer.h"

#include <cmath>

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>

#include "Common/System.h"

void Renderer::initialize(const std::string& windowTitle, int windowXPosition, int windowYPosition)
{
    //return;
    title = windowTitle;

    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    window = glfwCreateWindow(width * int(scale), height * int(scale), windowTitle.c_str(), NULL, NULL);
    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to open GLFW window.");
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowPos(window, windowXPosition, windowYPosition);

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLEW");
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    if (syncUpdate) {
        glfwSwapInterval(1);
    }

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void Renderer::update()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos2i(-1, -1);
    glPixelZoom(scale, scale);
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
    if (pressPauseTimeout == 0) {
        if (spacePressed) {
            pause = true;
            pressPauseTimeout = 10;
        }
    }
    else {
        --pressPauseTimeout;
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

    for (int i = 0; i < 2; ++i) {
        if (glfwJoystickIsGamepad(GLFW_JOYSTICK_1 + i))
        {
            GLFWgamepadstate state;
            if (glfwGetGamepadState(GLFW_JOYSTICK_1 + i, &state))
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
                buttonLeft |= state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] < -0.25f;
                buttonRight |= state.axes[GLFW_GAMEPAD_AXIS_LEFT_X] > 0.25f;
                buttonUp |= state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] < -0.25f;
                buttonDown |= state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y] > 0.25f;
            }
        }
    }
}

bool Renderer::isRunning() const
{
    return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0;
}
