#include "VideoRenderer.h"

#include <cmath>

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Common/System.h"

#include "Shader.h"

namespace Video
{

// public

Renderer::Renderer(int windowXPosition, int windowYPosition, int width, int height, float scale, bool syncUpdate, Output& output)
    : output(output, "renderer")
    , windowXPosition(windowXPosition)
    , windowYPosition(windowYPosition)
    , width(width)
    , height(height)
    , scale(scale)
    , syncUpdate(syncUpdate)
    , pixelBuffer(size_t(height)* size_t(width))
    , title("SNES Emulator")
{
}

Renderer::~Renderer()
{
    output.debug("Renderer ", title, " destructor");
    terminate();
}

double Renderer::getTime() const
{
    return glfwGetTime();
}

void Renderer::focusWindow(bool value)
{
    focusWindowRequested = value;
}

// private

// callbacks

void framebufferSizeCallback(GLFWwindow*, int width, int height)
{
    //Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));

    std::cout << "yo " << width << ":" << height << std::endl;

    //renderer->setWindowProperties(false);
}

// setup

void Renderer::initialize(bool fullscreen)
{
    setupGlfw(fullscreen);
    setupOpenGL();
}

// GLFW setup

void Renderer::setupGlfw(bool fullscreen)
{
    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    output.debug("Creating renderer with dimensions ", width, ":", height, ", scale ", scale);

    window = glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, nullptr);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window.");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glfwSwapInterval(syncUpdate ? 1 : 0);

    if (fullscreen)
    {
        calculateScale(mode);
    }
    else
    {
        setWindowProperties(false);
    }

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    output.debug("Initialized renderer with OpenGL ", glGetString(GL_VERSION));
}

#ifdef _WIN32
void Renderer::getConsoleWindowPosition(int& left, int& top, int& right, int& bottom)
{
    if (HWND consoleWindow = GetConsoleWindow())
    {
        RECT rect;
        GetWindowRect(consoleWindow, &rect);
        left = rect.left;
        top = rect.top;
        right = rect.right;
        bottom = rect.bottom;
    }
    else
    {
        left = 0;
        top = 0;
        right = 0;
        bottom = 0;
    }
}
#else
void Renderer::getConsoleWindowPosition(int& x, int& y, int& right, int& bottom)
{
    x = 0;
    y = 0;
    right = 100;
    bottom = 100;
}
#endif

GLFWmonitor* Renderer::getMonitorForPoint(int x, int y)
{
    int monitorCount;
    GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
    GLFWmonitor* result = nullptr;
    for (int i = 0; i < monitorCount; ++i)
    {
        GLFWmonitor* monitor = monitors[i];
        int monitorX, monitorY;
        glfwGetMonitorPos(monitor, &monitorX, &monitorY);
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        int relativeX = x - monitorX;
        int relativeY = y - monitorY;
        if (relativeX >= 0 && relativeX < mode->width && relativeY >= 0 && relativeY < mode->height)
        {
            result = monitor;
        }
    }
    return result;
}

void Renderer::calculateScale(const GLFWvidmode* mode)
{
    yScale = float(mode->height) / float(height);
    xScale = yScale * getAspectCorrectionFactor();
    float screenWidth = float(width) * xScale;
    xScreenCoverage = screenWidth / float(mode->width);
    yScreenCoverage = 1.f;
    if (xScreenCoverage > 1.f)
    {
        float scaleFactor = 1.f / xScreenCoverage;
        xScale *= scaleFactor;
        yScale *= scaleFactor;
        xScreenCoverage *= scaleFactor;
        yScreenCoverage *= scaleFactor;
    }
}

float Renderer::getAspectCorrectionFactor() const
{
    return (float(height) / float(width)) * (4.f / 3.f);
}

void Renderer::setWindowProperties(bool fullscreen)
{
    if (fullscreen)
    {
        int x, y;
        getWindowPosition(window, x, y);
        GLFWmonitor* fullscreenMonitor = getMonitorForPoint(x, y);
        if (!fullscreenMonitor)
        {
            fullscreenMonitor = glfwGetPrimaryMonitor();
        }
        const GLFWvidmode* mode = glfwGetVideoMode(fullscreenMonitor);
        calculateScale(mode);
        glfwSetWindowMonitor(window, fullscreenMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);

        int scaledWidth = int(width * xScale);
        int scaledHeight = int(height * yScale);
        int xOffset = (mode->width - scaledWidth) / 2;
        int yOffset = (mode->height - scaledHeight) / 2;

        glViewport(xOffset, yOffset, scaledWidth, scaledHeight);

        std::cout << "fullscreen " << scaledWidth << ":" << scaledHeight << std::endl;
    }
    else
    {
        yScale = scale;
        xScale = yScale * getAspectCorrectionFactor();
        xScreenCoverage = 1.f;
        yScreenCoverage = 1.f;
        glfwSetWindowMonitor(window, nullptr, windowXPosition, windowYPosition, int(float(width) * xScale + .5f), int(float(height) * yScale + .5f), 0);

        setViewportSize();
    }
}

void Renderer::getWindowPosition(GLFWwindow* glfwWindow, int& x, int& y)
{
    glfwGetWindowPos(glfwWindow, &x, &y);
    int left, top, right, bottom;
    glfwGetWindowFrameSize(glfwWindow, &left, &top, &right, &bottom);
    x -= left;
    y -= top;
}

// OpenGL setup

void Renderer::setupOpenGL()
{
    createShaders();
    createBuffers();
    createTextures();

    setViewportSize();
}

void Renderer::setViewportSize()
{
    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    std::cout << "windowed " << windowWidth << ":" << windowHeight << std::endl;
}

void Renderer::createShaders()
{
    shaderProgram = createShaderProgram(vertexShaderSource, scanlineFragmentShaderSource);

    timeUniform = glGetUniformLocation(shaderProgram, "time");
    resolutionUniform = glGetUniformLocation(shaderProgram, "resolution");
    aspectRatioUniform = glGetUniformLocation(shaderProgram, "aspectRatio");
    gameTextureUniform = glGetUniformLocation(shaderProgram, "gameTexture");
}

unsigned int Renderer::createShaderProgram(const char* vertexSource, const char* fragmentSource)
{
    unsigned int vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        throw std::runtime_error("Shader linking failed: " + std::string(infoLog));
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

unsigned int Renderer::compileShader(const char* source, unsigned int type)
{
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        throw std::runtime_error("Shader compilation failed: " + std::string(infoLog));
    }

    return shader;
}

void Renderer::createBuffers()
{
    // Fullscreen quad
    float vertices[] =
    {
        // positions        // texture coordinates
        -1.f, -1.f, 0.f,    0.f, 0.f,
         1.f, -1.f, 0.f,    1.f, 0.f,
         1.f,  1.f, 0.f,    1.f, 1.f,
        -1.f,  1.f, 0.f,    0.f, 1.f
    };

    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &screenQuadVertexArray);
    glGenBuffers(1, &screenQuadVertexBuffer);
    glGenBuffers(1, &screenQuadIndexBuffer);

    glBindVertexArray(screenQuadVertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, screenQuadVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, screenQuadIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Renderer::createTextures()
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, nullptr);

    glBindTexture(GL_TEXTURE_2D, 0);
}

// interface

void Renderer::setPixel(int row, int column, Pixel pixel)
{
    row = height - 1 - row;
    int index = row * width + column;
    if (index < 0 || index >= pixelBuffer.size())
    {
        throw std::logic_error("Renderer: Index out of bounds in pixel buffer");
    }
    pixelBuffer[index] = pixel;

    textureNeedsUpdate = true;
}

void Renderer::setGrayscalePixel(int row, int column, uint8_t white)
{
    uint8_t white5Bit = white >> 3;
    Pixel pixel = white5Bit << 0 | white5Bit << 5 | white5Bit << 10;
    setPixel(row, column, pixel);
}

void Renderer::clearDisplay(uint16_t clearColor)
{
    for (int row = 0; row < height; ++row)
    {
        for (int column = 0; column < width; ++column)
        {
            setPixel(row, column, clearColor);
        }
    }
}

void Renderer::clearScanline(int vCounter, uint16_t clearColor)
{
    for (int column = 0; column < width; ++column)
    {
        setPixel(vCounter, column, clearColor);
    }
}

bool Renderer::isRunning() const
{
    return !glfwWindowShouldClose(window);
}

bool Renderer::isPressed(int key) const
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

// update

void Renderer::update()
{
    handleInput();

    uploadTexture();

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    if (timeUniform >= 0)
    {
        glUniform1f(timeUniform, (float)getTime());
    }
    if (resolutionUniform >= 0)
    {
        glUniform2f(resolutionUniform, (float)width, (float)height);
    }
    if (aspectRatioUniform >= 0)
    {
        glUniform1f(aspectRatioUniform, (float)width / (float)height);
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    if (gameTextureUniform >= 0)
    {
        glUniform1i(gameTextureUniform, 0);
    }

    glBindVertexArray(screenQuadVertexArray);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    if (!syncUpdate)
    {
        static double previousTime = glfwGetTime();
        static int frameCount = 0;

        double currentTime = glfwGetTime();
        frameCount++;
        if (currentTime - previousTime >= 1.0)
        {
            output.debug(frameCount);

            frameCount = 0;
            previousTime = currentTime;
        }
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::handleInput()
{
    if (focusWindowRequested)
    {
        glfwFocusWindow(window);
        focusWindowRequested = false;
    }

    bool spacePressed = isPressed(GLFW_KEY_SPACE);
    bool escapePressed = isPressed(GLFW_KEY_ESCAPE);
    if (pressKeyTimeout == 0)
    {
        if (escapePressed)
        {
            pauseRequested = true;
            pressKeyTimeout = 30;
        }
        if (spacePressed)
        {
            toggleFullscreenRequested = true;
            pressKeyTimeout = 30;
        }
    }
    else
    {
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

    for (int joystick = GLFW_JOYSTICK_1; joystick <= GLFW_JOYSTICK_LAST; ++joystick)
    {
        if (glfwJoystickIsGamepad(joystick))
        {
            if (const char* name = glfwGetJoystickName(joystick))
            {
                //std::cout << name << std::endl;
                //if (name[0] == 'X') // To filter out non-Xbox controllers
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
                        if (axisX * axisX + axisY * axisY > thresholdSquared)
                        {
                            float angle = atan2f(axisY, axisX);
                            static const float pi8 = atanf(1.f) / 2.f;

                            if (angle > pi8 * 5 || angle < -pi8 * 5)
                            {
                                buttonLeft = true;
                            }
                            else if (angle > -pi8 * 3 && angle < pi8 * 3)
                            {
                                buttonRight = true;
                            }

                            if (angle > -pi8 * 7 && angle < -pi8)
                            {
                                buttonUp = true;
                            }
                            else if (angle > pi8 && angle < pi8 * 7)
                            {
                                buttonDown = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

void Renderer::uploadTexture()
{
    if (textureNeedsUpdate)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
        {
            std::scoped_lock lock(pixelBufferMutex);
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, pixelBuffer.data());
        }
        glBindTexture(GL_TEXTURE_2D, 0);

        textureNeedsUpdate = false;
    }
}

// teardown

void Renderer::terminate()
{
    if (screenQuadVertexArray)
    {
        glDeleteVertexArrays(1, &screenQuadVertexArray);
    }
    if (screenQuadVertexBuffer)
    {
        glDeleteBuffers(1, &screenQuadVertexBuffer);
    }
    if (screenQuadIndexBuffer)
    {
        glDeleteBuffers(1, &screenQuadIndexBuffer);
    }
    if (texture)
    {
        glDeleteTextures(1, &texture);
    }
    if (shaderProgram)
    {
        glDeleteProgram(shaderProgram);
    }

    if (window)
    {
        glfwDestroyWindow(window);
        window = nullptr;
    }

    glfwTerminate();
}

}
