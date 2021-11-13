#include <memory>
#include <string>
#include "ip/Syntax.hpp"

std::string Var::draw() const {
    if (type == VarType::X)
        return "X";
    if (type == VarType::Y)
        return "Y";
    return "Z";
}

Number::Number(double d) : value{d}{}

std::string Number::draw() const {
    return std::to_string(value);
}


Sqrt::Sqrt(std::unique_ptr<Expr>&& body)
        : body(std::move(body)){}

std::string Sqrt::draw() const {
    return "sqrt(" + body->draw() + ")";
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

