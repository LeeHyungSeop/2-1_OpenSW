#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_THREADS 2

volatile int cnt = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 정적 초기화

void *worker(void *ptr) {
    int i;
    for ( i = 0; i < 50000; i++)
    {
        pthread_mutex_lock(&mutex); // lock
        cnt++;
        pthread_mutex_unlock(&mutex); // unlock
    }
    pthread_exit(NULL);
}

int main(void){

    pthread_t threads[NUM_THREADS];
    int i, result;

    for ( i = 0; i < NUM_THREADS; i++)
    {
        result = pthread_create(&threads[i], NULL, worker, NULL);
        assert(result == 0);
    }
    for ( i = 0; i < NUM_THREADS; i++)
    {
        result = pthread_join(threads[i], NULL);
        assert(result == 0);
    }

    printf("Final value : %d\n", cnt);

    return 0;
}