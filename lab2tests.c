#include "types.h"
#include "stat.h"
#include "user.h"

inline void defaultPriority(){
    printf(1, "TESTING DEFAULT PRIORITY:\n");
    printf(1, "Default priority: %d\n", getpriority());
    if (getpriority() == 15) {
        printf(1, "Success!");
    }
    return;
}

inline void priorityDonation(){
    printf(1, "TESTING PRIORITY DONATION:\n");
    
    int pid = 0;
    int cprio = 0;
    changepriority(31);
    pid = fork();

    if (pid == 0){
        cprio = getpriority();
        printf(1, "Child priority: %d\n", cprio);
        if (cprio == 31) {
        printf(1, "Success!");
    }
        exit(0);
    }
    wait(0);

    return;
}

inline void prioritySchedulingTest(){
    printf(1, "TESTING SCHEDULING WITH 4 PROCESSES:\n");
    changepriority(10);
    int pid1, pid2 = 1;
    pid1 = fork();
    pid2 = fork();
    if (pid1 == 0 && pid2 == 0){ //child of child CC
        changepriority(31);
        yield();
        printf(1, "Priority of %d arrived last\n", getpriority());
        //print 4th
        exit(0);
    }
    else if (pid1 == 0 && pid2 != 0){ //CP
        changepriority(30);
        yield();
        printf(1, "Priority of %d arrived third\n", getpriority());
        //print 3rd
        exit(0);
    }
    else if (pid2 == 0 && pid1 != 0){ //PC
        changepriority(29);
        yield();
        printf(1, "Priority of %d arrived second\n", getpriority());
        //print 2nd
        exit(0);
    }
    else if (pid1 != 0 && pid2 != 0){ //PP
        changepriority(28);
        yield();
        //print 1st
        printf(1, "Priority of %d arrived first\n", getpriority());
        exit(0);
    }
}

int main(){
    defaultPriority();
    printf(1, "\n");
    priorityDonation();
    printf(1, "\n");
    prioritySchedulingTest();
    printf(1, "\n");
    exit(0);
}