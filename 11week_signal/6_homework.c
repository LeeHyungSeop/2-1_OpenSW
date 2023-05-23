/*
    구조체 대입 연산에서 
    data = zeros;
    data = ones;
    는 실제로 한번에 연산되는 것이 아니라
    실제 machine code를 보면 구조체 안에 있는 변수를 각각 대입한다

    0 0인 상태에서
    1 1을 대입하려고 할 때,
    
    1 0 -> 1 1로 대입이 되는데
    1 0일 때 alarm이 오면 끊고 1 1이 들어가지 않고
    1 0이 들어가는 상황이 생기게 된다
    마찬가지로 0 1 도...

    이러한 오류를 막기 위해서 따라서
    (blocking)
    data =zeors;
    (blocking)
    data - ones;

    sigprocmask()를 통해 저 동안 signal을 받지 않도록 해야 한다

*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h> // sigprocmask()
#include <unistd.h> // alarmq

struct two_double{
    double a;
    double b;
}data;

void signal_handler(int signo){
    printf("%f, %f\n", data.a, data.b);
    alarm(1);
}

int main(void){

    struct sigaction sa;
    static struct two_double zeros = {0.0, 0.0}, ones = {1.0, 1.0};

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = signal_handler;
    if(sigaction(SIGALRM, &sa, NULL) == -1) {
        perror("sigaction");
        exit(0);
    }

    sigset_t block_set;
    
    sigemptyset(&block_set);
    sigaddset(&block_set, SIGALRM); 
        // block_set에 SIGALRM에 대한 signal을 block

    data = zeros;
    alarm(1);

    while(1){
        sigprocmask(SIG_BLOCK, &block_set, NULL); // SIGALRM block set
        data = zeros;
        sigprocmask(SIG_UNBLOCK, &block_set, NULL); // SIGALRM block unset

        sigprocmask(SIG_BLOCK, &block_set, NULL); // SIGALRM block set
        data = ones;
        sigprocmask(SIG_UNBLOCK, &block_set, NULL); // SIGALRM block unset
    }

    return 0;
}

