#include "Insertion_Sort_binary.h"
#include <vector>

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

void BinaryInsertionSort(std::vector<int> &vec) {
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