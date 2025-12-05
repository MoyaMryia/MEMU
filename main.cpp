#include "include/common.h"

int main(int argc, char **argv){
    printStatus();
    while(1){
        uint Test;
        std::cin>>std::hex>>Test;
        
        runMain(Test);
        printStatus();
    }
    
    startMonitor(argc,argv);
    startShell();
    
    return 0;
}