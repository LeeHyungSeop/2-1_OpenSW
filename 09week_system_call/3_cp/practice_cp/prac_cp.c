/*
    문제 정의

    cp 명령어와 유사한 myexp 프로그램을 작성하자
    mycp는 첫번째 인자로 지정된 파일을 두번째 인자로 지정한 파일로 복사한다
    mycp source_file dest-file
    dest-file의 모드는 rw-r--r--로 세팅하라 (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
                                            0400    0200      0040      o004      -> O0644
*/

#include <stdio.h>

#include <sys/types.h> // open
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h> // read

#include <errno.h> // errno
#include <stdlib.h> // exit

  
// 3개를 받아야 함 (main, 복사파일, 붙여넣을파일)
int main(int argc, char* argv[]) {

    if(argc != 3) {
        printf("사용법 : ./prac_cp read.txt write.txt");
        exit(0);
    }

    int read_fd = open(argv[1], O_RDONLY);
    int write_fd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0755); 
                             //  내용이 있다면 지우고 새로, 없는 파일이라면 생성
    
    if(read_fd == -1|| write_fd == -1) { // open 실패
        perror("file open failed..\n");
        exit(0);
    }
    
    char buf[100];
    int read_bytes=0;

    while(1) { // EOF도달까지 copy
        read_bytes = read(read_fd, buf, sizeof(buf));
        if(read_bytes == 0) {
            break;
        }
        write(write_fd, buf, read_bytes);
    }

    close(read_fd);
    close(write_fd);

    return 0;
}