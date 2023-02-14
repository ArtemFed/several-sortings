#include <ctime>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "10_QuickSort/Quick_Sort.h"
#include "11_HeapSort/Heap_Sort.h"
#include "12_ShellSort_Ciur/Shell_Sort_Ciur.h"
#include "13_ShellSort/Shell_Sort.h"
#include "1_SelectionSort/Selection_Sort.h"
#include "2-4_BubbleSort/Bubble_Sort.h"
#include "5_InsertionSort/Insertion_Sort.h"
#include "6_InsertionSort_Binary/Insertion_Sort_Binary.h"
#include "7_CountingSort/Counting_Sort.h"
#include "8_RadixSort/Radix_Sort.h"
#include "9_MergeSort/Merge_Sort.h"


void randomVectorGeneratorEasy(std::vector<int> &vec, int n) {
    srand(std::time(nullptr));
    for (int i = 0; i < n; ++i) {
        vec[i] = rand() % 6;
    }
}
void randomVectorGeneratorHardcore(std::vector<int> &vec, int n) {
    srand(std::time(nullptr));
    for (int i = 0; i < n; ++i) {
        vec[i] = rand() % 1000;
    }
}
void descendingOrderVectorGenerator(std::vector<int> &vec, int n) {
    int current = n;
    for (int i = 0; i < n; ++i) {
        vec[i] = current--;
    }
}

void nearlySortedVectorGenerator(std::vector<int> &vec, int n) {
    int current = 0;
    for (int i = 0; i < n; ++i) {
        vec[i] = current++;
    }
    for (int i = 0; i < int(n * 0.1 + 1); ++i) {
        std::swap(vec[rand() % n], vec[rand() % n]);
    }
}

template<typename T>
void printVec(std::vector<T> &vec) {
    for (auto item : vec) {
        std::cout << item << " ";
    }
    std::cout << "\n";
}

void testBubbleSort() {
    int current_size = 50;
    for (int i = 0; i < 5; ++i) {
        std::vector<int> vector;
        vector.resize(current_size);
        randomVectorGeneratorHardcore(vector, current_size);
        printVec(vector);
        bubbleSort(vector, current_size);
        printVec(vector);
        std::cout << "\n";
        current_size += 50;
    }

    current_size = 100;
    for (int i = 0; i < 40; ++i) {
        std::vector<int> vector;
        vector.resize(current_size);

        current_size += 100;
    }
}


void adapterSelectionSort(std::vector<int> &vec, int n) {
    selectionSort(vec);
}

void adapterCountingSort(std::vector<int> &vec, int n) {
    int max = INT16_MIN, min = INT16_MAX, x;
    for (int i = 0; i < n; ++i) {
        std::cin >> x;
        vec[i] = x;
        max = std::max(max, x);
        min = std::min(min, x);
    }
    countingSort(vec, min, max);
}

void adapterMergeSort(std::vector<int> &vec, int n) {
    std::vector<int> vectorTemp(n);
    mergeSort(vec, vectorTemp, 0, n);
}

void testAnySort(void(sortingFunc)(std::vector<int>, int), int n) {
    std::vector<int> vec(n);

    randomVectorGeneratorHardcore(vec, n);
    printVec(vec);

    sortingFunc(vec, n);
    printVec(vec);

    std::cout << "\n";
}

int main() {
    int n = 10;
    auto map = std::unordered_map<std::string, void (*)(std::vector<int> &, int)>();
    //    map["Bubble"] = testBubbleSort;
    //    map["BubbleIv1"] = BubbleSortIversonOne;
    //    map["BubbleIv2"] = BubbleSortIversonTwo;
    map["Merge"] = adapterMergeSort;

    testAnySort(reinterpret_cast<void (*)(std::vector<int>, int)>(adapterMergeSort), n);

    return 0;
}
