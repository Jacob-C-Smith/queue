#include <stdio.h>

#include <queue/queue.h>

int main ( int argc, const char *argv[] )
{

	// Initialized data
	queue *p_queue = 0;
	void  *value   = 0;

	// Construct a queue
	queue_construct(&p_queue, 5);
	
	// Add three elements to the queue
	queue_enqueue(p_queue, "First!");
	queue_enqueue(p_queue, "Second!");
	queue_enqueue(p_queue, "Third!");

	// Empty the queue and print each element
	while ( queue_empty(p_queue) == false ) { void *v = 0; queue_dequeue(p_queue,&v); printf("%s\n", (char *) v); }
	
	printf("\n");

	// Fill up the queue
	queue_enqueue(p_queue, "First!");
	queue_enqueue(p_queue, "Second!");
	queue_enqueue(p_queue, "Third!");
	queue_enqueue(p_queue, "Fourth!");
	queue_enqueue(p_queue, "Fifth!");
	queue_enqueue(p_queue, "Sixth!");
	queue_dequeue(p_queue, 0);
	queue_dequeue(p_queue, 0);
	queue_dequeue(p_queue, 0);

	// Empty the full queue
	while ( queue_empty(p_queue) == false ) { void *v = 0; queue_dequeue(p_queue,&v); printf("%s\n", (char *) v); }

	// Cause an underflow
	if ( queue_dequeue(p_queue, &value) == 0 )
		printf("Detected queue underflow!\n");

	// Destroy the queue
	queue_destroy(&p_queue);

	// Success
	return 0;
}