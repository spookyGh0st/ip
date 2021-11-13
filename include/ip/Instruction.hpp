

#ifndef IP_INSTRUCTION_HPP
#define IP_INSTRUCTION_HPP

#include <cstddef>
#include <iostream>

enum class Opcode: unsigned char{
    foo = 0,
    bar = 5,
};

struct Clause {
    Opcode opcode;      // 1 byte
    std::byte output;   // 1 byte
};
struct Binary_Clause: public Clause {
    std::byte input_A;  // 1 byte
    std::byte input_B;  // 1 byte
    int padding;        // 4 byte
};

struct Float_Clause: public Clause {
    std::byte input_A;
    float input_B;
};
void testMemory();


#endif //IP_INSTRUCTION_HPP

// ich loope durch, alokiere slots mit den output + input


