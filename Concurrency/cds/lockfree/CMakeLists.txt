cmake_minimum_required(VERSION 3.17)
project(Lockfree)

set(CMAKE_CXX_STANDARD 14)

include_directories(queue)
include_directories(stack/hazp)
include_directories(stack/qsrb)

add_executable(lockfrees stack/hazp/main.cpp)
add_executable(lockfreeq queue/main.cpp)
add_executable(lockfreqs stack/qsrb/main.cpp)

