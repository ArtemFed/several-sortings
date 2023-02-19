#include "Counting_Sort.h"

#include <vector>

void countingSort(std::vector<int> &vec, int min, int max) {
    int k = max - min + 1;
    std::vector<int> vec_help(k, 0);
    for (int i : vec) {
        vec_help[i - min] += 1;
    }

    int it = 0;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < vec_help[i]; ++j) {
            vec[it++] = i + min;
        }
    }
}


std::size_t stableCountingSort(std::vector<int> &vec, int diffSize, int min, int n) {
    std::size_t count = diffSize + n;
    int prefCounts[diffSize];
    int tmp[n];
    for (int i = 0; i < diffSize; ++i) {
        prefCounts[i] = 0;
        count += 5;
    }

    for (int i = 0; i < n; ++i) {
        count += 13;
        // Для работы с отрицательными числами
        ++prefCounts[vec[i] - min];
        tmp[i] = vec[i];
    }

    for (int i = 1; i < diffSize; ++i) {
        count += 12;
        prefCounts[i] += prefCounts[i - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        count += 29;
        vec[prefCounts[tmp[i] - min] - 1] = tmp[i];
        --prefCounts[tmp[i] - min];
    }
    return count;
}