#include "Counting_Sort.h"

#include <vector>

void countingSort(std::vector<int>& vec, int min, int max) {
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