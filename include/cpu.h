#pragma once
#include "common.h"
inline void addi(u_int32_t rd, u_int32_t rs1, int32_t imm)
{
    write_gpr(rd, read_gpr(rs1) + (u_int32_t)imm);
}
inline void add(u_int32_t rd, u_int32_t rs1, u_int32_t rs2)
{
    write_gpr(rd, read_gpr(rs1) + read_gpr(rs2));
}
inline void lui(u_int32_t rd, u_int32_t imm32)
{
    write_gpr(rd, imm32);
}
inline void lw(u_int32_t rd, u_int32_t rs1, int32_t imm)
{
    u_int32_t addr = read_gpr(rs1) + (u_int32_t)imm;
    write_gpr(rd, read_memory_word(addr));
}
inline void lbu(u_int32_t rd, u_int32_t rs1, int32_t imm)
{
    u_int32_t addr = read_gpr(rs1) + (u_int32_t)imm;
    u_int32_t byte = read_memory_byte(addr);
    write_gpr(rd, byte & 0xFFU);
}
inline void sw(u_int32_t rs1, u_int32_t rs2, int32_t imm)
{
    u_int32_t addr = read_gpr(rs1) + (u_int32_t)imm;
    write_memory_word(addr, read_gpr(rs2));
}
inline void sb(u_int32_t rs1, u_int32_t rs2, int32_t imm)
{
    u_int32_t addr = read_gpr(rs1) + (u_int32_t)imm;
    write_memory_byte(addr, read_gpr(rs2));
}
inline void jalr(u_int32_t rd, u_int32_t rs1, int32_t imm)
{
    u_int32_t target = (read_gpr(rs1) + (u_int32_t)imm) & ~1U; 
    u_int32_t ret = read_pc() + 4;
    write_gpr(rd, ret);
    write_pc(target); 
}