cmake_minimum_required (VERSION 3.26)

project ("queue")

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")
if ( NOT "${HAS_QUEUE}")
    message("[queue] Adding queue project")
    set(HAS_QUEUE true PARENT_SCOPE)
endif()

if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif()

# Add source to the example program.
add_executable (queue_example "queue.c" "main.c")
target_include_directories(queue_example PUBLIC "include")

# Add source to the tester program.
add_executable (queue_test "queue.c" "queue_test.c")
target_include_directories(queue_test PUBLIC "include")

# Add source to this project's library
add_library    (queue SHARED "queue.c")
target_include_directories(queue PUBLIC include include/queue)

