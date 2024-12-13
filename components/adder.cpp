#ifndef __ADDER
#define __ADDER
#include "wire.cpp"

class Adder{
    private:
        int i;
        Wire a;
        Wire b;
        Wire output;
    public:
        Adder(Wire& c, Wire& d, Wire& out) : i(0), a(c), b(d), output(out) {}
        Adder(int c, Wire& d, Wire& out) : i(c), a(d), b(d), output(out) {}
        void execute(){
            if (i) output = i + b.value();
            else output = a.value() + b.value();
        }
};

#endif