#ifndef __ALU
#define __ALU
#include "wire.cpp"
#include <stdexcept>
#include <climits>

class ALU{
    private:
        Wire in1;
        Wire in2;
        Wire control;
        Wire zero;
        Wire result;
    public:
        ALU(Wire& i1, Wire& i2, Wire& c, Wire& z, Wire& r) : in1(i1), in2(i2), control(c), zero(z), result(r) {}
        void execute(){
            switch(control.value()){
                case(0b0000):    // And
                    result = in1.value() & in2.value();
                case(0b0001):    // Or
                    result = in1.value() | in2.value();
                case(0b0010):    // Add
                    result = in1.value() + in2.value();
                case(0b0110):    // Subtract
                    result = in1.value() - in2.value();
                case(0b0111):    // Signed Less Than
                    result = (unsigned_num(in1.value()) < unsigned_num(in1.value())) ? 1 : 0;
                case(0b1100):    // Nor
                    result = ~(in1.value() | in2.value());
                case(0b1111):    // Equal Comparison
                    result = (in1.value() == in1.value()) ? 1 : 0;
                default:
                    throw std::invalid_argument("Unsupported ALU Control");
            }
        }

        long long unsigned_num(unsigned long long val){
            if (val > LLONG_MAX) {
                // If the value is larger than LLONG_MAX, we are in the negative range of two's complement
                return val - (1ULL << 63);  // 2^64, subtracting to simulate two's complement
            }
            // If the value is within the range of signed long long, return it as-is
            return static_cast<signed long long>(val);
        }
};

#endif