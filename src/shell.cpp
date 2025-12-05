#include "common.h"
#include <readline/readline.h>
#include <readline/history.h>

static char *rlGets(){
    static char *lineRead = NULL;
    if(lineRead){
        free(lineRead);
        lineRead = NULL;
    }
    lineRead = readline("(memu)");
    
}

void startShell(){

}