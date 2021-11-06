#include <memory>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.cpp"
#include "Parser.hpp"


int main() {
    auto window{std::make_unique<Window>(Window())};
    std::string expr { "sqrt(x^2+y^2+z^2)+1" };
    auto p = ip::Parser(expr);
    auto e { p.parse() };
    std::cout << e->draw() << "\n";

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



