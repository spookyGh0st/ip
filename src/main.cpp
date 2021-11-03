#include <optional>
#include <memory>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.cpp"
#include "ip/Scanner.hpp"


int main() {
    auto window{std::make_unique<Window>(Window())};
    std::string expr { "sqrt(x^2+y^2+z^2)+1" };
    auto s = ip::Scanner(expr);
    ip::Token t = s.scanToken();
    while (t.type != ip::TOKEN_EOF) {
        std::cout << t.data << " " << t.type << std::endl;
        t = s.scanToken();
    }

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



