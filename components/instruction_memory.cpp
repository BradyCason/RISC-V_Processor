#ifndef __INSTRUCTION_MEM
#define __iNSTRUCTION_MEM
#include <vector>
#include "wire.cpp"

class InstructionMemory{
    private:
        std::vector<unsigned int> mem;
    public:
        Wire address;
        Wire instruction;
        void execute(){
            instruction = (mem[address.value()] << 24) + (mem[address.value() + 1] << 16) + (mem[address.value() + 2] << 8) + mem[address.value() + 3];
        }
        InstructionMemory(Wire& a, Wire& i) : address(a), instruction(i) {
            // Read IM

        }
};

#endif