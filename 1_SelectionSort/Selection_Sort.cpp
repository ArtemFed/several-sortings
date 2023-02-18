#include "Selection_Sort.h"

#include <vector>

std::size_t selectionSort(std::vector<int> &vec, int n) {
    std::size_t count = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_ind = i;

        for (int j = i + 1; j < n; j++) {
            if (vec[j] < vec[min_ind]) {
                min_ind = j;
            }
        }

        std::swap(vec[min_ind], vec[i]);
    }
//    return counter;
}
