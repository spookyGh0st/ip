#ifndef IP_WINDOW_H
#define IP_WINDOW_H

#include "glad.h"
#include "GLFW/glfw3.h"
#include "Scene.h"

#define GLFW_MAJOR_VERSION 4
#define GLFW_MINOR_VERSION 6

class Window {
private:
    GLFWwindow *glfwWindow;
    float xPos{}, yPos{};

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
public:
    Window();
    Window(const Window&) = delete;
    Window(Window&& other) noexcept;

    int shouldClose();
    void processInput();
    void swapBuffers();
    virtual ~Window();

    float height{};
    float width{};
};

#endif //IP_WINDOW_H
