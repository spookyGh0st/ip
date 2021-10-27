#include <optional>
#include <memory>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.cpp"


int main()
{
        auto window { std::make_unique<Window>(Window()) };



    // render loop
    while(!window->shouldClose()) {
        // input
        window->processInput();
        window->move(-0.5,-0.5,-0.5);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // check and call events and swap the buffers
        glfwPollEvents();
        window->swapBuffers();
    }

    // glfwTerminate();
    return 0;
}



