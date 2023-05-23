#include <stdio.h>  
#include <sys/types.h>
#include <unistd.h>

/*
    무한루프 안에서 프로세스 아이디 출력

*/

int main(void) {

    while (1) {
        printf("pid : %d\n", getpid());
        sleep(1);
    }
    

    return 0;
}
