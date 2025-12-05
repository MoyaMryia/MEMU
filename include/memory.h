#pragma once
#include "common.h"
//GPRs
u_int32_t read_gpr(u_int32_t address);
void write_gpr(u_int32_t address, u_int32_t data);
//Memory
u_int32_t read_memory_word(u_int32_t address);
void write_memory_word(u_int32_t address, u_int32_t data);
u_int32_t read_memory_byte(u_int32_t address);
void write_memory_byte(u_int32_t address, u_int32_t data);
//PC_GPR
u_int32_t get_pc();
void increment_pc();
u_int32_t fetch_instruction();
void write_pc(u_int32_t data);
//PC_clock

void increment_pc_clock();
u_int64_t read_pc_clock();