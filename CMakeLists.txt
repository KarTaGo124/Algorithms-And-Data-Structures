cmake_minimum_required(VERSION 3.28)
project(Algorithms-And-Data-Structures)

set(CMAKE_CXX_STANDARD 17)

add_executable(PointersArrays 1-pointers-and-arrays/PointersArrays.cpp)
add_executable(LinkedList 2-linked-list/ForwardList.cpp)
add_executable(CircularDoublyLinkedList 3-doubly-linked-list/CircularDoublyLinkedList.cpp)
add_executable(DoublyLinkedList 3-doubly-linked-list/DoublyLinkedList.cpp)
add_executable(Stack 4-stack/Stack.cpp)
add_executable(Queue 5-queue/Queue.cpp)
add_executable(CircularQueue 5-queue/CircularQueue.cpp)
add_executable(Hash 6-hash/main.cpp 6-hash/Hash.h)
