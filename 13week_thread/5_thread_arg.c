#include <stdio.h>
#include <stdlib.h> // exit()
#include <pthread.h> // pthread_create(), pthread_exit()
#include <unistd.h>

#define NUM_THREAD 1

/*
    구조체에 시작값과 마지막값을 넣어서 쓰레드에 전달하라
    쓰레드는 worker()함수를 수행,
    구조체에 전달받은 시작값부터 마지막 값까지 더해서 sum에 대입한다

    쓰레드가 종료하면, 메인 쓰레드는
    쓰레드가 계산한 sum 값을 출력한다.
*/

struct thread_data {
    long long start;
    long long end;
    long long sum;
};

void *workder(void* arg) {
    struct thread_data* p =  (struct thread_data*)arg;
    for (long long i = p->start; i<=p->end; i++)
    {
        p->sum += i;
    }

    pthread_exit(p);
}

int main(void){

    pthread_t mythread;
    struct thread_data my_data;
    my_data.start = 0;
    my_data.sum = 0;
    my_data.end = 100;

    pthread_create(&mythread, NULL, workder, (void*)&my_data);

    pthread_join(mythread, (void**)&my_data);
    printf("sum : %lld\n", my_data.sum);

    return 0;
}