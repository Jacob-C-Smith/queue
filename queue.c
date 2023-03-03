#include <queue/queue.h>

struct queue_s
{
	void   **contents;
	size_t   size;
	size_t   front;
	size_t   rear;
};

int queue_create(queue** pp_queue)
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

int queue_construct(queue** pp_queue, size_t size)
{

	// Argument check
	{
		#ifndef NDEBUG
			if(pp_queue == (void *)0)
				goto no_queue;
			if (size == 0)
				goto no_queue_size;
		#endif
	}

	// Initialized data
	queue *i_queue = 0;

	// Allocate for a queue
	if ( queue_create(pp_queue) == 0 ) 
		goto failed_to_create_queue;

	// Get a pointer to the allocated memory
	i_queue = *pp_queue;

	// Construct the queue
	{
		i_queue->contents = calloc(size, sizeof(void *));

		// Check memory
		{
			#ifndef NDEBUG
				if ( i_queue->contents == (void *)0 )
					goto no_mem;
			#endif
		}

		i_queue->front    = -1;
		i_queue->rear     = -1;
		i_queue->size     = size;
	}

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

void* queue_front(queue* p_queue)
{

	// Argument check
	{
		#ifndef NDEBUG
			if(p_queue == (void *)0)
				goto no_queue;
			if (p_queue->size == 0)
				goto no_queue_size;
		#endif
	}

	// Return the element at the front of the queue
	return p_queue->contents[p_queue->front];

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

			no_queue_size:
				#ifndef NDEBUG
					printf("[Queue] \"size\" must be greater than or equal to 1 in call to function \"%s\"\n", __FUNCTION__);
				#endif
			
			// Error
			return 0;
		}
	}
}

void* queue_rear(queue* p_queue)
{

	// Argument check
	{
		#ifndef NDEBUG
			if(p_queue == (void *)0)
				goto no_queue;
		#endif
	}

	// Return the element at the rear of the queue
	return p_queue->contents[p_queue->rear];

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
		}
	}
}

int queue_enqueue(queue* p_queue, void* data)
{

	// Argument check
	{
		#ifndef NDEBUG
			if (p_queue == (void *)0)
				goto no_queue;
		#endif
	}

	// Check for overflow
	if ( queue_full(p_queue) )
		goto queue_overflow;

	// Has the queue been reset?
	if (p_queue->front == -1)
		p_queue->front = 0;

	// Add the data to the queue
	p_queue->contents[++p_queue->rear] = data;

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

void* queue_dequeue ( queue* p_queue )
{
	
	// Argument check
	{
		#ifndef NDEBUG
			if (p_queue == (void *)0)
				goto no_queue;
		#endif
	}

	// Initialized data
	void* ret = 0;

	// Check for an underflow
	if ( queue_empty(p_queue) )
		goto queue_underflow;

	// Get the return value
	ret = p_queue->contents[p_queue->front];

	// If that was the last element, reset the queue
	if (p_queue->front >= p_queue->rear)
		p_queue->front = -2, 
		p_queue->rear  = -1;

	p_queue->front++;

	// Return a pointer to the element
	return ret;

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

bool queue_empty(queue* p_queue)
{
		
	// Argument check
	{
		#ifndef NDEBUG
			if (p_queue == (void *)0)
				goto no_queue;
		#endif
	}

	// Return true if the queue is empty, false otherwise
	return (p_queue->front == -1) ? true : false;
	
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
		}
	}
}

bool queue_full(queue* p_queue)
{
		
	// Argument check
	{
		#ifndef NDEBUG
			if (p_queue == (void *)0)
				goto no_queue;
		#endif
	}
	
	// Return true if queue is full, false otherwise
	return (p_queue->front == 0 && p_queue->rear == p_queue->size -1 ) ? true : false;

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
		}
	}
}

int queue_destroy(queue **pp_queue)
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

	// Free the queue contents
	free(p_queue->contents);

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
