#include <stdio.h>

#include <sys/types.h> // open
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h> // read , close

#include <stdlib.h> // exit()
#include <errno.h> // errno변수 사용

int main(int argc, char* argv[]) {

    if(argc != 2) {
        printf("사용법 : ./prac_open_read file명\n");
        exit(0);
    }

    int fd; // file descriptor
    fd = open(argv[1], O_RDONLY); // read할 것이기 때문에 readonly로 open

    if(fd == -1) { // open 실패
        perror("file open failed...\n");
        printf("errno : %d\n", errno); // 2가 나올것임. errno.h에 의해 (vi /usr/include/asm-generic/errno-base.h)
        exit(0);
    }
    else { // open 성공
        printf("file open success.\n");
    }
    printf("Let's read the file, %s\n", argv[1]);
    printf(" -------- \n");
    
    char buf[100];
    int rd = read(fd, buf, 99);

    if(rd == -1) {
        perror("file read failed..\n");
        printf("errno : %d\n", errno);
        exit(0);
    }
    else if(rd == 0) { // EOR
        printf("this file is empty\n");
        exit(0);
    }
    else {
        printf("%s\n", buf);
    }

    close(fd);

    return 0;
}