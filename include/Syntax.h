#ifndef IP_SYNTAX_H
#define IP_SYNTAX_H

#include <string>
#include <memory>
#include <stack>
#include "Clause.h"

enum VarType{ X, Y, Z };

class Expr {
public:
    using TapeInstructions = std::vector<Clause>;
    using Stack = std::stack<uint8_t>;
    using TapeConstants = std::vector<float>;

    [[nodiscard]] virtual std::string draw() const = 0;
    virtual uint8_t createTape(TapeInstructions &tape, Stack &stack, TapeConstants &ram) = 0;
    virtual ~Expr() = default; // Book Virtual Destructors
};

class Var:public Expr{
public:
    VarType type;
    explicit Var(VarType type) : type(type) {}
    [[nodiscard]] std::string draw() const override;
    uint8_t createTape(TapeInstructions &tape, Stack &stack, TapeConstants &ram) override;
};

class Number: public Expr{
public:
    explicit Number(double d);
    double value;

    [[nodiscard]] std::string draw() const override;

    uint8_t createTape(TapeInstructions &tape, Stack &stack, TapeConstants &ram) override;
};

class Sqrt: public Expr{
public:
    std::unique_ptr<Expr> body;
    explicit Sqrt(std::unique_ptr<Expr>&& body);
    [[nodiscard]] std::string draw() const override;

    uint8_t createTape(TapeInstructions &tape, Stack &stack, TapeConstants &ram) override;
};

// the values translate to the opCodes and are used both in the syntax tree and the instructions.
enum Operator{
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
    uint8_t createTape(TapeInstructions &tape, Stack &stack, TapeConstants &ram) override;
};


#include <memory>

#endif //IP_SYNTAX_H
