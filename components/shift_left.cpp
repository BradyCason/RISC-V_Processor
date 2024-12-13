#ifndef __SHIFT_LEFT
#define __SHIFT_LEFT
#include "wire.cpp"

class ShiftLeft{
    private:
        Wire in;
        Wire out;
    public:
        ShiftLeft(Wire& i, Wire& o) : in(i), out(o) {}
        void execute(){
            out = (in.value() << 1);
        }
};

#endif