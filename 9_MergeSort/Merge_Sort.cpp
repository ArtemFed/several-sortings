#include "Merge_Sort.h"

// Merges two subarrays of vec[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
//template<typename T>
void merge(std::vector<int> &vec, std::vector<int> &vecTemp, int begin, int middle, int end) {
    int iterMain = begin;
    int iterTemp = 0;
    int mid = middle + 1;

    while (iterMain <= middle && mid <= end) {
        if (vec[iterMain] < vec[mid]) {
            vecTemp[iterTemp++] = vec[iterMain++];
        } else {
            vecTemp[iterTemp++] = vec[mid++];
        }
    }

    for (; iterMain <= middle; ++iterMain) {
        vecTemp[iterTemp++] = vec[iterMain];
    }

    for (; mid <= end; ++mid) {
        vecTemp[iterTemp++] = vec[mid];
    }

    for (auto i = begin; i <= end; ++i) {
        vec[i] = vecTemp[i - begin];
    }
}

//template<typename T>
void mergeSort(std::vector<int> &vec, std::vector<int> &vecTemp, int begin, int end) {
    if (begin >= end) {
        return;
    }

    int middle = begin + (end - begin) / 2;
    mergeSort(vec, vecTemp, begin, middle);
    mergeSort( vec, vecTemp, middle + 1, end);
    merge(vec, vecTemp, begin, middle, end);
}