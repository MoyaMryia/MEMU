#include "common.h"

void addi(u_int32_t rd, u_int32_t rs1, int32_t imm){
    u_int32_t data = read_gpr(rs1) + imm;
    write_gpr(rd,data);
    increment_pc();
    return ;
}

void jalr(u_int32_t rd, u_int32_t rs1, int32_t imm){
    u_int32_t data = read_pc() + 0x4;
    write_pc((read_gpr(rs1) + imm) & 0xfffffffc);
    write_gpr(rd, data);
    return ;
}

void add(u_int32_t rd,u_int32_t rs1, u_int32_t rs2){
    u_int32_t data = read_gpr(rs1) + read_gpr(rs2);
    write_gpr(rd,data);
    increment_pc();
}

void lui(u_int32_t rd, u_int32_t imm){
    //imm is pre-extended
    write_gpr(rd, imm);
    increment_pc();
}