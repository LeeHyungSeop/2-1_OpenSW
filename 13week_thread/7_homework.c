/*
    0부터 1,000,000,000까지 합을 구하는 프로그램을 멀티쓰레딩으로 작성하라.

    NUM_THREADS(해당 개수)만큼 영역을 나누어서 각 쓰레드가 영역의 값들을 합산하고, 
    최종적으로 쓰레드가 계산한 값을 합산하여 최종합을 구하도록 하라

    NUM_THREAD2S 를 1, 2, 4로 변형시켜서 컴파일한 후 실행시간 성능을 측정해보라.

    time(1)명령어로 프로그램 수행시간 측정 ex) time ./a.out
*/

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h> 
#include <unistd.h> 

#define NUM_THREADS 4  // 1 , 2 , 4
#define NUM 1000000000

struct thread_data {
    long long start;
    long long end;
};

volatile long long sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

void *sumZeroToNum(void *arg) {

    struct thread_data* part = (struct thread_data*)arg;
    

    long long part_sum = 0;
    for (long long i = part->start; i <= part->end; i++) {
        part_sum += i;
    }
    printf("sum range : %lld ~ %lld\n", part->start, part->end);
    printf("part sum is %lld\n\n", part_sum);

    pthread_mutex_lock(&mutex);   // overhead가 큰 lock은 많이 부르면 오히려 멀티 쓰레드 성능이 떨어진다.
    sum +=  part_sum;             // critical section이기 때문에 lock, unlock으로 쓰레드간 동기화
    pthread_mutex_unlock(&mutex); // 따라서 최대한 적게 부르도록 하였다. 
        /*
            for문 안에서 1,000,000,000번 lock을 부르는 것은
            멀티 쓰레드 프로그래밍 효과가 없어지고 성능이 매우 떨어지게 되어
            오히려 단일 쓰레딩보다 속도가 느리게 나온 것을 경험했습니다.

            따라서 for문에서는 local변수로 part_sum을 선언하여 해당 쓰레드별 구간만큼만 더하고
            그것을 전역변수 sum에 합산할 때에(critical section) lock을 사용함으로써 
            오버헤드와 딜레이를 최소화하여 안정화된 멀티 쓰레드 프로그래밍을 이용하였습니다.
        */
    pthread_exit((void*)NULL);
}

int main(void){

    int result = 0;
    long long retval = 0;

    struct thread_data my_data[NUM_THREADS]; // start, end 정보를 담은 구조체. NUM_THREADS개수 만큼 선언
    pthread_t mythread[NUM_THREADS]; //  NUM_THREADS만큼 쓰레드 변수 선언

    printf("[%d개의 쓰레드를 통한 병렬처리]\n", NUM_THREADS);
    for (int i = 0; i < NUM_THREADS; i++)
    {
        my_data[i].start =  ((NUM / NUM_THREADS) * i) + 1; // 여기서부터
        my_data[i].end = (NUM / NUM_THREADS) * (i+1);      // 여기까지 더한다 (일반화식)
        result = pthread_create(&mythread[i], NULL, sumZeroToNum, &my_data[i]); // thread 생성
        if(result) {
            exit(0);
        }
    }
    
    for(int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(mythread[i], NULL); 
    }

    printf("Final value : %lld\n", sum);

    return 0;
}