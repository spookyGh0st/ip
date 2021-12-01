#include "ip/Tape.h"
#include "ip/Clause.h"

TapeGenerator::TapeGenerator(std::unique_ptr<Expr> &&e):
    expr(std::move(e)) {

}

Expr::Tape TapeGenerator::generate() {
    auto tape= std::vector<Clause>();
    auto stack = std::stack<uint8_t>();
    uint8_t address = 255;
    for (uint8_t i = UINT8_MAX; i > 0; --i) {
        stack.push(i);
    }
    stack.push(0);
    expr->createTape(tape,stack);
    return tape;
}

TapeEmulator::TapeEmulator(Expr::Tape &tape, float x, float y, float z)
    : tape(tape), X(x), Y(y), Z(z) {}

float TapeEmulator::emulate() {
    for (current = 0; current < tape.size(); ++current) {
        emulateClause(tape[current]);
    }
    return ram[tape[current].output];
}

void TapeEmulator::emulateClause(Clause &clause) {
    switch (clause.opcode) {
        case OPCODE_PLUS:
            ram[clause.output] = ram[clause.input_A] + ram[clause.input_B];
            break;
        case OPCODE_MINUS:
            ram[clause.output] = ram[clause.input_A] - ram[clause.input_B];
            break;
        case OPCODE_MULTIPLY:
            ram[clause.output] = ram[clause.input_A] * ram[clause.input_B];
            break;
        case OPCODE_DIVIDE:
            ram[clause.output] = ram[clause.input_A] / ram[clause.input_B];
            break;
        case OPCODE_POW:
            ram[clause.output] = powf(ram[clause.input_A], ram[clause.input_B]);
            break;
        case OPCODE_MODULO:
            ram[clause.output] = fmodf(ram[clause.input_A], ram[clause.input_B]);
            break;
        case OPCODE_MAXIMAL:
            ram[clause.output] = std::max(ram[clause.input_A] , ram[clause.input_B]);
            break;
        case OPCODE_MINIMAL:
            ram[clause.output] = std::min(ram[clause.input_A] , ram[clause.input_B]);
            break;
        case OPCODE_X:
            ram[clause.output] = X;
            break;
        case OPCODE_Y:
            ram[clause.output] = Y;
            break;
        case OPCODE_Z:
            ram[clause.output] = Z;
            break;
        case OPCODE_SQRT:
            ram[clause.output] = sqrtf(ram[clause.input_A]);
            break;
        case OPCODE_FLOAT:
            ram[clause.output] = clause.value;
            break;
    }
}

#include <glad/glad.h>

TapeBuffer::TapeBuffer(Expr::Tape &tape) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_UNIFORM_BUFFER,id);
}

TapeBuffer::~TapeBuffer() {
    glDeleteBuffers(1,&id);
}

Expr::Tape createTapeFromExprString(std::string &&exprStr) {
    auto expr = ip::Parser(exprStr).parse();
    auto tg = TapeGenerator(std::move(expr));
    auto tape = tg.generate();
    return tape;
}
