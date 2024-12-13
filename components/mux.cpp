#ifndef __MUX
#define __MUX
#include "wire.cpp"

class Mux{
    private:
        Wire zero;
        Wire one;
        Wire control;
        Wire output;
    public:
        Mux(Wire& z, Wire& o, Wire& ctrl, Wire& out) : zero(z), one(o), control(ctrl), output(o) {}
        void execute(){
            output = control.value() ? one : zero;
        }
};

#endif