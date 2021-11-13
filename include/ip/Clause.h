

#ifndef IP_CLAUSE_H
#define IP_CLAUSE_H

enum Opcode: unsigned char{
    foo = 0,
    bar = 5,
};
struct Clause {
    Opcode opcode;      // 1 byte
    uint8_t output;   // 1 byte
};
struct Binary_Clause: public Clause {
    uint8_t input_A;  // 1 byte
    uint8_t input_B;  // 1 byte
    int padding;        // 4 byte
};
struct Float_Clause: public Clause {
    uint8_t padding1;  // 1 byte
    uint8_t padding2;  // 1 byte
    float value;      // 4 byte
};

#include <vector>
#include "memory"
#include "Syntax.h"

#endif //IP_CLAUSE_H
