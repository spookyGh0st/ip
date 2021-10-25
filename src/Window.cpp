#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

#define GLFW_MAJOR_VERSION 3
#define GLFW_MINOR_VERSION 3

class Window {
private:
    GLFWwindow *glfwWindow;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
public:
    Window(){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_MAJOR_VERSION);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_MINOR_VERSION);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

        glViewport(0, 0, 800, 600);
        glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);
    }

    int shouldClose(){
        return glfwWindowShouldClose(glfwWindow);
    }

    void processInput(){
        if(glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(glfwWindow, true);
    }

    void swapBuffers(){
        glfwSwapBuffers(glfwWindow);
    }
};
