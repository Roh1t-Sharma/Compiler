cmake_minimum_required(VERSION 3.27)
project(MemoryManger)

set(CMAKE_CXX_STANDARD 17)

add_executable(MemoryManger
        main.cpp
        include/Heap.h
        src/Heap.cpp
#        src/MemoryBlock.cpp
#        include/structures.h
        src/HashTable.cpp
)
