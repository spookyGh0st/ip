#include <memory>
#include "Syntax.hpp"

class Expr {
public:
    [[nodiscard]] virtual std::string draw() const = 0;
    virtual ~Expr() = default; // Book Virtual Destructors
};

enum VarType{ X, Y, Z };

class Var:public Expr{
public:
    VarType type;
    explicit Var(VarType type) : type(type) {}

private:
    [[nodiscard]] std::string draw() const override;
};

std::string Var::draw() const {
    if (type == VarType::X)
        return "X";
    if (type == VarType::Y)
        return "Y";
    return "Z";
}

class Number: public Expr{
public:
    explicit Number(double d);;
    double value;

    [[nodiscard]] std::string draw() const override;
};

std::string Number::draw() const {
    return std::to_string(value);
}

Number::Number(double d) : value{d}{}

class Sqrt: public Expr{
public:
    std::unique_ptr<Expr> body;

    explicit Sqrt(std::unique_ptr<Expr> body);

    [[nodiscard]] std::string draw() const override;
};

std::string Sqrt::draw() const {
    return "sqrt(" + body->draw() + ")";
}

Sqrt::Sqrt(std::unique_ptr<Expr> body)
        : body(std::move(body)){}

class Binary{
public:
    std::unique_ptr<Expr> X;
    std::unique_ptr<Expr> Y;
    Binary(std::unique_ptr<Expr> x, std::unique_ptr<Expr> y);
    ~Binary() = default;
};

Binary::Binary(std::unique_ptr<Expr> x, std::unique_ptr<Expr> y)
        : X(std::move(x)), Y(std::move(y)) {}

struct Plus: Expr, Binary{
    using Binary::Binary;
    [[nodiscard]] std::string draw() const override;
};

std::string Plus::draw() const {
    return "(" + X->draw() + "+" + Y->draw() + ")";
}

struct Minus: Expr, Binary{
    using Binary::Binary;
    [[nodiscard]] std::string draw() const override;
};

std::string Minus::draw() const {
    return "(" + X->draw() + "-" + Y->draw() + ")";
}

struct Multiply: Expr, Binary{
    using Binary::Binary;
    [[nodiscard]] std::string draw() const override;
};

std::string Multiply::draw() const {
    return "(" + X->draw() + "+" + Y->draw() + ")";
}

struct Divide: Expr, Binary{
    using Binary::Binary;
    [[nodiscard]] std::string draw() const override;
};

std::string Divide::draw() const {
    return "(" + X->draw() + "/" + Y->draw() + ")";
}

struct Pow: Expr, Binary{
    using Binary::Binary;
    [[nodiscard]] std::string draw() const override;
};

std::string Pow::draw() const {
    return "(" + X->draw() + "^" + Y->draw() + ")";
}

struct Max: Expr, Binary{
    using Binary::Binary;
    [[nodiscard]] std::string draw() const override;
};

std::string Max::draw() const {
    return "max(" + X->draw() + "," + Y->draw() + ")";
}

struct Min: Expr, Binary{
    using Binary::Binary;
    [[nodiscard]] std::string draw() const override;
};

std::string Min::draw() const {
    return "min(" + X->draw() + "," + Y->draw() + ")";
}

class GeometricalObject {
public:
    std::unique_ptr<Expr> range;
};

class Sphere : public GeometricalObject {
public:
    explicit Sphere(double radius) {
        auto a = std::make_unique<int>(5);

        // jesus fucking christ
        // this is sqrt(x^2 + y^2 + z^2) + n
        range = std::make_unique<Plus>(
                std::make_unique<Sqrt>(
                        std::make_unique<Plus>(
                                std::make_unique<Pow>(
                                        std::make_unique<Var>(X),
                                        std::make_unique<Number>(2.0)),
                                std::make_unique<Plus>(
                                        std::make_unique<Pow>(
                                                std::make_unique<Var>(Y),
                                                std::make_unique<Number>(2.0)),
                                        std::make_unique<Pow>(
                                                std::make_unique<Var>(Z),
                                                std::make_unique<Number>(2.0))
                                )
                        )
                ),
                std::make_unique<Number>(radius)
        );
    }
};
