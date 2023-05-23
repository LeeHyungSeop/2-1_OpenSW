/*
    system이라는 system call이 있다.

        system("ls -l | wc -l"); 
            --> "" 안의 명령어들을 그대로 실행시켜주는 system call

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // execl(), _exit()
#include <sys/wait.h> // wait()

// system()과 똑같은 함수를 만들어라. 
int my_system(char* command) {

    // use fork() and execl()..
    pid_t pid;
    int status;
    int execl_rv = 0;

    if(command == NULL) {
        /*
            If  command  is  NULL, then a nonzero value if a shell is available, or 0 if no
            shell is available.
        */
        return 0;
    }

    pid = fork();
    if(pid < 0) {
        /*
            If a child proqcess could not be created, or its status could not be  retrieved,
            the return value is -1 and errno is set to indicate the error.
        */
        status = -1;
    }
    else if(pid == 0) { // child process
        /*
            The exec() functions return only if an error has occurred.  The  return  value  is
            -1, and errno is set to indicate the error.
        */
        execl_rv = execl("/bin/sh", "sh", "-c", command, (char*)NULL);
        if(execl_rv == -1) { // execl()에서 에러 발생했으면
            /*
                If a shell could not be executed in the child process, then the return value is
                as though the child shell terminated by calling _exit(2) with the status 127.
            */
            _exit(127);
        }
    }

    else { // parent process
        /*
            If all system calls succeed, then the return value is the termination status of
            the child shell used to execute command.  (The termination status of a shell is
            the termination status of the last command it executes.)
        */
        wait(&status);  
        return status;  
    }

}

int main(void) {

    int status;
    status = my_system("ls -l | wc -l");
    printf("exit code %d\n", WEXITSTATUS(status));

    return 0;
}
