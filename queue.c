#include <queue/queue.h>

struct queue_node_s
{
	void              *content;
	struct queue_node *prev,
	                  *next;
};

struct queue_s
{
	struct queue_node *front,
                      *rear;
};

int  queue_create ( queue **pp_queue)
{

	// Argument check
	{
		#ifndef NDEBUG
			if(pp_queue == (void *)0)
				goto no_queue;
		#endif
	}

	// Initialized data
	queue *ret = calloc(1, sizeof(queue));

	// Check memory
	{
		#ifndef NDEBUG
			if ( ret == (void *)0 )
				goto no_mem;
		#endif
	}

	// Return the queue
	*pp_queue = ret;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"pp_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif

			// Error
			return 0;
		}

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					printf("[Standard Library] Failed to allocate memory in call to function \"%s\"\n",__FUNCTION__);
				#endif

			// Error
			return 0;
		}
	}
}
 
int  queue_construct ( queue **pp_queue )
{

	// Argument check
	{
		#ifndef NDEBUG
			if(pp_queue == (void *)0)
				goto no_queue;
		#endif
	}

	// Initialized data
	queue *i_queue = 0;

	// Allocate for a queue
	if ( queue_create(pp_queue) == 0 ) 
		goto failed_to_create_queue;

	// Get a pointer to the allocated memory
	i_queue = *pp_queue;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"pp_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif
			
			// Error
			return 0;

			no_queue_size:
				#ifndef NDEBUG
					printf("[Queue] \"size\" must be greater than or equal to 1 in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
			// Error
			return 0;
		}

		// Queue errors
		{
			failed_to_create_queue:
				#ifndef NDEBUG
					printf("[Queue] Failed to create queue in call to function \"%s\"\n", __FUNCTION__);
				#endif

			// Error
			return 0;
		}

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					printf("[Standard Library] Failed to allocate memory in call to function \"%s\"\n",__FUNCTION__);
				#endif
			
			// Error
			return 0;
		}
	}
}
 
int queue_from_contents ( queue **pp_queue, void **pp_contents, size_t size )
{

	// Argument check
	{
		if ( pp_queue == (void *)0)
			goto no_queue;
		if ( pp_contents == (void *)0)
			goto no_queue_contents;
		if ( size == 0 )
			goto no_queue_contents;
	}

	if (queue_construct(pp_queue))

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"p_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif
			
			// Error
			return 0;

			no_queue_contents:
				#ifndef NDEBUG
					printf("[Queue] Queue has no contents in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
			// Error
			return 0;
		}
	}
}


int  queue_front ( queue* p_queue, void **pp_value )
{

	// Argument check
	{
		if ( p_queue == (void *)0)
			goto no_queue;
		if ( pp_value == (void *)0)
			goto no_ret;
		if ( queue_empty(p_queue) )
			goto no_queue_contents;
	}

	*pp_value = ((struct queue_node_s *)(p_queue->front))->content;

	no_ret:
	
	// Exit
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"p_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif
			
			// Error
			return 0;

			no_queue_contents:
				#ifndef NDEBUG
					printf("[Queue] Queue has no contents in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
			// Error
			return 0;
		}
	}
}
 
int  queue_rear ( queue* p_queue, void **pp_value)
{

	// Argument check
	{
		if ( p_queue == (void *) 0 )
			goto no_queue;
		if ( pp_value == (void *) 0 )
			goto no_ret;
		if ( queue_empty(p_queue) )
			goto no_queue_contents;
	}

	//while(((struct queue_node_s *)p_queue->rear)->next) { p_queue->rear = ((struct queue_node_s *)p_queue->rear)->next; };

	*pp_value = ((struct queue_node_s *)(p_queue->rear))->content;

	no_ret:
	
	// Exit
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"p_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif
			
			// Error
			return 0;

			no_queue_contents:
				#ifndef NDEBUG
					printf("[Queue] Queue has no contents in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
			// Error
			return 0;
		}
	}
}
 
int  queue_enqueue ( queue* p_queue, void* data)
{

	// Argument check
	{
		#ifndef NDEBUG
			if (p_queue == (void *)0)
				goto no_queue;
		#endif

	}

	// Initialized data
	struct queue_node_s *q = p_queue->rear, // Q comes before R(ear)
	                    *r = calloc(1, sizeof(struct queue_node_s));
	
	// Walk to the end from the rear
	if (!q)
	{
		q = p_queue->front = p_queue->rear = r;
	}
	else
	{
		while ( q->next != 0 ) { q = q->next; }; q->next = r;
		r->prev = q;
		p_queue->rear = r;
	}

	r->content = data;
	

	// Success
	return 1;
		
	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"p_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif

			// Error
			return 0;

			queue_overflow:
				#ifndef NDEBUG
					printf("[Queue] Queue overflow in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
			// Error
			return 0;
		}
	}
}
 
int  queue_dequeue ( queue* p_queue, void **pp_value )
{
	
	// Argument check
	{
		#ifndef NDEBUG
			if (p_queue == (void *)0)
				goto no_queue;
		#endif

		if (p_queue->front==0)
			return 0;
	}

	// Initialized data
	void **pp_ret = 0;
	struct queue_node_s *ret_m = 0,
	                    *ret_n = 0;

	ret_m = ((struct queue_node_s *)(p_queue->front));

	// Remove the front
	if (p_queue->front != p_queue->rear)
	{
		p_queue->front = ((struct queue_node_s *)(p_queue->front))->next;
		
	}
	else
		p_queue->front = 0,
		p_queue->rear  = 0;

	if(pp_value)
		*pp_value = ret_m->content;

	free(ret_n);

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"p_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif

			// Error
			return 0;

			queue_underflow:
				#ifndef NDEBUG
					printf("[Queue] Queue underflow in call to function \"%s\"\n", __FUNCTION__);
				#endif

			// Error
			return 0;
		}
	}
}

bool queue_empty ( queue *p_queue )
{
	
	// Argument check
	{
		#ifndef MDEBIG
			if ( p_queue == (void *)0 )
				goto no_p_queue;
		#endif
	}

	// Initialized data
	return p_queue->front == 0;

	// Error handling
	{

		// Argument errors
		{
			no_p_queue:
				#ifndef NDEBUG
					printf("[queue] Null pointer provided for parameter \"p_queue\" in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
			// Error
			return 0;
		}
	}
}

int  queue_destroy ( queue **pp_queue)
{

	// Argument check
	{
		#ifndef NDEBUG
			if (pp_queue == (void *)0)
				goto no_queue;
		#endif
	}

	// Initialized data
	queue *p_queue = *pp_queue;

	// No more queue for end user
	*pp_queue = 0;

	// Free the queue
	free(p_queue);

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"pp_queue\" in call to function \"%s\"\n",__FUNCTION__);
				#endif

			// Error
			return 0;
		}
	}
}
