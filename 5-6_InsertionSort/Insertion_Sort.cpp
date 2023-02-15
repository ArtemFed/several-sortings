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

int binarySearch(std::vector<int> vec, int value, int left, int right) {
    if (right <= left) {
        return (value > vec[left]) ? (left + 1) : left;
    }

    int middle = left + (right - left) / 2;

    if (value == vec[middle]) {
        return middle + 1;
    }

    if (value > vec[middle]) {
        return binarySearch(vec, value, middle + 1, right);
    }
    return binarySearch(vec, value, left, middle - 1);
}

void insertionBinarySort(std::vector<int> &vec) {
    int n = int(vec.size());
    int i, j, loc, selected;

    for (i = 1; i < n; ++i) {
        j = i - 1;
        selected = vec[i];

        loc = binarySearch(vec, selected, 0, j);

        while (j >= loc) {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = selected;
    }
}