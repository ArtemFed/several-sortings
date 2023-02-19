#include "Bubble_Sort.h"

#include <vector>

std::size_t bubbleSort(std::vector<int> &vec, int n) {
    std::size_t count = 1;
    for (int i = 0; i < n - 1; i++) {
        count += 5;
        for (int j = 0; j < n - i - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                count += 10;
            }
            count += 13;
        }
    }
    return count;
}

std::size_t bubbleSortIversonOne(std::vector<int> &vec, int n) {
    std::size_t count = 2;
    int ind = 0;
    bool flag = true;
    while (flag) {
        flag = false;
        for (int k = 0; k < n - ind - 1; ++k) {
            if (vec[k] > vec[k + 1]) {
                flag = true;
                std::swap(vec[k], vec[k + 1]);
                count += 11;
            }
            count += 13;
        }
        ind++;
        count += 4;
    }
    return count;
}

std::size_t bubbleSortIversonTwo(std::vector<int> &vec, int n) {
    std::size_t count = 4;
    int t = 0;
    int m = n - 1;
    for (int i = 0; i < n - 1; i++) {
        count += 5;
        for (int j = 0; j < m; j++) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                t = j;
                count += 11;
            }
            count += 11;
        }
        if (t != 0) {
            m = t;
            count += 1;
        }
        count += 1;
    }
    return count;
}