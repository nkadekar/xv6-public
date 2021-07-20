#include "types.h"
#include "stat.h"
#include "user.h"

#define NULL (void*)0

inline void exit_test() {
    printf(1, "Testing exit: 'Child' should exit status 100.\n");

    int pid = 0;
    int status;
    pid = fork();

    wait(&status);

    if (pid == 0){ //child
        exit(100);
    }

    printf(1, "Child exited with status: ");
    printf(1, "%d\n", status);
    return;
}

inline void wait_test(){
    printf(1, "Testing wait: 'Child' should print before 'Parent'. Status should be 100.\n");

    int pid = 0;
    int status;
    pid = fork();

    wait(&status);

    if (pid == 0){ //child
        printf(1, "Child ");
        exit(100);
    }
    else {
        printf(1, "Parent \nStatus:");
        printf(1, "%d\n", status);
    }
    return;
}

inline void waitpid_test_nochild() {
    printf(1, "Testing waitpid with no child: should print return pid of -1\n");
    int child_status;
    int wpid = waitpid(4, &child_status, 0);

    if (wpid == -1) {
        printf(1, "Success: wpid = -1\n");
    }
    else {
        printf(1, "Error: pid was %d, expected -1\n", wpid);
        return;
    }
    return;
}
inline void waitpid_test_withchild() {
    int pid;
    int child_status;

    printf(1, "Testing waitpid with child: child should terminate with exit status 100\n");

    if ((pid = fork()) == 0) 
    exit(100);
    int wpid = waitpid(pid, &child_status, 0);
    if (child_status == 100 && wpid == pid)
        printf(1, "Success: Child %d terminated with exit status %d\n",
            wpid, child_status);
    else
        printf(1, "Error: Child %d terminated with exit status %d, Expected child pid is %d, expected exit status = 100", wpid, child_status, pid);
    return;
}

inline void waitpid_test_withnull() {
    int pid;
    int *child_status = NULL;
    
    if ((pid = fork()) == 0) 
    exit(100);
    
    printf(1, "Testing waitpid null status: should return null status\n");

    waitpid(pid, child_status, 0);

    if (!child_status)
        printf(1, "Success: waitpid status returned null status");
    else
        printf(1, "Error: waitpid returned something else");
    return;
}

int main() {
    exit_test();
    printf(1, "\n");
    wait_test();
    printf(1, "\n");
    waitpid_test_nochild();
    printf(1, "\n");
    waitpid_test_withchild();
    printf(1, "\n");
    waitpid_test_withnull();
    printf(1, "\n");

    exit(0);
}