#include <stdio.h>
#include <sys/types.h> // open()
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h> // exit()
#include <unistd.h> // read()

#define BUF_SZ 64

// cp 명령어와 유사한 myexp 프로그램을 작성하자
// mycp는 첫번째 인자로 지정된 파일을 두번째 인자로 지정한 파일로 복사한다
// mycp source_file dest-file
// dest-file의 모드는 rw-rw-rw-로 세팅하라 (0644 , S_IRUSR | S_IRGRP | S_IROTH)

int main(int argc, char* argv[]) {

    if(argc != 3) { 
        printf("usage : mycp source-file destination-file\n");
        exit(0); // not system call, library임-> program 종료, #include <stdlib.h>
    }

    printf("--------------------\n");
    printf("first parmaeter : %s\n", argv[0]); // 명령어 
    printf("second parmaeter : %s\n", argv[1]); // 첫번째 param
    printf("third parmaeter : %s\n", argv[2]); // 두번째 param

    int fd_read, fd_write;
    fd_read = open(argv[1], O_RDONLY);
    fd_write = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                             // 존재하지 않으면 생성, 있으면 새로 write
  


    if(fd_read == -1 || fd_write == -1) {
        perror("first open : ");
        exit(0);
    }
    else {
        printf("open success!\n");
        printf("Let's read & write!!\n\n");
    }

    char* buf = (char*)malloc(sizeof(char)*BUF_SZ);

    while(1){
        int nb = read(fd_read, buf, BUF_SZ);
        if(nb == 0) { // EOF
            break;
        }
        write(fd_write, buf, nb); // 읽어온 개수만큼만 write하면 된다
    }
    free(buf);
    
    close(fd_read);
    close(fd_write);

}