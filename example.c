#include "types.h"
// #include "defs.h"
// #include "param.h"
// #include "memlayout.h"
// #include "mmu.h"
// #include "x86.h"
// #include "proc.h"
// #include "spinlock.h"
#include "user.h"
#include "stat.h"
// #include "string.h"

// int main(){
//     printf(1, "hello");
//     // cprintf("%d", 1);
//     exit(0);
//     // return 0;
// }

int main() {
    int count = 0;
    int pid=0,pid2=0;
    if ( (pid = fork()) ) {
        count=count + 2;
        printf(0, "%d", count);
    }
    if(count == 0){
        count++;
        pid2=fork();
        printf(0, "%d", count);
    }
    else { pid2 = fork();}
    if(pid2 || pid) {
        waitpid(pid2, 0, 0);
        count = count+4;
    }
    printf(0, "%d", count);
    exit(0);
}