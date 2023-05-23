#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <signal.h> // sigaction(), exit()


/*
    alarm(2)함수를 통해 매 1초마다 SIGALRM을 발생시켜라
    sigaction(2)함수를 써서 SIGARLM을 받으면 "Alarm arrived!"출력

    alarm(2)는 한 번만 SIGALRM을 발생시킨다.
    주기적으로 SIGALRM을 발생시키기 위해서는 SIGARLM시그널 핸들러에도
    alarm(2)을 설정해 주어야 한다.
*/

unsigned int alarm(unsigned int seconds); 
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

void my_int_handler(int sig) {
    printf("I got a signal %d\n", sig);
}
void my_quit_handler(int sig) {
    printf("I got a signal %d\n", sig);
    printf("Good bye ~\n");
    exit(0);
}
void my_alrm_handler(int sig) {
    printf("Alarm arrived!\n");

    alarm(2);
}

int main(void) {

    struct sigaction sa_int, sa_quit, sa_alrm;

    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sa_int.sa_handler = my_int_handler;

    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sa_quit.sa_handler = my_quit_handler;

    sigemptyset(&sa_alrm.sa_mask);
    sa_alrm.sa_flags = 0;
    sa_alrm.sa_handler = my_alrm_handler;
    

    if(sigaction(SIGINT, &sa_int, NULL) == -1) {
        perror("sigaction");
        exit(0);
    }
    if(sigaction(SIGQUIT, &sa_quit, NULL) == -1) {
        perror("sigaction");
        exit(0);
    }
    if(sigaction(SIGALRM, &sa_alrm, NULL) == -1) {
        perror("sigaction");
        exit(0);
    }

    alarm(5); // 5초 뒤 알람 도착

    for(;;) {
        printf("pid : %d\n", getpid());
        sleep(1);
    }

    return 0;
}