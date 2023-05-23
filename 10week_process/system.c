/*
    system이라는 system call이 있다.

        system("ls -l | wc -l"); 
            --> "" 안의 명령어들을 그대로 실행시켜주는 system call

*/

#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int status;
    status = system("ls -l | aa"); 
    printf("exit code %d\n", WEXITSTATUS(status));

    return 0;
}