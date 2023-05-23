/*
    자식 프로세스를 fork를 통해 생성.
    자식 프로세스가 execv()를 통해  ls -l 명령어를 실행하라
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include <stdlib.h>  // exit()

int main(void) {

    pid_t pid;

    pid = fork();

    if (pid == 0) {
        printf("child pid  : %d, ppid : %d\n", getpid(), getppid());
        char* new_argv[] = {"ls", "-l", NULL}; // 명령인자 ls, -l이 끝(NULL)   
        execve("/usr/bin/ls", new_argv, NULL);  // envp[]는 설정 안함 
                                                // exit()는 ls process에서 보낸다
        exit(101); // 이 exit(101)도 의미가 없어진다
        printf("[Child Process] Hello World!\n"); // 이거는 실행 안된다.

    } 
    else {
        int exitstatus;
        wait(&exitstatus);
        printf("[Parent Process] Hello World!\n");
        printf("child procecss의 exit code : %d\n", WEXITSTATUS(exitstatus)); // 101이 오지 못한다. execve() 때문에
    }

    return 0;
}