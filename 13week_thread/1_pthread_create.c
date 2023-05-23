#include <stdio.h>
#include <stdlib.h> // exit()
#include <pthread.h> // pthread_create(), pthread_exit()

/*
    myfunc()함수를 수행하는 쓰레드를 생성하라
*/

void *myfunc(void *arg) {
    printf("Hello world\n");
    pthread_exit(NULL);
}

int main(void){

    pthread_t mythread;

    int result = pthread_create(&mythread, NULL, myfunc, NULL);
    if(result) { // thread 생성이 성공하면 0, 아니면
        exit(1);
    }

    printf("I am the main thread\n");
    
    pthread_exit(NULL); // main thread만 종료되고 남은 thread는 계속 진행.
                        // 이거 안하면 return 0;으로 프로세스가 종료되어 모든 쓰레드가 종료돼버려서
                        // hello world 출력이 안된다.

    return 0;
}q