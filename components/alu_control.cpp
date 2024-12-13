#ifndef __ALU_CONTROLLER
#define __ALU_CONTROLLER
#include "wire.cpp"

class ALUController{
    private:
        Wire* instruction;
        Wire* alu_op;
        Wire* operation;
    public:
        ALUController(Wire* i, Wire* a, Wire* r) : instruction(i), alu_op(a), operation(r) {}
        void execute(){
            int funct7 = instruction->slice(31, 25).value();
            int funct3 = instruction->slice(14, 12).value();
            switch(alu_op->value()){
                case(0b00):
                    switch(funct3){
                        case(0b000):
                            *operation = 0b0010;
                        case(0b010):
                            *operation = 0b0111;
                        case(0b100):
                            *operation = 0b1100;
                        case(0b110):
                            *operation = 0b0001;
                        case(0b111):
                            *operation = 0b000;
                    }
                case(0b01):
                    *operation = 0010;
                case(0b10):
                    switch(funct3){
                        case(0b000):
                            switch(funct7){
                                case(0b0100000):
                                    *operation = 0b0110;
                                case(0b0000000):
                                    *operation = 0b0010;
                            }
                        case(0b010):
                            *operation = 0b0111;
                        case(0b100):
                            *operation = 0b1100;
                        case(0b110):
                            *operation = 0b0001;
                        case(0b111):
                            *operation = 0b000;
                    }
                case(0b11):
                default:
                    throw std::invalid_argument("ALU operation not found");
            }
        }
};

#endif