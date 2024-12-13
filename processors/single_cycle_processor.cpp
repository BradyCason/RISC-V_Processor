#ifndef __SINGLE_CYCLE_PROCESSOR
#define __SINGLE_CYCLE_PROCESSOR
#include "instruction_memory.cpp"
#include "register_file.cpp"
#include "control_unit.cpp"
#include "immediate_generator.cpp"
#include "mux.cpp"
#include "alu.cpp"
#include "data_memory.cpp"
#include "adder.cpp"
#include "alu_control.cpp"
#include "pc.cpp"
#include "shift_left.cpp"
#include "and_gate.cpp"
#include "wire.cpp"

#define PC_SIZE 10

class SingleCycleProcessor{
    private:
        // Define wires
        Wire instruction = Wire(32);
        Wire address = Wire(PC_SIZE);
        Wire pc_in = Wire(PC_SIZE);
        Wire write_data = Wire(64);
        Wire reg_write = Wire(1);
        Wire alu_in1 = Wire(64);
        Wire alu_in2 = Wire(64);
        Wire read_data2 = Wire(64);
        Wire branch = Wire(1);
        Wire mem_to_reg = Wire(1);
        Wire mem_read = Wire(1);
        Wire alu_op = Wire(2);
        Wire mem_write = Wire(1);
        Wire alu_src = Wire(1);
        Wire imm_out = Wire(64);
        Wire alu_control = Wire(4);
        Wire zero = Wire(1);
        Wire alu_result = Wire(64);
        Wire read_data = Wire(64);
        Wire sl_out = Wire(65);
        Wire pc0 = Wire(PC_SIZE);
        Wire pc1 = Wire(PC_SIZE);
        Wire pc_src = Wire(PC_SIZE);

        // Define Components
        PC pc;
        InstructionMemory im;
        RegisterFile rf;
        ControlUnit cu;
        ImmediateGenerator ig;
        ALU alu;
        Mux alu_mux;
        ALUController alu_ctrl;
        DataMemory dm;
        Mux dm_mux;
        Mux pc_mux;
        Adder adder1;
        Adder adder2;
        AndGate and_gate;
        ShiftLeft sl;

    public:
        SingleCycleProcessor() : im(address, instruction), rf(instruction, write_data, reg_write, alu_in1, write_data),
                cu(instruction, branch, mem_read, mem_to_reg, alu_op, mem_write, alu_src, reg_write),
                ig(instruction, imm_out), alu(alu_in1, alu_in2, alu_control, zero, alu_result),
                alu_mux(write_data, imm_out, alu_src, alu_in2), alu_ctrl(instruction, alu_op, alu_control),
                dm(alu_result, write_data, mem_write, mem_read, read_data),
                dm_mux(read_data, alu_result, mem_to_reg, write_data), pc(pc_in, address), adder1(4, address, pc0),
                adder2(address, sl_out, pc1), pc_mux(pc0, pc1, pc_src, pc_in), and_gate(branch, zero, pc_src),
                sl(imm_out, sl_out){
            pc.set(0);
        }
        void clock(){
            // high
            pc.execute();
            im.execute();
            rf.execute_falling_edge();
            cu.execute();
            ig.execute();
            sl.execute();
            alu_mux.execute();
            alu_ctrl.execute();
            alu.execute();
            and_gate.execute();
            dm.execute();
            dm_mux.execute();
            adder1.execute();
            adder2.execute();
            pc_mux.execute();

            // low
            rf.execute_rising_edge(); // switch after pipelining
        }
};

#endif