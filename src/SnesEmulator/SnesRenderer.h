#pragma once

#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderer
{
public:
    struct Pixel
    {
        GLubyte red;
        GLubyte green;
        GLubyte blue;
    };

    static const int width = 256;
    static const int height = 224;

    Renderer(std::ostream& output, std::istream& input, std::ostream& error)
        : pixelBuffer(height * width)
        , output(output)
        , input(input)
        , error(error)
    {
    }

    ~Renderer()
    {
        output << "Renderer destructor start" << std::endl;
        glfwTerminate();
        output << "Renderer destructor end" << std::endl;
    }

    Renderer(Renderer&) = delete;
    Renderer& operator=(Renderer&) = delete;

    void initialize(const std::string& windowTitle);
    void setScanline(int lineIndex, const std::array<Pixel, width>& pixels);
    void update();
    bool isRunning() const;

    double getTime()
    {
        return glfwGetTime();
    }

private:
    void setPixel(int row, int column, Pixel pixel);

public:
    bool pause = false;

private:
    std::ostream& output;
    std::istream& input;
    std::ostream& error;

    GLFWwindow* window;

    float scale2 = 4.5f;

    std::vector<Pixel> pixelBuffer;
};