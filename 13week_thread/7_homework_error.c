#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h> 
#include <unistd.h> 

#define NUM_THREADS 4   // 1 , 2 , 4
#define NUM 1000000000

volatile long long sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

void *sumZeroToNum(void *arg) {

    int* _index = (int*)arg; // main에 있는 index에 대한 포인터
    int index = *(_index);   // main에 있는 index값을 받아옴
    (*_index) += 1;          // main에 있는 실제 index의 값을 +1 증가 (다음 쓰레드의 합구간 일반화식에 대입하기 위하여)

    long long part_start = ((NUM / NUM_THREADS) * index) + 1; // 여기서 부터
    long long part_end = (NUM / NUM_THREADS) * (index+1);     // 여기까지 더한다
    long long part_sum = 0;                                   // local variable로써 부분합을 저장.
    printf("%lld %lld\n", part_start, part_end);
    
    for (long long i = part_start; i <= part_end; i++) {
        pthread_mutex_lock(&mutex);   // overhead가 큰 lock은 많이 부르면 오히려 멀티 쓰레드 성능이 떨어진다.
        part_sum += i;
        pthread_mutex_unlock(&mutex); // 따라서 최대한 적게 부르도록 하였다.
    }

    sum += part_sum; // critical section이기 때문에 lock, unlock으로 쓰레드간 동기화

    pthread_exit((void*)index);
}

int main(void){

    int result = 0;
    int index = 0;
    int retval = 0;

    pthread_t mythread[NUM_THREADS];
    printf("%d개의 쓰레드를 통한 병렬처리\n", NUM_THREADS);
    for (int i = 0; i < NUM_THREADS; i++)
    {
        result = pthread_create(&mythread[i], NULL, sumZeroToNum, &index); 
            // i를 넘기면 maini의 i값이 ++되기 때문에 쓰레드 별 합구간을 연산할 때 오류가 발생.
            // 따라서 main에서 값이 변하지 않도록 index변수를 따로 선언하여 
            // sumZeroToNum()함수에서만 index값을 증가시킨다.
        if(result) {
            exit(0);
        }
    }
    for(int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(mythread[i], (void**)&retval);
        printf("mythread[%d] exit..\n", retval);
    }

    printf("Final value : %lld\n", sum);

    return 0;
}