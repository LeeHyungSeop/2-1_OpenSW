#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h> // wait()
#include <stdlib.h> // exit()

int main(void) {

    pid_t pid;

    pid = fork();

    if (pid == 0) {
        printf("child pid  : %d, ppid : %d\n", getpid(), getppid());
        for (int i = 0; i < 10; i++) {
            printf("%d ",i);
        }
        printf("\n");
        exit(101); 
    } 

    else {
        printf("parent pid : %d, ppid : %d\n", getpid(), getppid());
        int exitstatus;
        for (int i = 10; i < 20; i++) {
            printf("%d ",i);
        }
        printf("\n");
        wait(&exitstatus);
        printf("child procecss의 exit code : %d\n", WEXITSTATUS(exitstatus));
    }

    return 0;
}