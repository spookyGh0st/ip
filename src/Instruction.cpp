

#include "ip/Instruction.hpp"

void testMemory() {
    Binary_Clause bc {
            Opcode::foo,
            std::byte{1},
            std::byte{2},
            std::byte{3},
            0
    };
    Float_Clause fc {
            Opcode::bar,
            std::byte{1},
            std::byte{2},
            4.0
    };
    std::cout << sizeof(bc) << std::endl;
    std::cout << sizeof(fc) << std::endl;
}
