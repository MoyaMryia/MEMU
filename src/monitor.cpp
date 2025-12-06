#include "common.h"
#include <limits>
void startMonitor(int argc,char **argv){
    
    if(argc<2){
        std::cout<<"Usage:"<<argv[0]<<" /path/to/your/ROM.hex /path/to/your/RAM.hex(optional)"<<std::endl;
        return ;
    }else if(argc<3){
        init_rom(argv[1]);
        std::cout<<"Setting the Default RAM written to 0"<<std::endl;
    }else{
        //std::cout<<"Using given ROM & RAM"<<std::endl;
        init_rom(argv[1]);
        init_memory(argv[2]);
    }/*
    for(int i = 0;i<7000;++i){
        run_cycle();
        printStatus();
        //getchar();
    }
    getchar();*/
    char t;
    while (true) {
        std::cout << "> ";
        if (!(std::cin >> t)) break; 
        if (t == 'n') {
            std::cout<<"PC Status:"<<read_pc()<<std::endl;
            run_cycle();
            printStatus(); 
        } else if (t == 'p') {
            printStatus();
        } else if (t == 'q') {
            std::cout << "Exiting simulator." << std::endl;
            return;
        } else if (t == 'm') {
            int m_addr;
            std::cout << "Enter address (hex): ";
            if (std::cin >> std::hex >> m_addr) {
                std::cout << "MEM[0x" << std::hex << m_addr << "] = 0x" 
                          << std::hex << read_memory_word(m_addr) << std::endl;
            } else {
                std::cout << "Invalid address format." << std::endl;
                std::cin.clear(); 
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
        } else if(t == 'l'){
            int m_addr;
            std::cout << "Enter cycle loops: ";
            if (std::cin>> m_addr) {
                for(int i = 1;i<=m_addr;++i){
                    run_cycle();
                    printStatus(); 
                }
            } else {
                std::cout << "Invalid." << std::endl;
                std::cin.clear(); 
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
        }else if (t == 'b') {
        int b_addr;
        std::cout << "Enter byte address (hex): ";
        if (std::cin >> std::hex >> b_addr) {
            u_int32_t byte_data = read_memory_byte(b_addr);
            std::cout << "BYTE[0x" << std::hex << b_addr << "] = 0x" 
                      << std::hex << (byte_data & 0xFF) << std::endl;
        } else {
            std::cout << "Invalid byte address format." << std::endl;
            std::cin.clear(); 
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
    } else {
        std::cout << "Unknown command: " << t << std::endl;
    }
    }
}


void printStatus(){
    std::cout<<read_pc()<<std::endl;
    std::cout<<"PC Clock:"<<read_pc_clock()
        <<"\nGPR Status:\n";
    for(int i = 0;i<32;++i){
        std::cout<<read_gpr(i)<<' ';
    }std::cout<<std::endl;
}

void run_cycle(){
    //get command
    u_int32_t operate = fetch_instruction();
    //decode command & run
    
    //because of the jalr, the switch process will be in mainRun()
    runMain(operate, 1);
    //printStatus();
    //get next clock
    increment_pc_clock();
}
//Need some error procedure
//00000000000000010100001100000011
//