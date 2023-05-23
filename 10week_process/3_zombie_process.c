/*
    child process가 종료되면, parent process가 정리를 해줘야 함
    메모리 해제, process table에서 지우는..

    하지만 parent process가 처리를 안해주고 다른 일을 하고 있으면
    child process는 종료되었지만 process table에서 지워지지 않은 상태.
    <defunct>
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h> // wait()

int main(void) {

    pid_t pid;

    pid = fork();

    if (pid == 0) {
        printf("child pid  : %d, ppid : %d\n", getpid(), getppid());
    } 
    else {
        int exitstatus;
        while(1) {}   // wait()에 도달하지 못하도록 막는다.
        wait(&exitstatus);
        printf("parent pid : %d, ppid : %d\n", getpid(), getppid());
    }

    return 0;
}