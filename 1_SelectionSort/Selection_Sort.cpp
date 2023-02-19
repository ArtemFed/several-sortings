#include "Selection_Sort.h"

#include <vector>

std::size_t selectionSort(std::vector<int> &vec, int n) {
    std::size_t count = 1;
    for (int i = 0; i < n - 1; i++) {
        int min_ind = i;
        count += 7;

        for (int j = i + 1; j < n; j++) {
            if (vec[j] < vec[min_ind]) {
                min_ind = j;
                count += 1;
            }
            count += 10;
        }

        std::swap(vec[min_ind], vec[i]);
        count += 9;
    }
    return count;
}
