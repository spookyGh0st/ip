#ifndef IP_WINDOW_H
#define IP_WINDOW_H

#define GLFW_MAJOR_VERSION 3
#define GLFW_MINOR_VERSION 3

class Window {
private:
    GLFWwindow *glfwWindow;
    float xPos{}, yPos{}, size{};
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
public:
    Window();
    Window(const Window&) = delete;
    Window(Window&& other) noexcept;

    void move(float x, float y, float z);
    int shouldClose();
    void processInput();
    void swapBuffers(){
        glfwSwapBuffers(glfwWindow);
    }
    virtual ~Window();
};

#endif //IP_WINDOW_H
