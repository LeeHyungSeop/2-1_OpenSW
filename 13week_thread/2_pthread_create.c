#include <stdio.h>
#include <stdlib.h> // exit()
#include <pthread.h> // pthread_create(), pthread_exit()
#include <unistd.h>

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
    
    // sleep(1); 
        /*
            새로 생성한 쓰레드가 실행되기에 충분한 시간인 것 같지만
            생성된 쓰레드가 실행되는 시간은 프로그램에 따라 달라지기 떄문에
            이런 식으로 시간을 기다려주는 코드는 안좋다
        */
    pthread_join(mythread, NULL);
        /*
            main thread에서 mythread가 끝나기를 기다린다
        */

    return 0;
}