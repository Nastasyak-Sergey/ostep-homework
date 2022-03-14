#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>

#include <sys/types.h>
#include <signal.h>


 /*  https://stackoverflow.com/questions/28867909/c-synchronize-processes-using-signal */


/* https://www.linkedin.com/pulse/parent-child-process-signal-synchronization-technique-minh-pham */

//Signal handler
void handler(int sig){
    printf("Switching\n");
//    sleep(1);
}


int main(int argc, char *argv[])
{  
    setbuf(stdout, NULL); /* Disable buffering of stdout */

    pid_t pid = fork();
    signal(SIGUSR1, handler); // Setup signal handler for parent and child  

    if (pid < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (pid == 0) {
	    // child:
        printf("In child start to wait signal from parent \n");
        sleep(1);
        pause();                 // wait for the signal from the parent
        printf("Hello");
        kill(getppid(), SIGUSR1);// signal the parent
    } else {
        // parent
        printf("In parent send signal to child \n");
        sleep(1);
        kill(pid, SIGUSR1); // signal the child
        pause();            // wait for the child to signal back
        printf("Goodbay");
    }
    return 0;
}
