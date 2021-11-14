#include "ip/Tape.h"
#include "ip/Clause.h"

TapeGenerator::TapeGenerator(std::unique_ptr<Expr> &&e):
    expr(std::move(e)) {

}

Expr::Tape TapeGenerator::generate() {
    auto tape= std::vector<std::unique_ptr<Clause>>();
    auto stack = std::stack<uint8_t>();
    uint8_t address = 255;
    for (uint8_t i = UINT8_MAX; i > 0; --i) {
        stack.push(i);
    }


    expr->createTape(tape,stack);
    return tape;
}
