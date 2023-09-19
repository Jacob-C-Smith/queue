/** !
 * @file queue/queue.h 
 * @author Jacob Smith
 * 
 * Include header for queue library
 */

// Include guard
#pragma once

// sync submodule
#include <sync/sync.h>

// Standard library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Platform dependent macros
#ifdef _WIN64
#define DLLEXPORT extern __declspec(dllexport)
#else
#define DLLEXPORT
#endif

// Memory management macro
#ifndef QUEUE_REALLOC
#define QUEUE_REALLOC(p, sz) realloc(p,sz)
#endif

// Forward declarations
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
DLLEXPORT int queue_create ( queue **const pp_queue );

// Constructors
/** !
 *  Construct a queue with a specific number of entries
 *
 * @param pp_queue return
 *
 * @sa queue_create
 * @sa queue_from_contents
 * @sa queue_destroy
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int queue_construct ( queue **const pp_queue );

/** !
 * TODO:
 *  Construct a queue from a void pointer array
 *
 * @param pp_queue    return
 * @param pp_contents pointer to array of void pointers to use as queue contents.
 * @param size        number of queue entries. 
 *
 * @sa queue_construct
 * @sa queue_destroy
 *
 * @return 1 on success, 0 on error
 */
DLLEXPORT int queue_from_contents ( queue **const pp_queue, void * const* const pp_contents, size_t size );

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
DLLEXPORT int queue_front ( const queue *const p_queue, const void **const pp_value );

/** !
 *  Get the element at the rear of the queue
 *
 * @param p_queue queue
 *
 * @sa queue_front
 *
 * @return element on success, null pointer on error
 */
DLLEXPORT int queue_rear ( const queue *const p_queue, const void **const pp_value );

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
DLLEXPORT int queue_enqueue ( queue *const p_queue ,  void *const data );

/** !
 *  Remove an element from a queue
 *
 * @param p_queue queue
 *
 * @sa queue_enqueue
 *
 * @return element on success, null pointer on error
 */
DLLEXPORT int queue_dequeue ( queue *const p_queue, const void **const pp_value );

/** !
 *  Check if a queue is empty
 *
 * @param p_queue queue
 *
 * @sa queue_full
 *
 * @return true if queue is empty else false
 */
DLLEXPORT bool queue_empty ( const queue *const p_queue );

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
DLLEXPORT int queue_destroy ( queue **const pp_queue );
