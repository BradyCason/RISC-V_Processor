#ifndef __IMM_GEN
#define __IMM_GEN
#include "wire.cpp"

class ImmediateGenerator{
    private:
        Wire* instruction;
        Wire* out;
    public:
        ImmediateGenerator(Wire* i, Wire* o) : instruction(i), out(o) {}
        void execute(){
            int inst = instruction->value();
            unsigned long long output;
            switch(instruction->slice(6, 0).value()){
                case(0b0000011):    // I-type - Load
                    if (inst & (1 << 31)){
                        output = (0xFFFFFFFFFFFFF000) | (inst >> 20);
                    }
                    else{
                        output = inst >> 20;
                    }
                case(0b0010011):    // I-type - non-Load
                    if (inst & (1 << 31)) {
                        output = (0xFFFFFFFFFFFFF000) | (inst >> 20);
                    } else {
                        output = inst >> 20;
                    }
                case(0b0100011):    // S-type - store
                    if (inst & (1 << 31)) {
                        output = (0xFFFFFFFFFFFFF000) | ((inst >> 25) << 5) | ((inst >> 7) - ((inst >> 12) << 5));
                    } else {
                        output = ((inst >> 25) << 5) | ((inst >> 7) - ((inst >> 12) << 5));
                    }

                    output = (output << 5) | ((inst >> 7) & 0x1F);
                case(0b0010111):    // U-type
                    output = (inst >> 12) << 12;
                default:
                    output = 0;
            }
            *out = output;
        }
};

#endif