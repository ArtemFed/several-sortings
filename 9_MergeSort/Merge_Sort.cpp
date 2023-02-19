#include "Merge_Sort.h"

// Merges two subarrays of vec[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
//template<typename T>
void merge(std::vector<int> &vec, std::vector<int> &vecTemp, int begin, int middle, int end, std::size_t *count) {
    int iterMain = begin;
    int iterTemp = 0;
    int mid = middle + 1;
    *count += 4;
    while (iterMain <= middle && mid <= end) {
        if (vec[iterMain] < vec[mid]) {
            vecTemp[iterTemp++] = vec[iterMain++];
            *count += 11;
        } else {
            vecTemp[iterTemp++] = vec[mid++];
            *count += 11;
        }
        *count += 10;
    }

    for (; iterMain <= middle; ++iterMain) {
        vecTemp[iterTemp++] = vec[iterMain];
        *count += 12;
    }

    for (; mid <= end; ++mid) {
        vecTemp[iterTemp++] = vec[mid];
        *count += 12;
    }

    for (auto i = begin; i <= end; ++i) {
        vec[i] = vecTemp[i - begin];
        *count += 11;
    }
}

//template<typename T>
void mergeSort(std::vector<int> &vec, std::vector<int> &vecTemp, int begin, int end, std::size_t *count) {
    *count += 1;
    if (begin >= end) {
        return;
    }

    int middle = begin + (end - begin) / 2;
    mergeSort(vec, vecTemp, begin, middle, count);
    mergeSort(vec, vecTemp, middle + 1, end, count);
    *count += 5;
    merge(vec, vecTemp, begin, middle, end, count);
}