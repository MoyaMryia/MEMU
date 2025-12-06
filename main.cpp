#include "include/common.h"

int main(int argc, char **argv){
    //freopen("out.txt","w",stdout);
    printStatus();
    /*while(1){
        uint Test;
        std::cin>>std::hex>>Test;
        
        runMain(Test,1);
        printStatus();
    }*/
    
    startMonitor(argc,argv);
    startShell();
    //fclose(stdout);
    return 0;
}
//0000 000 0 0100 0010 0 010 0000 0 010 0011