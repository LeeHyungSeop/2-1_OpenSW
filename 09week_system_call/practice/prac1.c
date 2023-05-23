#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void fork_test2() {
    printf("L0\n");
    if(fork() == 0) {
        execl("/bin/echo", "echo", "L1", NULL);
        printf("L2\n");
    }
    printf("L3\n");
}

int main(void){

    int status;

    fork_test2();
    wait(&status);
    printf("L4\n");

    return 0;
}