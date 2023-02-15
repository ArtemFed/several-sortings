cmake_minimum_required(VERSION 3.24)
project(HW1)

set(CMAKE_CXX_STANDARD 17)

add_executable(HW1 main.cpp
        1_SelectionSort/Selection_Sort.cpp
        2-4_BubbleSort/Bubble_Sort.cpp
        5-6_InsertionSort/Insertion_Sort.cpp
        7_CountingSort/Counting_Sort.cpp
        8_RadixSort/Radix_Sort.cpp
        9_MergeSort/Merge_Sort.cpp
        10_QuickSort/Quick_Sort.cpp
        11_HeapSort/Heap_Sort.cpp
        12-13_ShellSort/Shell_Sort.cpp
        Generator.cpp
        Distributor.cpp)
