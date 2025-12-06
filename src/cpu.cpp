#include "../include/cpu.h"
#include <bitset>
#include <iostream>
int32_t sign_extend(u_int32_t imm, int bits)
{
    int32_t shift = 32 - bits;
    return (int32_t)(imm << shift) >> shift;
}
void runMain(u_int32_t operate, bool printer)
{
    u_int32_t opcode = operate & 0x7F;
    u_int32_t rd = (operate >> 7) & 0x1F;
    u_int32_t funct3 = (operate >> 12) & 0x7;
    u_int32_t rs1 = (operate >> 15) & 0x1F;
    u_int32_t rs2 = (operate >> 20) & 0x1F;
    u_int32_t funct7 = (operate >> 25) & 0x7F;
    if (opcode == 0b0010011 && funct3 == 0b000)
    { // addi
        int32_t imm = sign_extend(operate >> 20, 12);
        if (printer)
            std::cout << "addi x" << rd << ", x" << rs1 << ", " << imm << std::endl;
        addi(rd, rs1, imm);
    }
    else if (opcode == 0b1100111 && funct3 == 0b000)
    { // jalr
        int32_t imm = sign_extend(operate >> 20, 12);
        if (printer)
            std::cout << "jalr x" << rd << ", " << imm << "(x" << rs1 << ")" << std::endl;
        jalr(rd, rs1, imm);
        return; 
    }
    else if (opcode == 0b0110011 && funct3 == 0b000 && funct7 == 0b0000000)
    { // add
        if (printer)
            std::cout << "add x" << rd << ", x" << rs1 << ", x" << rs2 << std::endl;
        add(rd, rs1, rs2);
    }
    else if (opcode == 0b0110111)
    {                                         // lui
        u_int32_t imm = operate & 0xFFFFF000; 
        if (printer)
            std::cout << "lui x" << rd << ", 0x" << std::hex << (imm >> 12) << std::dec << std::endl;
        lui(rd, imm);
    }
    else if (opcode == 0b0000011)
    { // lw / lbu
        int32_t imm = sign_extend(operate >> 20, 12);
        if (funct3 == 0b010)
        { // lw
            if (printer)
                std::cout << "lw x" << rd << ", " << imm << "(x" << rs1 << ")" << std::endl;
            lw(rd, rs1, imm);
        }
        else if (funct3 == 0b100)
        { // lbu
            if (printer)
                std::cout << "lbu x" << rd << ", " << imm << "(x" << rs1 << ")" << std::endl;
            lbu(rd, rs1, imm);
        }
        else
        {
            goto ERROR;
        }
    }
    else if (opcode == 0b0100011)
    { // sw / sb  (S-type)
        u_int32_t imm_raw = ((operate >> 25) & 0x7F) << 5 | ((operate >> 7) & 0x1F);
        int32_t imm = sign_extend(imm_raw, 12);
        if (funct3 == 0b000)
        { // sb
            if (printer)
                std::cout << "sb x" << rs2 << ", " << imm << "(x" << rs1 << ")" << std::endl;
            sb(rs1, rs2, imm);
        }
        else if (funct3 == 0b010)
        { // sw
            if (printer)
                std::cout << "sw x" << rs2 << ", " << imm << "(x" << rs1 << ")" << std::endl;
            sw(rs1, rs2, imm);
        }
        else
        {
            goto ERROR;
        }
    }
    else
    {
        goto ERROR;
    }
    if (opcode != 0b1100111)
    { 
        increment_pc();
    }
    return;
ERROR:
    std::cout << "Unsupported instruction! PC=0x" << std::hex << read_pc()
              << " inst=0x" << operate << std::dec << std::endl;
}