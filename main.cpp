#include "include/common.h"

int main(int argc, char **argv){
    while(1){
        uint Test;
        std::cin>>std::hex>>Test;
        runMain(Test);
    }
    
    startMonitor(argc,argv);
    startShell();
    
    return 0;
}