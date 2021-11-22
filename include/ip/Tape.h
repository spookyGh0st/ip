#ifndef IP_TAPE_H
#define IP_TAPE_H

#include <vector>
#include <cmath>
#include <algorithm>
#include "memory"
#include "Syntax.h"
#include "Clause.h"

class TapeGenerator {
    std::unique_ptr<Expr> expr;
public:
    explicit TapeGenerator(std::unique_ptr<Expr>&& expr);
    Expr::Tape generate();
};

class TapeEmulator{
    Expr::Tape tape ;
    float X, Y, Z;
    int current = 0;
    float ram[UINT8_MAX] {};
    void emulateClause(Clause &clause);
public:
    TapeEmulator(Expr::Tape &tape, float x, float y, float z);
    float emulate();
};


#endif //IP_TAPE_H
