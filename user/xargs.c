#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

#define MAXSIZE 512

int main(int argc, char* argv[]){
    
    char buf[MAXSIZE];
    
    char* xargv[MAXARG];
    int xargc = 0;
    for(int i = 1; i < argc; i++){
        xargv[xargc++] = argv[i];
    }
    
    int p = 0;
    while(read(0, &buf[p], sizeof(char)) == sizeof(char)){
        if(buf[p] == '\n'){
            int pid = fork();
            if(pid > 0){
                p = 0;
                wait(0);
            }else{
                buf[p] = 0;
                xargv[xargc++] = buf;
                exec(xargv[0], xargv);
                exit(1);
            }
        }else{
            p++;
        }
    }
    wait(0);
    exit(0);
}