#include <stdio.h>
#include <sys/types.h> // open()
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // read()
#include <errno.h> // errno
#include <stdlib.h> // exit()

#define BUF_SIZE 20

int main(int argc, char* argv[]) {

    if(argc != 2) {
        printf("사용법 :cat some_file.txt | ./mytee paste.txt");
        printf("errno : %d\n", errno);
        exit(0);
    }
        /*
            실행할 때 인자로 2개를 받아야 하는데,
            2개가 아니면 사용법을 출력해주고 프로그램 종료.
        */

    int paste_fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0666); 
        /*
            paste_fd는 some-file.txt에서 tee명령어로 
            stdin이 저장될 file descriptor.

            paste_fd에 해당하는 file을 open할 것이다.
            쓰기전용, 내용이 있다면 지운다, 없는 파일이라면 생성한다.
            파일을 생성할때는 8진수 0666에 해당하는 모드로 생성한다.
        */

    if(paste_fd == -1) { 
        perror("file open failed..\n");
        exit(0);
    }
        /*
            paste_fd에 해당하는 파일 open에 실패한 경우,
            error message를 출력하고 프로그램 종료.
        */
    
    char buf[BUF_SIZE]; // read, write를 위한 buffer 변수
    int read_bytes=0; // read()의 return값을 저장할 변수, 몇 bytes read했는지, EOF인지 확인

    while(1) { // EOF도달까지 copy
        read_bytes = read(0, buf, BUF_SIZE);
        if(read_bytes == 0) {
            break;
        }
        write(1, buf, read_bytes); 
        write(paste_fd, buf, read_bytes); 
    }
        /*  while(1)

            Standard file descriptor를 참고하여
            
            0 - stdin --> read(0, .. ,..) -> stdin을 read
            1 - stdout --> write(1, .. ,..) -> stdout에 write
            paste_fd --> write(paste_fd, .., ..) -> paste_fd file에 write
        */

    close(paste_fd);
        /*
            위에서 open했던 paste_fd에 해당하는 file을
            close한다.
        */

    return 0;
}