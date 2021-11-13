#ifndef IP_SYNTAX_HPP
#define IP_SYNTAX_HPP

#include <string>
#include <memory>

// todo namespaces

enum VarType{ X, Y, Z };

class Expr {
public:
    [[nodiscard]] virtual std::string draw() const = 0;
    virtual ~Expr() = default; // Book Virtual Destructors
};

class Var:public Expr{
public:
    VarType type;
    explicit Var(VarType type) : type(type) {}

private:
    [[nodiscard]] std::string draw() const override;
};

class Number: public Expr{
public:
    explicit Number(double d);
    double value;

    [[nodiscard]] std::string draw() const override;
};

class Sqrt: public Expr{
public:
    std::unique_ptr<Expr> body;

    explicit Sqrt(std::unique_ptr<Expr>&& body);

    [[nodiscard]] std::string draw() const override;
};

enum class Operator{
    OP_PLUS = 0,
    OP_MINUS = 1,
    OP_MULTIPLY = 2,
    OP_DIVIDE = 3,
    OP_POW = 4,
    OP_MODULO = 5,
    OP_MAXIMAL = 6,
    OP_MINIMAL = 7,
};

class Binary: public Expr {
public:
    std::unique_ptr<Expr> X;
    std::unique_ptr<Expr> Y;
    Operator op;
    Binary(std::unique_ptr<Expr>&& x, std::unique_ptr<Expr>&& y, Operator op);
    [[nodiscard]] std::string draw() const override;
};


#include <memory>

#endif //IP_SYNTAX_HPP
