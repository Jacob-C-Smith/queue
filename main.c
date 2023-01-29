#include <stdio.h>

#include <queue/queue.h>

int main ( int argc, const char *argv[] )
{

	// Initialized data
	queue *q = 0;

	// Construct a queue
	queue_construct(&q, 5);
	
	// Add three elements to the queue
	queue_enqueue(q, "Hello, World 1!");
	queue_enqueue(q, "Hello, World 2!");
	queue_enqueue(q, "Hello, World 3!");

	// Empty the queue and print each element
	while ( queue_empty(q) == false )
		printf("%s\n", queue_dequeue(q));

	// Fill up the queue
	queue_enqueue(q, "Hello, World 6!");
	queue_enqueue(q, "Hello, World 5!");
	queue_enqueue(q, "Hello, World 4!");
	queue_enqueue(q, "Hello, World 3!");
	queue_enqueue(q, "Hello, World 2!");

	// Cause an overflow
	queue_enqueue(q, "Hello, World 1!");

	// Empty the full queue
	while (queue_empty(q)==false) printf("%s\n", queue_dequeue(q));
	
	// Cause an underflow
	queue_dequeue(q);

	// Destroy the queue
	queue_destroy(q);

	// Success
	return 0;
}