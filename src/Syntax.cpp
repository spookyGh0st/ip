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

uint8_t Var::createTape(Tape &tape, Stack &stack) {
    // todo
}

Number::Number(double d) : value{d}{}

std::string Number::draw() const {
    return std::to_string(value);
}

uint8_t Number::createTape(Tape &tape, Stack &stack) {
    auto out = stack.top();
    stack.pop();
    auto clause = std::make_unique<Float_Clause>();
    clause->output = out;
    clause->value = float(value);
    tape.push_back(std::move(clause));
    return out;
}

Sqrt::Sqrt(std::unique_ptr<Expr>&& body)
        : body(std::move(body)){}

std::string Sqrt::draw() const {
    return "sqrt(" + body->draw() + ")";
}

uint8_t Sqrt::createTape(Expr::Tape &tape, Stack &stack) {
    // todo
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

uint8_t Binary::createTape(Expr::Tape &tape, Stack &stack) {
    auto X_out { X->createTape(tape, stack) };
    auto Y_out { Y->createTape(tape, stack) };

    stack.push(X_out);
    stack.push(Y_out);
    auto out { stack.top() };
    stack.pop();

    auto clause = std::make_unique<Binary_Clause>();
    clause->input_A = X_out;
    clause->input_B = Y_out;
    clause->opcode = static_cast<Opcode>(op);
    clause->output = out;

    tape.push_back(std::move(clause));
    return out;
}

