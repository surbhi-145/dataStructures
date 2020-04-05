cmake_minimum_required(VERSION 3.15)
project(dataStructures C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(dataStructures
        AVL.c
        BinaryHeap.c
        BST.c
        BTrees.c
        hash.c
        HeapSort.c
        LevelPrintBT.c
        LinkBubble.c
        LinkedList.c
        LinkInteger.c
        LinkQueue.c
        LinkReverse.c
        LinkSelection.c
        LinkStack.c
        poly.c
        PriorityQueue.c
        Queue.c
        queueimp.c
        QueueUsingStack.c
        RedBlackTree.c
        SparseMatrix.c
        SplayTree.c
        Stack.c)
