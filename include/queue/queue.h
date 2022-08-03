#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DLLEXPORT extern __declspec(dllexport)

struct queue_s
{
	void   **contents;
	size_t   size;
	size_t   front;
	size_t   rear;
};

typedef struct queue_s queue;

DLLEXPORT int   queue_create    ( queue **pp_queue );
DLLEXPORT int   queue_construct ( queue **pp_queue, size_t   size );
DLLEXPORT void *queue_front     ( queue  *p_queue );
DLLEXPORT void *queue_rear      ( queue  *p_queue );
DLLEXPORT int   queue_enqueue   ( queue  *p_queue , void    *data );
DLLEXPORT void *queue_dequeue   ( queue  *p_queue );
DLLEXPORT bool  queue_empty     ( queue  *p_queue );
DLLEXPORT bool  queue_full      ( queue  *p_queue );
DLLEXPORT int   queue_destroy   ( queue  *p_queue );