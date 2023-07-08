# Need CMake 3.26
cmake_minimum_required (VERSION 3.26)

# This is the name of the repository
project ("queue")

# Set the correct paths
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/extern/)

# Comment out for Debug mode
set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Set for debug mode
if (${IS_DEBUG_BUILD})
    add_compile_definitions(NDEBUG)
endif()

# Find the sync module
if ( NOT "${HAS_SYNC}")

    # Log
    message("[queue] Adding sync project")

    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    set(HAS_SYNC true PARENT_SCOPE)
endif()

# Add the queue project
if ( NOT "${HAS_QUEUE}")

    # Log
    message("[queue] Adding queue project")

    # Let any parent project know that it has the queue project
    set(HAS_QUEUE true PARENT_SCOPE)
endif()

# Add source to the example program.
add_executable (queue_example "queue.c" "main.c")
add_dependencies(queue_example sync)
target_include_directories(queue_example PUBLIC include include/queue ${CMAKE_SOURCE_DIR}/extern/sync/include/)
target_link_libraries(queue_example sync)

# Add source to the tester program.
add_executable (queue_test "queue.c" "queue_test.c")
add_dependencies(queue_test sync)
target_include_directories(queue_test PUBLIC include include/queue ${CMAKE_SOURCE_DIR}/extern/sync/include/)
target_link_libraries(queue_test sync)

# Add source to this project's library
add_library    (queue SHARED "queue.c")
add_dependencies(queue sync)
target_include_directories(queue PUBLIC include include/queue ${CMAKE_SOURCE_DIR}/extern/sync/include/)
target_link_libraries(queue sync)
