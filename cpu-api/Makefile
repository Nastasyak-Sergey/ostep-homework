
all: 1 2 3

clean:
	rm -f cpu-api-1 cpu-api-2 test.txt cpu-api-3 cpu-api-4 cpu-api-7 cpu-api-8  msg_q_receive msg_q_send

1: cpu-api-1.c
	gcc -o cpu-api-1 cpu-api-1.c -Wall
	./cpu-api-1

2: cpu-api-2.c
	gcc -o cpu-api-2 cpu-api-2.c -Wall
	./cpu-api-2
	cat test.txt

3: cpu-api-3.c
	gcc -o cpu-api-3 cpu-api-3.c -Wall
	./cpu-api-3

4: cpu-api-4.c
	gcc -o cpu-api-4 cpu-api-4.c -Wall
	./cpu-api-4

7: cpu-api-7.c
	gcc -o cpu-api-7 cpu-api-7.c -Wall
	./cpu-api-7

8: cpu-api-8.c
	gcc -o cpu-api-8 cpu-api-8.c -Wall
	./cpu-api-8

queue: queue_send queue_receive

queue_send: message_q_sender.c
	gcc -o msg_q_send message_q_sender.c -Wall

queue_receive: message_q_receiver.c
	gcc -o msg_q_receive message_q_receiver.c -Wall

