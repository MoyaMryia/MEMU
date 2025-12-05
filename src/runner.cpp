#include "../include/common.h"

int32_t sign_extend(u_int32_t imm, int bits) {
    if ((imm >> (bits - 1)) & 1) {
        return (int32_t)(imm | (~((1 << bits) - 1)));
    } else {
        return (int32_t)imm;
    }
}

void runMain(u_int32_t operate){
    u_int32_t opcode = operate & 0b1111111;
    u_int32_t rd = (operate >> 7) & 0b11111;
    u_int32_t funct3 = (operate >> 12) & 0b111;
    u_int32_t rs1 = (operate >> 15) & 0b11111;
    u_int32_t rs2 = (operate >> 20) & 0b11111;
    u_int32_t funct7 = (operate >>25) & 0b1111111;

    if(opcode == 0b0010011 && funct3 == 0b000){ 
        //addi
        int32_t imm = sign_extend(operate>>20,12);
        std::cout<<"addi x"<<rd<<",x"<<rs1<<","<<imm<<std::endl;

    }else if(opcode == 0b1100111 && funct3 == 0b000){
        //jalr
        int32_t imm = sign_extend(operate>>20,12);
        std::cout<<"jalr x"<<rd<<","<<imm<<"(x"<<rs1<<")"<<std::endl;
    }else if(opcode == 0b0110011 && funct3 == 0b000 && funct7 == 0b0000000){
        //add
        std::cout<<"add x"<<rd<<",x"<<rs1<<",x"<<rs2<<std::endl;

    }else if(opcode == 0b0110111){
        //lui
        int32_t imm = operate & 0xFFFFF000;
        std::cout<<"lui x"<<rd<<",0x"<<std::hex << (imm >> 12)<<std::endl;

    }else if(opcode == 0b0000011) {
        //lw & lbu
        int32_t imm = sign_extend(operate>>20,12);
        if(funct3 == 0b010){
            //lw
            std::cout << "lw x" << rd << "," << imm << "(x" << rs1 << ")" << std::endl;
        }else if(funct3 == 0b100){
            //lbu
            std::cout << "lbu x" << rd << "," << imm << "(x" << rs1 << ")" << std::endl;
        }else {
            goto ERROR_OCCUR;
        }
    }else if(opcode == 0b0100011) {
        //sw & sb
        u_int32_t imm_s = (funct7<<5) | rd;
        int32_t imm = sign_extend(imm_s, 12);
        if(funct3 == 0b000){
            //sb
            std::cout << "sb x" << rs2 << "," << imm << "(x" << rs1 << ")" << std::endl;
        }else if(funct3 == 0b010){
            //sw
            std::cout << "sw x" << rs2 << "," << imm << "(x" << rs1 << ")" << std::endl;
        }else{
            goto ERROR_OCCUR;
        }
    }else{
        goto ERROR_OCCUR;
    }
    return ;
    ERROR_OCCUR:std::cout << "Unsupported operation or wrong typed (Opcode: " 
                  << std::hex << opcode << std::dec << ")" << std::endl;
    return ;
}