#include "ip/test.h"


std::unique_ptr<Expr> testParsing() {
    std::string expr { "sqrt(x^2+y^2+z^2)+1" };
    auto p = ip::Parser(expr);
    auto e { p.parse() };
    std::cout << e->draw() << "\n";
    return e;
}

void testTape() {
    //auto exprStr { "min(1++2,5"};
    auto exprStr { "min(y,sqrt(x^2+(y-1)^2+(z-6)^2)-1)" };
    auto expr = ip::Parser(exprStr).parse();
    auto tg = TapeGenerator(std::move(expr));
    auto tape = tg.generate();
    std::cout << "op\tout\tiA\tiB" << std::endl;
    for (auto & i : tape.instructions) {
        std::cout << i.print() << std::endl;
    }
    auto te { TapeEmulator(tape,-0.2,1.0,5.0)};
    std::cout << "\n Output: "+std::to_string(te.emulate()) <<std::endl;
};


