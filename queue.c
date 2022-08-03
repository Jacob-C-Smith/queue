#include "include\queue\queue.h"

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

	*pp_queue = ret;

	return 0;

	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"pp_queue\" in call to function \"%s\"\n",__FUNCSIG__);
				#endif
			return 0;
		}

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					printf("[Standard Library] Failed to allocate memory in call to function \"%s\"\n",__FUNCSIG__);
				#endif
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
	queue_create(pp_queue);

	i_queue = *pp_queue;

	// Construct the queue
	{
		i_queue->contents = calloc(size, sizeof(void *));
		i_queue->front    = -1;
		i_queue->rear     = -1;
		i_queue->size     = size;
	}

	return 0;

	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"pp_queue\" in call to function \"%s\"\n",__FUNCSIG__);
				#endif
			return 0;

			no_queue_size:
				#ifndef NDEBUG
					printf("[Queue] \"size\" must be greater than or equal to 1 in call to function \"%s\"\n", __FUNCSIG__);
				#endif
			return 0;
		}

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					printf("[Standard Library] Failed to allocate memory in call to function \"%s\"\n",__FUNCSIG__);
				#endif
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

	return p_queue->contents[p_queue->front];

	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"p_queue\" in call to function \"%s\"\n",__FUNCSIG__);
				#endif
			return 0;

			no_queue_size:
				#ifndef NDEBUG
					printf("[Queue] \"size\" must be greater than or equal to 1 in call to function \"%s\"\n", __FUNCSIG__);
				#endif
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

	return p_queue->contents[p_queue->rear];

	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"p_queue\" in call to function \"%s\"\n",__FUNCSIG__);
				#endif
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
	if (queue_full(p_queue))
		goto queue_overflow;

	// Has the queue been reset?
	if (p_queue->front == -1)
		p_queue->front = 0;

	// Add the data to the queue
	p_queue->contents[++p_queue->rear] = data;

	return 0;
		
	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"p_queue\" in call to function \"%s\"\n",__FUNCSIG__);
				#endif
			return 0;

			queue_overflow:
				#ifndef NDEBUG
					printf("[Queue] Queue overflow in call to function \"%s\"\n", __FUNCSIG__);
				#endif
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

	//Check for an underflow
	if ( queue_empty(p_queue) )
		goto queue_underflow;

	// Get the return value
	ret = p_queue->contents[p_queue->front];

	// If that was the last element, reset the queue
	if (p_queue->front >= p_queue->rear)
		p_queue->front = -2, 
		p_queue->rear  = -1;

	
	p_queue->front++;

	return ret;

	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"p_queue\" in call to function \"%s\"\n",__FUNCSIG__);
				#endif
			return 0;

			queue_underflow:
				#ifndef NDEBUG
					printf("[Queue] Queue underflow in call to function \"%s\"\n", __FUNCSIG__);
				#endif
			return 0;
		}
	}
	return 0;
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

	return (p_queue->front == -1) ? true : false;
	
	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"p_queue\" in call to function \"%s\"\n",__FUNCSIG__);
				#endif
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

	return (p_queue->front == 0 && p_queue->rear == p_queue->size -1 ) ? true : false;

	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"p_queue\" in call to function \"%s\"\n",__FUNCSIG__);
				#endif
			return 0;
		}
	}
}

int queue_destroy(queue* p_queue)
{

	// Argument check
	{
		#ifndef NDEBUG
			if (p_queue == (void *)0)
				goto no_queue;
		#endif
	}

	free(p_queue->contents);
	free(p_queue);
	return 0;

	// Error handling
	{

		// Argument errors
		{
			no_queue:
				#ifndef NDEBUG
					printf("[Queue] Null pointer provided for \"p_queue\" in call to function \"%s\"\n",__FUNCSIG__);
				#endif
			return 0;
		}
	}
}
