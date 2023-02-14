#include "Heap_Sort.h"

void heapify(std::vector<int> &vec, int n, int i) {
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;
    int largest_child = i;

    if (left_child < n && vec[left_child] > vec[largest_child]) {
        largest_child = left_child;
    }

    if (right_child < n && vec[right_child] > vec[largest_child]) {
        largest_child = right_child;
    }

    if (largest_child != i) {
        std::swap(vec[i], vec[largest_child]);

        heapify(vec, n, largest_child);
    }
}

void heapSort(std::vector<int> &vec) {
    int n = int(vec.size());

    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(vec, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        std::swap(vec[0], vec[i]);

        heapify(vec, i, 0);
    }
}