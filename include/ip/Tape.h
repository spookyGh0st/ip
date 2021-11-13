#ifndef IP_TAPE_H
#define IP_TAPE_H

#include <vector>
#include "memory"
#include "Syntax.h"
#include "Clause.h"

class TapeGenerator {
    std::unique_ptr<Expr> expr;
public:
    explicit TapeGenerator(std::unique_ptr<Expr>&& expr);
    Expr::Tape generate();
};


#endif //IP_TAPE_H
