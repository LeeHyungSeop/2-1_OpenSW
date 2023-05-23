#include <stdio.h>
#include <stdlib.h> // exit()
#include <pthread.h> // pthread_create(), pthread_exit()
#include <unistd.h>

#define NUM_THREAD 100

/*
    thread 100개를 생성하라
*/

void *myfunc(void *arg) {
    printf("Hello world\n");
    pthread_exit(NULL);
}

int main(void){

    pthread_t mythread[NUM_THREAD];
    for (int i = 0; i < NUM_THREAD; i++)
    {
        pthread_create(&mythread[i], NULL, myfunc, NULL);
    }

    printf("I am the main thread\n");
    
    for (int i = 0; i < NUM_THREAD; i++)
    {
        pthread_join(mythread[i], NULL);
    }
    

    return 0;
}