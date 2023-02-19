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

void insertionBinarySort(std::vector<int> &vec, std::size_t *count) {
    *count += 3;
    int n = int(vec.size());
    int i, j, ind, curr;

    for (i = 1; i < n; ++i) {
        j = i - 1;
        curr = vec[i];

        ind = binarySearch(vec, curr, 0, j, count);

        while (j >= ind) {
            vec[j + 1] = vec[j--];
            *count += 11;
        }
        vec[j + 1] = curr;
        *count += 12;
    }
}