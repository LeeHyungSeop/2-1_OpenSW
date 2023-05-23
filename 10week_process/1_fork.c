/*
    fork()의 리턴값을 확인하여 자식과 부모 프로세스를 구분하도록 
    자신의 pid와 ppid를 출력하자
*/

#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>

int main(void){

    pid_t pid = fork();

    if(pid == 0) { // 자식 프로세스가 걸림
        pid_t pid_c = getpid();
        pid_t ppid_c = getppid();
        printf("자식 프로세스의 pid  : %d / ppid : %d\n", pid_c, ppid_c);
    }
    else { // 부모 프로세스가 걸림
        pid_t pid_p = getpid();
        pid_t ppid_p = getppid();
        printf("부모 프로세스의 pid  : %d / ppid : %d\n", pid_p, ppid_p);
    }

    return 0;
}