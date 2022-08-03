#include <stdio.h>

#include "include/queue/queue.h"

int main(int argc, const char* argv[])
{
	queue *q = 0;

	queue_construct(&q, 5);
	
	queue_enqueue(q, "Hello, World 1!");
	queue_enqueue(q, "Hello, World 2!");
	queue_enqueue(q, "Hello, World 3!");


	printf("%s\n", queue_dequeue(q));
	printf("%s\n", queue_dequeue(q));
	printf("%s\n", queue_dequeue(q));

	queue_enqueue(q, "Hello, World 3!");
	queue_enqueue(q, "Hello, World 2!");
	queue_enqueue(q, "Hello, World 1!");

	printf("%s\n", queue_dequeue(q));
	printf("%s\n", queue_dequeue(q));
	printf("%s\n", queue_dequeue(q));
	queue_dequeue(q);
	queue_dequeue(q);
	queue_destroy(q);

	return 0;
}