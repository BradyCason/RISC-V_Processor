#ifndef __AND_GATE
#define __AND_GATE
#include "wire.cpp"

class AndGate{
    private:
        Wire in1;
        Wire in2;
        Wire out;
    public:
        AndGate(Wire& i1, Wire& i2, Wire& o) : in1(i1), in2(i2), out(o) {}
        void execute(){
            out = (in1.value() & in2.value());
        }
};

#endif