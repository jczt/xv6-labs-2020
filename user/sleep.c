#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(2, "error argc nums\n");
        exit(1);
    }
    int i;
    i = atoi(argv[1]);
    sleep(i);
    exit(0);
}
