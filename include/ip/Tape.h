#ifndef IP_TAPE_H
#define IP_TAPE_H

#include <vector>
#include <cmath>
#include <algorithm>
#include "memory"
#include "Syntax.h"
#include "Clause.h"
#include "Parser.hpp"

struct Tape {
    Expr::TapeInstructions instructions;
    Expr::TapeConstants constants;
};

class TapeGenerator {
    std::unique_ptr<Expr> expr;
public:
    explicit TapeGenerator(std::unique_ptr<Expr>&& expr);
    Tape generate();
};

class TapeEmulator{
    Tape tape ;
    float X, Y, Z;
    int current = 0;
    float ram[UINT8_MAX] {};
    void emulateClause(Clause &clause);
public:
    TapeEmulator(const Tape& tape, float x, float y, float z);
    float emulate();
};

Tape createTapeFromExprString(std::string &&exprStr);


#endif //IP_TAPE_H
