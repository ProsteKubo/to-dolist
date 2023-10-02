cmake_minimum_required(VERSION 3.26)
project(to_dolist C)

set(CMAKE_C_STANDARD 99)

include_directories(src)
include_directories(test)

add_executable(to_dolist
        src/main.c
        src/map.h
        src/task.h
        src/utilities/task_list.c
        src/utilities/task_list.h
        src/task.c
)
