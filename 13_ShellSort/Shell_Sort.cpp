#include "Shell_Sort.h"

#include <vector>

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
