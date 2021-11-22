#include <iostream>
#include <ip/Tape.h>
#include "ip/Parser.hpp"
#include "ip/Display.h"

std::unique_ptr<Expr> testParsing(){
    std::string expr { "sqrt(x^2+y^2+z^2)+1" };
    auto p = ip::Parser(expr);
    auto e { p.parse() };
    std::cout << e->draw() << "\n";
    return e;
};

void testTape(){
    auto expr = ip::Parser("sqrt(x^2+y^2+z^2)+1").parse();
    auto tg = TapeGenerator(std::move(expr));
    auto tape = tg.generate();
    std::cout << "op\tout\tiA\tiB\tvalue" << std::endl;
    for (auto & i : tape) {
        std::cout << i.print() << std::endl;
    }
}

int main() {
    testTape();
    auto display { Display() };
    display.createWindow();

    // render loop
    while(!display.shouldClose()) {
        display.update();
    }

    return 0;
}



