#include "../include/memory.h"
u_int32_t gpr[32]; //register
u_int32_t memUsr[16777216]; //memory
u_int32_t romPro[16777216]; //ROM
u_int32_t PC_GPR = 0x00000000;
u_int64_t PC_CLOCK = 0x0000000000000000;
//GPR
u_int32_t read_gpr(u_int32_t address){
    return gpr[(address & 0b11111)];
}

void write_gpr(u_int32_t address, u_int32_t data){
    if((address & 0b11111) == 0){
        return ;
    }
    gpr[(address&0b11111)] = data;
    return ;
}
//MEMORY
u_int32_t read_memory_word(u_int32_t address) {
    const u_int32_t RAM_BYTE_SIZE = 16777216 * 4; 
    if (address & 0b11) {
        //Load Address Misaligned
        return 0; 
    }
    if (address >= RAM_BYTE_SIZE) {
        //Load Access Fault
        return 0; 
    }
    u_int32_t word_index = address >> 2; 
    return memUsr[word_index];
}
void write_memory_word(u_int32_t address, u_int32_t data){
    const u_int32_t RAM_BYTE_SIZE = 16777216 * 4; 
    if (address & 0b11) {
        //Store Address Misaligned
        return ; 
    }
    if (address >= RAM_BYTE_SIZE) {
        //Store Access Fault
        return ; 
    }
    u_int32_t word_index = address >> 2; 
    memUsr[word_index] = data;
    return ;
}
u_int32_t read_memory_byte(u_int32_t address){
    const u_int32_t RAM_BYTE_SIZE = 16777216 * 4; 
    if (address >= RAM_BYTE_SIZE) {
        //Load Access Fault
        return 0; 
    }
    u_int32_t word_index = address >> 2; 
    u_int32_t byte_offset = address & 0b11;
    u_int32_t shift_amount = byte_offset * 8;
    u_int32_t result = (memUsr[word_index] >> shift_amount) & 0xFF;
    return result;
}
void write_memory_byte(u_int32_t address, u_int32_t data){
    const u_int32_t RAM_BYTE_SIZE = 16777216 * 4; 
    if (address >= RAM_BYTE_SIZE) {
        //Store Access Fault
        return ; 
    }
    u_int32_t word_index = address >> 2; 
    u_int32_t byte_offset = address & 0b11;
    u_int32_t shift_amount = byte_offset * 8;
    u_int32_t write_data = (data & 0xFF)<<shift_amount;
    u_int32_t dcode = !(0xff<<shift_amount);
    memUsr[word_index] = (memUsr[word_index] & dcode) | write_data;
    return ;
}
//PC GPR
u_int32_t read_pc(){
    return PC_GPR;
}
void increment_pc(){
    PC_GPR = PC_GPR + 0x4;
    return ;
}
u_int32_t fetch_instruction(){
    return romPro[PC_GPR>>2];
}

void write_pc(u_int32_t data){
    PC_GPR = data;
    return ;
}

//PC CLOCK
void increment_pc_clock(){
    ++PC_CLOCK;
    return ;
}
u_int64_t read_pc_clock(){
    return PC_CLOCK;
}
void init_memory(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    u_int32_t word_index = 0;

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open data file " << filename << std::endl;
        return;
    }

    while (std::getline(file, line) && word_index < RAM_WORD_SIZE) {
        u_int32_t data_word;
        std::stringstream ss;
        ss << std::hex << line;
        ss >> data_word; 
        memUsr[word_index++] = data_word;
    }
    std::cout << "Successfully loaded " << word_index << " words into RAM." << std::endl;
}

void init_rom(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    u_int32_t word_index = 0;

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open data file " << filename << std::endl;
        return;
    }

    while (std::getline(file, line) && word_index < RAM_WORD_SIZE) {
        u_int32_t data_word;
        std::stringstream ss;
        ss << std::hex << line;
        ss >> data_word; 
        romPro[word_index++] = data_word;
    }
    std::cout << "Successfully loaded " << word_index << " words into ROM." << std::endl;
}