# queue
[![CMake](https://github.com/Jacob-C-Smith/queue/actions/workflows/cmake.yml/badge.svg)](https://github.com/Jacob-C-Smith/queue/actions/workflows/cmake.yml)
 
 A minimal queue implementation written in C. 
 
 > 1 [Download](#download)
 >
 > 2 [Build](#build)
 >
 > 3 [Example](#example)
 >
 >> 3.1 [Example output](#example-output)
 >
 > 4 [TODO: Tester](#tester)
 >
 > 5 [Definitions](#definitions)
 >
 >> 5.1 [Type definitions](#type-definitions)
 >>
 >> 5.2 [Function definitions](#function-definitions)

 ## Download
 To download queue, execute the following command
 ```bash
 $ git clone https://github.com/Jacob-C-Smith/queue
 ```
 ## Build
 To build on UNIX like machines, execute the following commands in the same directory
 ```bash
 $ cd queue
 $ cmake .
 $ make
 ```
  This will build the example program, the tester program, and dynamic / shared libraries

  To build queue for Windows machines, open the base directory in Visual Studio, and build your desired target(s)
 ## Example
 To run the example program, execute this command
 ```
 $ ./queue_example
 ```
 ### Example output
 ```
 TODO
 ```
 [Source](main.c)
## TODO: Tester
 To run the tester program, execute this command after building
 ```
 $ ./queue_test
 ```
 [Source](queue_test.c)
 ## Definitions
 ### Type definitions
 ```c
 typedef struct queue_s queue;
 ```
 ### Function definitions
 ```c 
// Allocaters
DLLEXPORT int   queue_create    ( queue **pp_queue );

// Constructors
DLLEXPORT int   queue_construct ( queue **pp_queue, size_t   size );

// Accessors
DLLEXPORT void *queue_front     ( queue  *p_queue );
DLLEXPORT void *queue_rear      ( queue  *p_queue );

// Mutators
DLLEXPORT int   queue_enqueue   ( queue  *p_queue , void    *data );
DLLEXPORT void *queue_dequeue   ( queue  *p_queue );
DLLEXPORT bool  queue_empty     ( queue  *p_queue );
DLLEXPORT bool  queue_full      ( queue  *p_queue );

// Destructors
DLLEXPORT int   queue_destroy   ( queue **pp_queue );
 ```