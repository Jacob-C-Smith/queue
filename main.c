#include <stdio.h>

#include <queue/queue.h>

int main ( int argc, const char *argv[] )
{

	// Initialized data
	queue *p_queue = 0;

	// Construct a queue
	queue_construct(&p_queue, 5);
	
	// Add three elements to the queue
	queue_enqueue(p_queue, "First!");
	queue_enqueue(p_queue, "Second!");
	queue_enqueue(p_queue, "Third!");

	// Empty the queue and print each element
	while ( queue_empty(p_queue) == false ) { printf("%s\n", (char *) queue_dequeue(p_queue)); }
	
	// Fill up the queue
	queue_enqueue(p_queue, "First!");
	queue_enqueue(p_queue, "Second!");
	queue_enqueue(p_queue, "Third!");
	queue_enqueue(p_queue, "Fourth!");
	queue_enqueue(p_queue, "Fifth!");

	// Cause an overflow
	queue_enqueue(p_queue, "Sixth!");

	// Empty the full queue
	while ( queue_empty(p_queue) == false ) { printf("%s\n", (char *) queue_dequeue(p_queue)); }

	// Cause an underflow
	queue_dequeue(p_queue);

	// Destroy the queue
	queue_destroy(&p_queue);

	// Success
	return 0;
}