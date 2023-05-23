/*
    현재 프로세스로 fork해서
    다른 프로세스를 실행하도록

    execve() 사용하여 ls -l 명령어를 실행하라
*/
#include <stdio.h>
#include <unistd.h> // execve()

int main() {

    char* new_argv[] = {"ls", "-l", NULL}; // 명령인자 ls, -l이 끝(NULL)

    execve("/usr/bin/ls", new_argv, NULL); // envp[]는 설정 안함 

    printf("Hello world\n"); // execve로 프로세스가 새로운 것으로 바뀌어서
                             // execve 밑에 있는 모든 코드들은 실행이 안된다.
                             // execve를 만난 순간 새로운 프로세스로 바뀌어 버려서 밑의 내용들은 싹 없어진다
                             // 따라서 "Hello world"는 출력이 안된다

    return 0;
}