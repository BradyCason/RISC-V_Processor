#ifndef __CONTROL_UNIT
#define __CONTROL_UNIT
#include "wire.cpp"
#include <stdexcept>
#include <string>
#include <iostream>

inline std::string intToBinary(int num) {
    if (num == 0) return "0"; // Special case for 0

    std::string binary = "";
    while (num > 0) {
        binary = (num % 2 == 0 ? "0" : "1") + binary; // Append the bit at the beginning
        num /= 2; // Shift the number to the right
    }
    return binary;
}

class ControlUnit{
    private:
        Wire* instruction;
        Wire* branch;
        Wire* mem_read;
        Wire* mem_to_reg;
        Wire* alu_op;
        Wire* mem_write;
        Wire* alu_src;
        Wire* reg_write;
    public:
        ControlUnit(Wire* i, Wire* b, Wire* mr, Wire* mtr, Wire* ao, Wire* mw, Wire* as, Wire* rw) : instruction(i), 
                branch(b), mem_read(mr), mem_to_reg(mtr), alu_op(ao), mem_write(mw), alu_src(as), reg_write(rw){}
        void execute(){
            unsigned int opcode = instruction->slice(6, 0).value();
            std::cout << instruction->value();

            switch (opcode){
                case 0b0110011:    // R-type
                    *branch = 0;
                    *mem_read = 0;
                    *mem_to_reg = 0;
                    *alu_op = 0b10;
                    *mem_write = 0;
                    *alu_src = 0;
                    *reg_write = 1;
                case 0b0010011:    // I-type
                    *branch = 0;
                    *mem_read = 0;
                    *mem_to_reg = 0;
                    *alu_op = 0b00;
                    *mem_write = 0;
                    *alu_src = 1;
                    *reg_write = 1;
                case 0b0000011:    // Load
                    *branch = 0;
                    *mem_read = 1;
                    *mem_to_reg = 1;
                    *alu_op = 0b01;
                    *mem_write = 0;
                    *alu_src = 1;
                    *reg_write = 1;
                case 0b0100011:    // Store
                    *branch = 0;
                    *mem_read = 0;
                    *mem_to_reg = 0;
                    *alu_op = 0b01;
                    *mem_write = 1;
                    *alu_src = 1;
                    *reg_write = 0;
                default:
                    throw std::invalid_argument("Unsupported opcode: " + intToBinary(opcode));
            }
        }
};

#endif