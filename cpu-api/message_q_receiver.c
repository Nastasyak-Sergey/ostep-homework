#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

#include "message_q.h"

void report_and_exit(const char* msg){
    perror(msg);
    exit(-1);
}

int main() {
    key_t key = ftok(PathName, ProjectId);
    if (key < 0) report_and_exit("could`n get key ...");

    int qid = msgget(key, 0666| IPC_CREAT);
    if (qid < 0) report_and_exit("could`n get queue Id ...");

    int types[] = {3, 1, 2, 1, 3, 2}; /* each must be > 0 */

    int i;
    for (i = 0; i < MSG_COUNT; i++){
        queue_msg msg;
        if (msgrcv(qid, &msg, sizeof(msg), types[i], MSG_NOERROR | IPC_NOWAIT) < 0)
            puts("msgrcv trouble ...");

        printf("%s received as type %i \n", msg.payload, (int) msg.type);
    }

    if(msgctl(qid, IPC_RMID, NULL) < 0 )
        report_and_exit("trouble removing queue ...");
    
    return 0;

}
