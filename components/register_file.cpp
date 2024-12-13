#ifndef __REGISTER_FILE
#define __REGISTER_FILE
#include "wire.cpp"

class RegisterFile{
    private:
        unsigned long long reg[32];
    public:
        Wire instruction;
        Wire write_data;
        Wire reg_write;
        Wire read_data1;
        Wire read_data2;
    void execute_rising_edge(){
        if (reg_write.value()){
            reg[instruction.slice(11, 7).value()] = write_data.value();
        }
    }
    void execute_falling_edge(){
        read_data1 = reg[instruction.slice(19, 15).value()];
        read_data2 = reg[instruction.slice(24, 20).value()];
    }

    RegisterFile(Wire& i, Wire& wd, Wire& rw, Wire& rd1, Wire& rd2) : instruction(i), write_data(wd), reg_write(rw), read_data1(rd1), read_data2(rd2) {}
};

#endif