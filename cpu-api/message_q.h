#ifndef MSG_Q
#define MSG_Q

#define PathName "message_q.h"
#define ProjectId 123
#define MSG_LEN 4
#define MSG_COUNT 6

typedef struct {
    long type;
    char payload[MSG_LEN + 1];
} queue_msg;


#endif

