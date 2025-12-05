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

    if(lineRead && *lineRead){
        add_history(lineRead);
    }
    return lineRead;
}

void startShell(){

}