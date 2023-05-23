#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <signal.h> // sigaction()


/*
    sigaction()을 사용하여 
    SIGINT signal을 받으면 "ouch" 출력
*/

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

void my_int_handler(int sig) {
    printf("I got a signal %d\n", sig);
}

int main(void) {

    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = my_int_handler;
        // &my_int_handler 가 아님을 유의하자

    if(sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(0);
    }
    for(;;) {
        printf("pid : %d\n", getpid());
        sleep(1);
    }

    return 0;
}