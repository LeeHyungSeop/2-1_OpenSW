#include <stdio.h>
#include <stdlib.h> // exit()
#include <pthread.h> // pthread_create(), pthread_exit()
#include <unistd.h>

#define NUM_THREAD 1

/*
    long long 타입의 전역변수 counter(0) --> %lld
    char타입의 전역변수 is_running(1)

    is_running == 1인 동안 루프를 돌면서 counter 값 증가
    is_running == 0인 경우 루프 종료하고 쓰레드 종료

    main thread는 
    루프를 돌면서 counter값을 출력하라.
    sleep(1)을 사용하여 1초마다 한번씩 루프가 돌도록 하라.
    10회 루프를 돌고나면 is_running = 0으로 세팅하라
*/

// static long long counter = 0;
// static char is_running = 1;

// 최적화 컴파일을 했을 때, 값을 서로 공유할 수 없기 때문에 (L1 cache)
// volatile을 선언하여서 memory에 대해 optimize하지 말라고 선언.
volatile static long long counter = 0;
volatile static char is_running = 1;

void *myfunc(void *arg) {
    while (is_running == 1){
        counter += 1;
    }
    pthread_exit(NULL);
}

int main(void){

    pthread_t mythread[NUM_THREAD];

    for (int i = 0; i < NUM_THREAD; i++) {
        pthread_create(&mythread[i], NULL, myfunc, NULL);
    }
    
    for (int i = 0; i < 10; i++)
    {
        printf("counter : %lld\n", counter);
        sleep(1);
    }
    is_running = 0;

    pthread_join(mythread[0], NULL);

    return 0;
}