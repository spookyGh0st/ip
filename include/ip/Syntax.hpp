#include <string>
#include <memory>

#ifndef IP_SYNTAX_HPP
#define IP_SYNTAX_HPP

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

    explicit Sqrt(std::unique_ptr<Expr> body);

    [[nodiscard]] std::string draw() const override;
};

class Binary{
public:
    std::unique_ptr<Expr> X;
    std::unique_ptr<Expr> Y;
    Binary(std::unique_ptr<Expr> x, std::unique_ptr<Expr> y);
    ~Binary() = default;
};

struct Plus: Expr, Binary{
    using Binary::Binary;
    [[nodiscard]] std::string draw() const override;
};

struct Minus: Expr, Binary{
    using Binary::Binary;
    [[nodiscard]] std::string draw() const override;
};

struct Multiply: Expr, Binary{
    using Binary::Binary;
    [[nodiscard]] std::string draw() const override;
};

struct Divide: Expr, Binary{
    using Binary::Binary;
    [[nodiscard]] std::string draw() const override;
};

struct Pow: Expr, Binary{
    using Binary::Binary;
    [[nodiscard]] std::string draw() const override;
};

struct Max: Expr, Binary{
    using Binary::Binary;
    [[nodiscard]] std::string draw() const override;
};

struct Min: Expr, Binary{
    using Binary::Binary;
    [[nodiscard]] std::string draw() const override;
};

#include <memory>

#endif //IP_SYNTAX_HPP
