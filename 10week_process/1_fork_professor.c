#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {

    pid_t pid;

    pid = fork();

    if (pid == 0) {
        printf("child pid  : %d, ppid : %d\n", getpid(), getppid());
    } else {
        printf("parent pid : %d, ppid : %d\n", getpid(), getppid());
    }

    return 0;
}