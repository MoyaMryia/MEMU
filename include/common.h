#pragma once
#include <assert.h>
#include <iostream>
#include <string.h>
#include <cstdio>
#include "memory.h"

void startMonitor(int argc,char **argv);
void startShell();
void runMain(u_int32_t operate,bool printer);
int32_t sign_extend(u_int32_t imm, int bits);

void run_cycle();
void printStatus();