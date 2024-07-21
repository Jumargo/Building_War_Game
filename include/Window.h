#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

class Window
{
public:
    GLFWwindow* window;
    Window(int width, int height, const char* title);
    ~Window();
    bool shouldClose();
    void swapBuffers();
    void pollEvents();
    void captureMouse();
    void updateTitleWithFPS();
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void initGLFW();
    void createWindow(int width, int height, const char* title);
    void initGLEW();
    float lastTime;
    int nbFrames;
};


