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
            fflush(NULL); 
            // printf()를 하면 memory buffer에 저장되었다가. 
            // 어느정도 모이면 한꺼번에 출력된다. 곧바로 출력되게 하도록. fflush()
        }
        printf("\n");
        exit(101); // 종료하면서 parent한테 101이라는 status code를 넘긴다
    } 
    else {
        printf("parent pid : %d, ppid : %d\n", getpid(), getppid());
        int exitstatus;
        for (int i = 10; i < 20; i++) {
            printf("%d ",i);
            fflush(NULL); 
        }
        printf("\n");
        wait(&exitstatus);
        printf("child procecss의 exit code : %d\n", WEXITSTATUS(exitstatus));
    }

    return 0;
}