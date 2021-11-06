#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <ip/Window.hpp>

void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

    glfwWindow = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (glfwWindow == nullptr)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(glfwWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);
    xPos = 800; yPos = 500; size = 800.0;
    const GLFWvidmode *modes = glfwGetVideoMode(glfwGetPrimaryMonitor());
    xPos = float(modes->width)/2.0f;
    yPos = float(modes->height)/2.0f;
    //move(0,0,0); // set Position and size
}

Window::~Window() {
    if (glfwWindow != nullptr)
        glfwDestroyWindow(glfwWindow);
}

void Window::move(float x, float y, float z) {
    xPos += x; yPos += y; size += z;
    glfwSetWindowPos(glfwWindow, int(xPos-size/2),int(yPos-size/2));
    glfwSetWindowSize(glfwWindow, int(size),int(size));
    glViewport(0, 0, int(size), int(size));
}

int Window::shouldClose() {
    return glfwWindowShouldClose(glfwWindow);
}

Window::Window(Window &&other) noexcept {
    glfwWindow = other.glfwWindow;
    other.glfwWindow = nullptr;
    size = other.size;
    xPos = other.xPos;
    yPos = other.yPos;
}

void Window::processInput() {
    if(glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(glfwWindow, true);
}
