#ifndef IP_CLAUSE_H
#define IP_CLAUSE_H

#include <vector>
#include "memory"

enum Opcode: uint8_t {
    OPCODE_PLUS = 0,
    OPCODE_MINUS = 1,
    OPCODE_MULTIPLY = 2,
    OPCODE_DIVIDE = 3,
    OPCODE_POW = 4,
    OPCODE_MODULO = 5,
    OPCODE_MAXIMAL = 6,
    OPCODE_MINIMAL = 7,

    OPCODE_X = 8,
    OPCODE_Y = 9,
    OPCODE_Z = 10,

    OPCODE_SQRT = 11,
    OPCODE_FLOAT = 12,
};

class alignas(4) Clause {
public:
    Opcode opcode;    // 1 byte
    uint8_t output;   // 1 byte
    uint8_t input_A{};  // 1 byte
    uint8_t input_B{};  // 1 byte
    // float value{};      // 4 byte
    Clause(Opcode opcode, uint8_t output, uint8_t inputA, uint8_t inputB);
    Clause(Opcode opcode, uint8_t output, uint8_t inputA);
    Clause(Opcode opcode, uint8_t output);
    [[nodiscard]] std::string print() const;
};


#endif //IP_CLAUSE_H
