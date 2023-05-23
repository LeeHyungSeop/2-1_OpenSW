#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void){

    // unsigned int
    pid_t get_p, get_pp;

    get_p = getpid();
    get_pp = getppid(); 

    printf("pid : %d\n", get_p);

    printf("ppid : %d\n", get_pp);

}