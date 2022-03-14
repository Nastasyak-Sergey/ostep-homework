#include <stdio.h>
#include <stdlib.h> /* exit function */
#include <unistd.h> /* read, write, pipe, _exit */
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h> /* wait */

#define READ_END 0
#define WRITE_END 1

// https://stackoverflow.com/questions/6542491/how-to-create-two-processes-from-a-single-parent
// https://opensource.com/article/19/4/interprocess-communication-linux-channels


void report_and_exit(const char* msg){
    perror(msg);
    exit(-1); /* failure */ 
} 


int main(int argc, char *argv[])
{
    int pipe_fd[2]; /* two file descriptors */
    char buf;       /* 1-byte buffer */
    const char* msg = "Test msg through the pipe\n";

    pid_t child_a, child_b;


    if(pipe(pipe_fd) < 0) report_and_exit("Pipe FD");

    child_a = fork();
    // Creation of child A fail
    if (child_a < 0) report_and_exit("Fork A");

    if (child_a == 0) {
	    // child A code:
        close(pipe_fd[WRITE_END]);
        printf("Hello from child A\n");
        while(read(pipe_fd[READ_END], &buf, 1) > 0) /* Read until end of the stream */
            write(STDOUT_FILENO, &buf, sizeof(buf)); /* Echo to the standartoutput */
        close(pipe_fd[READ_END]);
        _exit(0);

    } else {
        child_b = fork();
        if (child_b < 0) report_and_exit("Fork B");
        if (child_b == 0){
            // child B code
            printf("Hello from child B\n");
            close(pipe_fd[READ_END]);
            printf("Send msg from B to A\n");
            write(pipe_fd[WRITE_END], msg, strlen(msg));
            close(pipe_fd[WRITE_END]);
            
            wait(NULL);

            exit(0);

        } else {
            // parent goes down this path (original process)
            close(pipe_fd[WRITE_END]);
            close(pipe_fd[READ_END]);
            printf("Hello from parent\n");
            wait(NULL);
        }
    }
    return 0;
}
