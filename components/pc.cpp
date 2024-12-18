#ifndef __PC
#define __PC
#include "wire.cpp"
#include <iostream>

class PC{
    private:
        Wire* in;
        Wire* out;

        unsigned long long mem[128];
    public:
        PC(Wire* i, Wire* o) : in(i), out(o) {}
        void execute(){
            out = in;
            std::cout << out->value() << std::endl;
        }

        void set(int val){
            *out = val;
        }
};

#endif