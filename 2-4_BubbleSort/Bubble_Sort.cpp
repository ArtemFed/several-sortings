#include "Bubble_Sort.h"

#include <vector>

void bubbleSort(std::vector<int> &vec, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

void bubbleSortIversonOne(std::vector<int> &vec, int n) {
    int ind = 0;
    bool flag = true;
    while (flag) {
        flag = false;
        for (int k = 0; k < n - ind - 1; ++k) {
            if (vec[k] > vec[k + 1]) {
                flag = true;
                std::swap(vec[k], vec[k + 1]);
            }
        }
        ind++;
    }
}

void bubbleSortIversonTwo(std::vector<int> &vec, int n) {
    int t = 0;
    int m = n - 1;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                t = j;
            }
        }
        if (t != 0) {
            m = t;
        }
    }
}