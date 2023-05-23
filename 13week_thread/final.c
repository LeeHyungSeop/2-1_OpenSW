#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 1
#define NUM_DATA 100

struct thread_args {
    long long num_start;
    long long num_end;
};

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;
int my_data[NUM_DATA] = {0};
volatile long long sum = 0;

void* calc_array_sum(void* arg) {

    struct thread_args* ptr = (struct thread_args*) arg;
    long long part_sum = 0;

    printf("%lld ~ %lld\n", ptr->num_start, ptr->num_end);

    for (long long i = ptr->num_start; i <= ptr->num_end; i++)
    {
        part_sum += my_data[i];
    }
    pthread_mutex_lock(&my_mutex);
    sum += part_sum;
    pthread_mutex_unlock(&my_mutex);
    
    pthread_exit(NULL);
}

int main(void){

    struct thread_args TA[NUM_THREADS];
    pthread_t my_thread[NUM_THREADS];

    for (int i = 0; i < NUM_DATA; i++)
    {
        my_data[i] = i;
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        TA[i].num_start = ((NUM_DATA / NUM_THREADS) * i);
        TA[i].num_end = (NUM_DATA / NUM_THREADS) * (i+1) -1; 
    }
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&my_thread[i], NULL, calc_array_sum, (void*)&TA[i]);
    }
    
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(my_thread[i], NULL);
    }
    
    printf("Total sum : %lld\n", sum);

    return 0;
}