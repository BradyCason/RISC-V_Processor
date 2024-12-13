#ifndef __INSTRUCTION_MEM
#define __iNSTRUCTION_MEM
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "wire.cpp"

class InstructionMemory{
    private:
        std::vector<unsigned int> mem;
    public:
        Wire* address;
        Wire* instruction;
        void execute(){
            *instruction = (mem[address->value()] << 24) + (mem[address->value() + 1] << 16) + (mem[address->value() + 2] << 8) + mem[address->value() + 3];
        }
        InstructionMemory(Wire* a, Wire* i) : address(a), instruction(i) {
            // Read IM
            std::ifstream f("instruction_memory.txt");
            if (f.is_open()){
                std::string line;
                while (std::getline(f, line)) { // Read each line
                    std::stringstream ss1;
                    std::stringstream ss2;
                    std::stringstream ss3;
                    std::stringstream ss4;
                    unsigned int buf;
                    ss1 << std::hex << line.substr(0,2);
                    ss1 >> buf;
                    mem.push_back(buf);
                    buf = 0;
                    ss2 << std::hex << line.substr(2,2);
                    ss2 >> buf;
                    mem.push_back(buf);
                    buf = 0;
                    ss3 << std::hex << line.substr(4,2);
                    ss3 >> buf;
                    mem.push_back(buf);
                    buf = 0;
                    ss4 << std::hex << line.substr(6,2);
                    ss4 >> buf;
                    mem.push_back(buf);
                }
                f.close();
            }
            else{
                std::cout << "Cannot find instruction_memory.txt" << std::endl;
            }
        }
};

#endif