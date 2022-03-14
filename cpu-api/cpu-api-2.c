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
    FILE *fd;
    fd = fopen("./test.txt", "w+");
    if(fd == NULL){
        printf("Unnable to create file test.txt\n");
        return -1; /* fopen failed */
    }

    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
    	// child: redirect standard output to a file
        fprintf(fd, "Write to file from Child\n");
    //    fclose(fd);
    } else {
        // parent goes down this path (original process)
        //int wc = wait(NULL);
    	//assert(wc >= 0);

        fprintf(fd, "Write to file from Parent\n");
        fclose(fd);
    }
    return 0;
}
