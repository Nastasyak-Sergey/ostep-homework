#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{   
    int x = 123;
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
	    // child:
        printf("in child x = %d\n", x);
        printf("in child x+10 = %d\n", x += 10);
    } else {
        // parent
        printf("in parent x = %d\n", x);
        printf("in parent x+11 = %d\n", x += 11);
    }
    return 0;
}
