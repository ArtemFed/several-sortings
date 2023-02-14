#include "Bubble_Sort.h"

#include <vector>

#include "iostream"

// A function to implement bubble countingSort
void bubbleSort(std::vector<int> &vec, int n) {
    for (int i = 0; i < n - 1; i++) {
        // Last i elements are already
        // in place
        for (int j = 0; j < n - i - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

void BubbleSortIversonOne(std::vector<int> &vec, int n) {
    int i = 0;
    bool t = true;
    while (t) {
        t = false;
        for (int k = 0; k < n - i - 1; ++k) {
            if (vec[k] > vec[k + 1]) {
                t = true;
                std::swap(vec[k], vec[k + 1]);
            }
        }
        i++;
    }
}

void BubbleSortIversonTwo(std::vector<int> &vec, int n) {
    int t = n - 1;
    while (t != 0) {
        for (int k = 0; k < t; ++k) {
            if (vec[k] > vec[k + 1]) {
                std::swap(vec[k], vec[k + 1]);
                t = k + 1;
            }
        }
    }
}