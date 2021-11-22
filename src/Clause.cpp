#include "ip/Clause.h"

Clause::Clause(Opcode opcode, uint8_t output, uint8_t inputA, uint8_t inputB)
    : opcode(opcode), output(output), input_A(inputA), input_B(inputB) {}

Clause::Clause(Opcode opcode, uint8_t output, float value)
    : opcode(opcode), output(output), value(value) {}

Clause::Clause(Opcode opcode, uint8_t output, uint8_t inputA)
    : opcode(opcode), output(output), input_A(inputA) {}
Clause::Clause(Opcode opcode, uint8_t output)
        : opcode(opcode), output(output)  {}

std::string Clause::print() const {
    return std::to_string(opcode) + "\t" + std::to_string(output) + "\t" + std::to_string(input_A) + "\t" + std::to_string(input_B) + "\t" + std::to_string(value);
}
