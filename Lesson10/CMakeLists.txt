add_executable(counter src/counter.c inc/precise_counter.h inc/approximate_counter.h)
add_executable(linked_list src/linked_list.c inc/linked_list.h)
add_executable(queue src/queue.c inc/queue.h)
add_executable(hash src/hash.c inc/hash.h)

include_directories(inc)
