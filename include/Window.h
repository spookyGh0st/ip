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
    float xPos{}, yPos{}, width{}, height{};
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
public:
    Window();
    Window(const Window&) = delete;
    Window(Window&& other) noexcept;

    void setPosition(float x, float y);
    void setSize(float width, float height);
    int shouldClose();
    void processInput();
    void swapBuffers();
    virtual ~Window();
};

#endif //IP_WINDOW_H
