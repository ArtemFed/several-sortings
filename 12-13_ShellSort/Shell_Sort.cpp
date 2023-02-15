#include "Shell_Sort.h"

#include <vector>

void shellSortCiur(std::vector<int> &vec, int n) {
    std::vector<int> steps = {1750, 701, 301, 132, 57, 23, 10, 4, 1, 0};

    auto iter = std::lower_bound(steps.begin(), steps.end(), n) - 1;
    for (int step = *iter; step != steps[n - 1]; step = *(++iter)) {
        for (int i = step, j; i < n; i += 1) {
            int temp = vec[i];

            for (j = i; j >= step && vec[j - step] > temp; j -= step) {
                vec[j] = vec[j - step];
            }
            vec[j] = temp;
        }
    }
}

void shellSort(std::vector<int> &vec, int n) {
    for (int step = n / 2; step > 0; step /= 2) {
        for (int i = step, j; i < n; i += 1) {
            int temp = vec[i];

            for (j = i; j >= step && vec[j - step] > temp; j -= step) {
                vec[j] = vec[j - step];
            }
            vec[j] = temp;
        }
    }
}
