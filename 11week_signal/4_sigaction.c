#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <signal.h> // sigaction(), exit()


/*
    sigaction()을 사용하여 
    SIGINT signal을 받으면 "ouch" 출력
*/

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

void my_int_handler(int sig) {
    printf("I got a signal %d\n", sig);
}
void my_quit_handler(int sig) {
    printf("I got a signal %d\n", sig);
    printf("Good bye ~\n");
    exit(0);
}

int main(void) {

    struct sigaction sa_int, sa_quit;

    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sa_int.sa_handler = my_int_handler;

    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sa_quit.sa_handler = my_quit_handler;
    
    // sigaction(SIGINT, &sa_int, NULL);
    if(sigaction(SIGINT, &sa_int, NULL) == -1) {
        perror("sigaction");
        exit(0);
    }
    if(sigaction(SIGQUIT, &sa_quit, NULL) == -1) {
        perror("sigaction");
        exit(0);
    }
    for(;;) {
        printf("pid : %d\n", getpid());
        sleep(1);
    }

    return 0;
}