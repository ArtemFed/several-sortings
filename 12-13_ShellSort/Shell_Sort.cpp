#include "Shell_Sort.h"

#include <vector>

std::size_t shellSortCiur(std::vector<int> &vec, int n) {
    std::size_t count = 22;
    std::vector<int> steps = {0, 1, 4, 10, 23, 57, 132, 301, 701, 1750};

    auto iter = std::lower_bound(steps.begin(), steps.end(), n) - 1;
    for (int step = *iter; step != *steps.begin(); step = *(--iter)) {
        count += 8;
        for (int i = step, j; i < n; i += 1) {
            count += 12;

            int temp = vec[i];

            for (j = i; j >= step && vec[j - step] > temp; j -= step) {
                count += 17;
                vec[j] = vec[j - step];
            }
            vec[j] = temp;
        }
    }
    return count;
}

std::size_t shellSort(std::vector<int> &vec, int n) {
    std::size_t count = 2;
    for (int step = n / 2; step > 0; step /= 2) {
        count += 4;
        for (int i = step, j; i < n; i += 1) {
            count += 11;
            int temp = vec[i];
            for (j = i; j >= step && vec[j - step] > temp; j -= step) {
                count += 8;
                vec[j] = vec[j - step];
            }
            vec[j] = temp;
        }
    }
    return count;
}
