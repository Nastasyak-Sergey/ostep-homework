#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>

#include "message_q.h"

void report_and_exit(const char* msg){
    perror(msg);
    exit(-1);
}

int main() {
    key_t key = ftok(PathName, ProjectId);
    if (key < 0) report_and_exit("could`n get key ...");

    int qid = msgget(key, 0666 | IPC_CREAT);
    if (qid < 0) report_and_exit("could`n get queue Id ...");

    char* payloads[] = {"msg1","msg2","msg3","msg4","msg5","msg6"};
    int types[] = {1, 1, 2, 2, 3, 3}; /* each must be > 0 */

    int i;
    for (i = 0; i < MSG_COUNT; i++){
        queue_msg msg;
        /* build the message */
        msg.type = types[i];
        strcpy(msg.payload, payloads[i]);
        
        /* send the message */
        msgsnd(qid, &msg, sizeof(msg), IPC_NOWAIT); /* Don`t block */
        printf("%s sent as type %i \n", msg.payload, (int) msg.type);

    }
    
    return 0;

}
