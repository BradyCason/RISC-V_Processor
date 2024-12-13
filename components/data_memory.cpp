#ifndef __DATA_MEMORY
#define __DATA_MEMORY
#include "wire.cpp"

class DataMemory{
    private:
        Wire address;
        Wire write_data;
        Wire mem_write;
        Wire mem_read;
        Wire read_data;

        unsigned long long mem[128];
    public:
        DataMemory(Wire& a, Wire& wd, Wire& mw, Wire& mr, Wire& rd) : address(a), 
                write_data(wd), mem_write(mw), mem_read(mr), read_data(rd) {}
        void execute(){
            if (mem_write.value()){
                mem[address.slice(8,2).value()] = write_data.value();
            }

            if (mem_read.value()){
                read_data = mem[address.slice(8,2).value()];
            }
        }
};

#endif