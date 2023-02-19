#include "Heap_Sort.h"

void heapify(std::vector<int> &vec, int n, int i, std::size_t *count) {
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;
    int largest_child = i;

    *count += 7;
    if (left_child < n && vec[left_child] > vec[largest_child]) {
        largest_child = left_child;
        *count += 1;
    }

    if (right_child < n && vec[right_child] > vec[largest_child]) {
        largest_child = right_child;
        *count += 1;
    }

    if (largest_child != i) {
        *count += 9;
        std::swap(vec[i], vec[largest_child]);

        heapify(vec, n, largest_child, count);
    }
    *count += 19;
}

void heapSort(std::vector<int> &vec, std::size_t *count) {
    int n = int(vec.size());
    *count += 7;

    for (int i = n / 2 - 1; i >= 0; --i) {
        *count += 3;
        heapify(vec, n, i, count);
    }

    for (int i = n - 1; i > 0; i--) {
        *count += 12;

        std::swap(vec[0], vec[i]);

        heapify(vec, i, 0, count);
    }
}