#include "common.h"

void startMonitor(int argc,char **argv){
    if(argc<2){
        std::cout<<"Usage:"<<argv[0]<<" /path/to/your/ROM.hex /path/to/your/RAM.hex(optional)"<<std::endl;
        return ;
    }else if(argc<3){
        std::cout<<"Setting the Default RAM written to 0"<<std::endl;
    }else{
        std::cout<<"Using given ROM & RAM"<<std::endl;
    }
}

void printStatus(){
    std::cout<<"PC Clock:"<<read_pc_clock()
        <<"\nPC Status:"<<get_pc()
        <<"\nGPR Status:\n";
    for(int i = 0;i<32;++i){
        std::cout<<read_gpr(i)<<' ';
    }std::cout<<std::endl;
}

void run_cycle(){
    //get command
    u_int32_t operate = fetch_instruction();
    //decode command & run
    printStatus();
    //because of the jalr, the switch process will be in mainRun()
    runMain(operate);
    //get next clock
    increment_pc_clock();
}
//Need some error procedure