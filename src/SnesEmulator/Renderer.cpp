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
    glfwSetWindowPos(window, 1000, 40);

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
    if (!syncUpdate) {
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

    glClear(GL_COLOR_BUFFER_BIT);

    glRasterPos2i(-1, -1);
    glPixelZoom(scale, scale);
    glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, pixelBuffer.data());
    glFlush();

    glfwSwapBuffers(window);
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        pause = true;
    }

    buttonStart = glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS;
    buttonSelect = glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS;
    buttonA = glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS;
    buttonB = glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS;
    buttonX = glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS;
    buttonY = glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS;
    buttonL = glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS;
    buttonR = glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS;
    buttonUp = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
    buttonDown = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
    buttonLeft = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
    buttonRight = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
}

bool Renderer::isRunning() const
{
    return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0;
}
