#include <iostream>
#include "Parser.hpp"
#include "Display.hpp"


int main() {
    std::string expr { "sqrt(x^2+y^2+z^2)+1" };
    auto p = ip::Parser(expr);
    auto e { p.parse() };
    std::cout << e->draw() << "\n";

    auto display { Display() };
    display.createWindow();
    display.createWindow();
    display.createWindow();
    display.createWindow();

    // render loop
    while(!display.shouldClose()) {
        display.update();
    }

    return 0;
}



