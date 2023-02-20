cmake_minimum_required (VERSION 3.8)

project ("queue")

# Add source to this project's executable.
add_executable (queue_example "queue.c" "main.c")

# Add source to this project's library
add_library    (queue SHARED "queue.c")

# Define targets
target_include_directories(queue_example PUBLIC "include/")
target_include_directories(queue PUBLIC "include/")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET queue PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
