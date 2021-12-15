#include <memory>
#include <string>
#include "ip/Syntax.h"

std::string Var::draw() const {
    if (type == VarType::X)
        return "X";
    if (type == VarType::Y)
        return "Y";
    return "Z";
}

uint8_t Var::createTape(TapeInstructions &tape, Stack &stack, TapeConstants &ram) {
    Opcode op; switch (type) {
        case VarType::X: op = OPCODE_X; break;
        case VarType::Y: op = OPCODE_Y; break;
        case VarType::Z: op = OPCODE_Z; break;
    }
    auto out { stack.top() }; stack.pop();

    tape.push_back(Clause(op,out));
    return out;
}

Number::Number(double d) : value{d}{}

std::string Number::draw() const {
    return std::to_string(value);
}

uint8_t Number::createTape(TapeInstructions &tape, Stack &stack, TapeConstants &ram) {
    auto out = stack.top();
    stack.pop();
    ram.emplace_back(float(value));
    auto in = uint8_t(ram.size()-1);
    tape.push_back(Clause(OPCODE_FLOAT,out,in));
    return out;
}

Sqrt::Sqrt(std::unique_ptr<Expr>&& body)
        : body(std::move(body)){}

std::string Sqrt::draw() const {
    return "sqrt(" + body->draw() + ")";
}

uint8_t Sqrt::createTape(TapeInstructions &tape, Stack &stack, TapeConstants &ram) {
    auto bodyOut {body->createTape(tape, stack, ram)};
    stack.push(bodyOut);
    auto out { stack.top() };
    stack.pop();

    tape.push_back(Clause(OPCODE_SQRT,out,bodyOut));
    return out;
}


Binary::Binary(std::unique_ptr<Expr>&& x, std::unique_ptr<Expr>&& y, Operator op)
        : X(std::move(x)), Y(std::move(y)), op(op) {}

std::string Binary::draw() const {
    if(op == Operator::OP_MAXIMAL)
        return "max(" + X->draw() + "," + Y->draw() + ")";
    if(op == Operator::OP_MINIMAL)
        return "min(" + X->draw() + "," + Y->draw() + ")";
    std::string opString;
    if (op == Operator::OP_PLUS) opString = "+";
    else if (op == Operator::OP_MINUS) opString = "-";
    else if (op == Operator::OP_MULTIPLY) opString = "*";
    else if (op == Operator::OP_DIVIDE) opString = "/";
    else if (op == Operator::OP_POW) opString = "^";
    else if (op == Operator::OP_MODULO) opString = "%";
    return "(" + X->draw() + opString + Y->draw() + ")";
}

uint8_t Binary::createTape(TapeInstructions &tape, Stack &stack, TapeConstants &ram) {
    // keep in mind, recursion can kill cpp when the stack is to big
    // use iterative if problems arise
    auto X_out {X->createTape(tape, stack, ram)};
    auto Y_out {Y->createTape(tape, stack, ram)};

    stack.push(Y_out);
    stack.push(X_out);
    auto out { stack.top() };
    stack.pop();

    auto opCode = static_cast<Opcode>(op);
    tape.push_back(Clause(opCode,out,X_out,Y_out));
    return out;
}

// todo
// - instructions printer
// - instructions simulator
// - erstmal ein datentyp mit clause abeiten

// remember alignas to stretch bytes
struct alignas(16) RememberAlignas {
    uint8_t opcode;    // 1 byte
};
// opgengl standard buffer layout std140 std430
