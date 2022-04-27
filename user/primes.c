# include "kernel/types.h"
# include "user.h"

# define RD 0
# define WR 1

void prime(int p[]){
    close(p[WR]);
    int p1[2];
    pipe(p1);
    
    int pm;
    if((read(p[RD], &pm, sizeof(pm))) == sizeof(pm)){
        printf("prime %d\n", pm);
    }
    
    int tp;
    while((read(p[RD], &tp, sizeof(tp))) == sizeof(tp)){
        if(tp % pm != 0){
            write(p1[WR], &tp, sizeof(tp));
        }
    }
    close(p[RD]);
    close(p1[WR]);

    if(fork() == 0){
        prime(p1);
    }else{
        close(p1[RD]);
        wait(0);
    }
    
    exit(0);
}

int main(int argc, char *argv[]){
    int p[2];
    pipe(p);
    
    for(int i = 2; i <= 35; i++){
        write(p[WR], &i, sizeof(i));
    }
    
    if(fork() == 0){
        prime(p);
    }else{
        close(p[WR]);
        close(p[RD]);
        wait(0);
    }

    exit(0);
}