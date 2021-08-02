#include "types.h"
#include "stat.h"
#include "user.h"

inline void defaultPriority(){
    printf(1, "Default priority: %d\n", getpriority());
    return;
}

inline void priorityDonation(){
    
    int pid = 0;
    changepriority(13);
    pid = fork();

    if (pid == 0){
        printf(1, "Child priority: %d\n", getpriority());
        exit(0);
    }
    exit(0);
}

int main(){
    defaultPriority();
    printf(1, "\n");
    priorityDonation();
    printf(1, "\n");
    return 0;
}