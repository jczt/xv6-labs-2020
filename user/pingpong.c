#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc > 1){
        fprintf(2, "wrong arg num\n");
        exit(1);
    }
    //父到子
    int p1[2];
    //子到父
    int p2[2];

    if(pipe(p1) == -1 || pipe(p2) == -1){
        fprintf(2, "fail to create pipe\n");
        exit(1);
    }
    
    int pd;
    if((pd = fork()) < 0){
        fprintf(2, "fail to fork\n");
        exit(1);
    }else if(pd == 0){
        //子进程
        close(p1[1]);
        close(p2[0]);

        char buf[5];
        read(p1[0], buf, 4);
        close(p1[0]);
        printf("%d: received %s\n", getpid(), buf);

        write(p2[1], "pong", strlen("pong"));
        close(p2[1]);
    }else{
        //父进程
        close(p1[0]);
        close(p2[1]);

        write(p1[1], "ping", strlen("ping"));
        close(p1[1]);

        char buf[5];
        read(p2[0], buf, 4);
        close(p2[0]);
        printf("%d: received %s\n", getpid(), buf);
    }
    exit(0);
}