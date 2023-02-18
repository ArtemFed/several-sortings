#include "Insertion_Sort.h"

#include <vector>

int insertionSort(std::vector<int>::iterator begin,
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
    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (vec[middle] == value) {
            return middle + 1;
        } else if (vec[middle] < value) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return left;
}

int insertionBinarySort(std::vector<int> &vec) {
    int n = int(vec.size());
    int i, j, ind, curr;

    for (i = 1; i < n; ++i) {
        j = i - 1;
        curr = vec[i];

        ind = binarySearch(vec, curr, 0, j);

        while (j >= ind) {
            vec[j + 1] = vec[j--];
        }
        vec[j + 1] = curr;
    }
}