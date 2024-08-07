# Need CMake 3.16
cmake_minimum_required (VERSION 3.16.0)

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
    add_compile_options(-Wall -Wextra -Wpedantic -Wpointer-arith -Wstrict-prototypes -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -Wno-unused-value)
else()
    add_compile_definitions(NDEBUG)
endif ()

# Find the sync module
if ( NOT "${HAS_SYNC}")

    # Add the sync directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/sync ${CMAKE_SOURCE_DIR}/build/sync)

    # Let any parent project know that this project has sync
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_SYNC true PARENT_SCOPE)
        set(SYNC_INCLUDE_DIR ${SYNC_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()

# Find the log module
if ( NOT "${HAS_LOG}")
    
    # Add the log directory
    add_subdirectory(${CMAKE_SOURCE_DIR}/extern/log ${CMAKE_SOURCE_DIR}/build/log)

    # Let any parent project know that this project has log
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_LOG true PARENT_SCOPE)
        set(LOG_INCLUDE_DIR ${LOG_INCLUDE_DIR} PARENT_SCOPE)
    endif()
endif()


# Add the queue project
if ( NOT "${HAS_QUEUE}")

    # Log
    message("[queue] Adding queue project")
    
    # Set the include directory
    set(QUEUE_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

    # Let any parent project know that it has the queue project
    if(NOT PROJECT_IS_TOP_LEVEL)
        set(HAS_QUEUE true PARENT_SCOPE)
        set(QUEUE_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include PARENT_SCOPE)
    endif()
endif()

# Add source to this project's executable.
add_executable(queue_example "main.c" "queue.c")
add_dependencies(queue_example queue)
target_include_directories(queue_example PUBLIC ${QUEUE_INCLUDE_DIR})
target_link_libraries(queue_example queue)

# Add source to the tester
add_executable (queue_test "queue_test.c" "queue.c")
add_dependencies(queue_test sync queue log)
target_include_directories(queue_test PUBLIC ${QUEUE_INCLUDE_DIR} ${SYNC_INCLUDE_DIR} ${LOG_INCLUDE_DIR})
target_link_libraries(queue_test sync queue log)

# Add source to the library
add_library(queue SHARED "queue.c")
add_dependencies(queue sync log)
target_include_directories(queue PUBLIC ${QUEUE_INCLUDE_DIR} ${SYNC_INCLUDE_DIR} ${LOG_INCLUDE_DIR})
target_link_libraries(queue sync log)
