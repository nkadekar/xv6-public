#include "types.h"
#include "stat.h"
#include "user.h"


#define N 5

int main() {

    int pid[N];
    int i;
    int child_status;

    for (i = 0; i < N; i++) 
        if ((pid[i] = fork()) == 0) 
	    exit(100+i); /* Child */
    for (i = 0; i < N; i++) {
        int wpid = waitpid(pid[i], &child_status, 0);
            if (child_status >= 0)
                printf(1, "Child %d terminated with exit status %d\n",
                    wpid, child_status);
            else
                printf(1, "Child %d terminate abnormally\n", wpid);
    }

    exit(0);
}