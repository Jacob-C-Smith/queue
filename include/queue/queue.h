/** !
 * @file queue/queue.h 
 * @author Jacob Smith
 * 
 * Include header for queue library
 */

// Include guard
#pragma once

// Standard library
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Platform dependent macros
#ifdef _WIN64
#define DLLEXPORT extern __declspec(dllexport)
#else
#define DLLEXPORT
#endif

// Forward declared structs
struct queue_s;

// Type definitions
/** !
 *  @brief The type definition of a queue struct
 */
typedef struct queue_s queue;

// Allocaters
/** !
 *  Allocate memory for a queue
 *
 * @param pp_queue return
 *
 * @sa destroy_queue
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int   queue_create    ( queue **pp_queue );

// Constructors
/** !
 *  Construct a queue with a specific number of entries
 *
 * @param pp_dict  return
 * @param size     number of queue entries. 
 *
 * @sa queue_create
 * @sa queue_destroy
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int   queue_construct ( queue **pp_queue, size_t   size );

// Accessors
/** !
 *  Get the element at the front of the queue
 *
 * @param p_queue queue
 *
 * @sa queue_rear
 *
 * @return element value on success, null pointer on error
 */
DLLEXPORT void *queue_front     ( queue  *p_queue );

/** !
 *  Get the element at the rear of the queue
 *
 * @param p_queue queue
 *
 * @sa queue_front
 *
 * @return element on success, null pointer on error
 */
DLLEXPORT void *queue_rear      ( queue  *p_queue );

// Mutators
/** !
 *  Add an element to a queue
 *
 * @param p_queue queue
 * @param data    element to add to the queue
 *
 * @sa queue_dequeue
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int   queue_enqueue   ( queue  *p_queue , void    *data );

/** !
 *  Remove an element from a queue
 *
 * @param p_queue queue
 *
 * @sa queue_enqueue
 *
 * @return element on success, null pointer on error
 */
DLLEXPORT void *queue_dequeue   ( queue  *p_queue );

/** !
 *  Check if a queue is empty
 *
 * @param p_queue queue
 *
 * @sa queue_full
 *
 * @return true if queue is empty else false
 */
DLLEXPORT bool  queue_empty     ( queue  *p_queue );

/** !
 *  Check if a queue is full
 *
 * @param p_queue queue
 *
 * @sa queue_empty
 *
 * @return true if queue is full else false
 */
DLLEXPORT bool  queue_full      ( queue  *p_queue );

// Destructors
/** !
 *  Destroy and deallocate a queue
 *
 * @param pp_queue queue
 *
 * @sa queue_create
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int   queue_destroy   ( queue **pp_queue );