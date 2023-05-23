#include <stdio.h>  
#include <sys/types.h>
#include <unistd.h>

void goo() {
    printf("this is goo\n");
}

void foo() {
    printf("this is foo\n");
    goo();
}

int main(void) {

    while (1) {
        foo();
        printf("pid : %d\n", getpid());
        sleep(1);
    }
    

    return 0;
}
