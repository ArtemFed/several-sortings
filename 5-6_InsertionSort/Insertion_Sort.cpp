#include "Insertion_Sort.h"

#include <vector>

std::size_t insertionSort(std::vector<int>::iterator begin,
                          std::vector<int>::iterator end) {
    std::size_t count = 1;
    int tmp;
    for (int i = 1, j; i < end - begin; ++i) {
        tmp = *(begin + i);
        for (j = i - 1; j >= 0 && *(begin + j) >= tmp; --j) {
            count += 13;
            *(begin + j + 1) = *(begin + j);
        }
        count += 12;
        *(begin + j + 1) = tmp;
    }
    return count;
}

int binarySearch(std::vector<int> vec, int value, int left, int right, std::size_t *count) {
    while (left <= right) {
        *count += 9;

        int middle = left + (right - left) / 2;

        if (vec[middle] == value) {
            return middle + 1;
        } else if (vec[middle] < value) {
            *count += 6;
            left = middle + 1;
        } else {
            *count += 6;
            right = middle - 1;
        }
    }

    return left;
}

void insertionBinarySort(std::vector<int> &vec, int n, std::size_t *count) {
    int i, position, j, tmp;

    *count += 1;
    for (i = 1; i < n; ++i) {
        j = i - 1;
        tmp = vec[i];

        position = binarySearch(vec, tmp, 0, j, count);

        while (j >= position) {
            vec[j + 1] = vec[j];
            j--;
            *count += 10;
        }
        vec[j + 1] = tmp;
        *count += 15;
    }
}