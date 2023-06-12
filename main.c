#include <stdio.h>

#include <queue/queue.h>

int main ( int argc, const char *argv[] )
{

	// Initialized data
	queue  *p_queue       = 0;
	void   *value         = 0;
	char   *pp_contents[] = { "First!", "Second!", "Third!", "Fourth!", "Fifth!", "Sixth!", 0x0 };

	// Construct a queue
	queue_construct(&p_queue);
	
	// Add three elements to the queue
	queue_enqueue(p_queue, "First!");
	queue_enqueue(p_queue, "Second!");
	queue_enqueue(p_queue, "Third!");

	// Empty the queue and print each element
	while ( queue_empty(p_queue) == false ) { void *v = 0; queue_dequeue(p_queue,&v); printf("%s\n", (char *) v); }
	
	printf("\n");

	// Fill up the queue
	queue_from_contents(&p_queue, (void **)pp_contents, 6);
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