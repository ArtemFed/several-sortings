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
    std::size_t count = 1;
    bool flag;

    for (int i = 0; i < n - 1; ++i) {
        flag = false;

        for (int j = 0; j < n - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                flag = true;
                count += 11;
            }
            count += 13;
        }
        count += 4;
        if (!flag) {
            break;
        }
    }
    return count;
}

std::size_t bubbleSortIversonTwo(std::vector<int> &vec, int n) {
    std::size_t count = 3;
    int prev = n - 1;
    bool flag;
    for (int i = 0; i < n - 1; ++i) {
        flag = false;
        int top = prev;
        prev = 0;

        for (int j = 0; j < top; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                flag = true;
                prev = j;
                count += 12;
            }
            count += 11;
        }

        count += 10;
        if (!flag) {
            break;
        }
    }
    return count;
}