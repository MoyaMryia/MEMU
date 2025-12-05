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

