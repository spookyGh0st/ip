#include <memory>
#include "ip/Syntax.hpp"
#include <string>
#include "ip/GeometricalObject.hpp"

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


Sqrt::Sqrt(std::unique_ptr<Expr> body)
        : body(std::move(body)){}

std::string Sqrt::draw() const {
    return "sqrt(" + body->draw() + ")";
}


Binary::Binary(std::unique_ptr<Expr> x, std::unique_ptr<Expr> y)
        : X(std::move(x)), Y(std::move(y)) {}

std::string Plus::draw() const {
    return "(" + X->draw() + "+" + Y->draw() + ")";
}

std::string Minus::draw() const {
    return "(" + X->draw() + "-" + Y->draw() + ")";
}

std::string Multiply::draw() const {
    return "(" + X->draw() + "+" + Y->draw() + ")";
}

std::string Divide::draw() const {
    return "(" + X->draw() + "/" + Y->draw() + ")";
}

std::string Pow::draw() const {
    return "(" + X->draw() + "^" + Y->draw() + ")";
}

std::string Max::draw() const {
    return "max(" + X->draw() + "," + Y->draw() + ")";
}

std::string Min::draw() const {
    return "min(" + X->draw() + "," + Y->draw() + ")";
}

