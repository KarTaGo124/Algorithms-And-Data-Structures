cmake_minimum_required(VERSION 3.28)
project(Algorithms-And-Data-Structures)

set(CMAKE_CXX_STANDARD 17)

add_executable(PointersArrays 1-pointers-and-arrays/PointersArrays.cpp)
add_executable(LinkedList 2-linked-list/ForwardList.h 2-linked-list/main.cpp)
add_executable(CircularDoublyLinkedList 3-doubly-linked-list/CircularDoublyLinkedList.cpp)
add_executable(DoublyLinkedList 3-doubly-linked-list/DoublyLinkedList.cpp)
add_executable(Stack 4-stack/Stack.cpp)
add_executable(Queue 5-queue/Queue.h 5-queue/main.cpp)
add_executable(CircularQueue 5-queue/CircularQueue.cpp)
add_executable(Hash 6-hash/main.cpp 6-hash/Hash.h)
add_executable(BST 7-bst/main.cpp 7-bst/BST.h)
add_executable(BTree 8-b-tree/BTree.cpp)
add_executable(BPlus 8-b-tree/BPlus.cpp)
add_executable(Trie 9-trie/Trie.cpp)
add_executable(Graph 10-graph/Graph.h 10-graph/main.cpp)
add_executable(DisjointSet 11-disjoint-set/DisjointSet.h 11-disjoint-set/main.cpp)
