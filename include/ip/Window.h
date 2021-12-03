#ifndef IP_WINDOW_H
#define IP_WINDOW_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Scene.h"

#define GLFW_MAJOR_VERSION 4
#define GLFW_MINOR_VERSION 6
#include <glm/glm/ext/matrix_float4x4.hpp>

class Window {
private:
    GLFWwindow *glfwWindow;
    double xPos{}, yPos{}, size{};
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
public:
    Window();
    Window(const Window&) = delete;
    Window(Window&& other) noexcept;
    glm::mat4 mm { glm::mat4() };

    void move(float x, float y, float z);
    void setPosition(double x, double y);
    void setSize(double size);
    int shouldClose();
    void processInput();
    void swapBuffers();
    virtual ~Window();

    void draw();
};

#endif //IP_WINDOW_H
