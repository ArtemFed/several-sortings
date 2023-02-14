#include "Insertion_Sort.h"

#include <vector>

void insertionSort(std::vector<int>::iterator begin,
                   std::vector<int>::iterator end) {
    int tmp;
    for (int i = 1, j; i < end - begin; ++i) {
        tmp = *(begin + i);
        for (j = i - 1; j >= 0 && *(begin + j) >= tmp; --j) {
            *(begin + j + 1) = *(begin + j);
        }
        *(begin + j + 1) = tmp;
    }
}