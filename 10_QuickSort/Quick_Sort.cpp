#include "Quick_Sort.h"

int partition(std::vector<int> &vec, int left, int right, std::size_t *count) {
    // Первый опорный
    int piv = vec[right];
    int i = (left - 1);
    for (int j = left; j <= right - 1; j++) {
        if (vec[j] < piv) {
            ++i;
            std::swap(vec[i], vec[j]);
            *count += 20;
        }
        *count += 8;
    }
    *count += 18;
    std::swap(vec[i + 1], vec[right]);
    return i + 1;
}

void quickSort(std::vector<int> &vec, int left, int right, std::size_t *count) {
    *count += 1;
    if (left >= right) {
        return;
    }
    int piv = partition(vec, left, right, count);

    *count += 3;
    quickSort(vec, left, piv - 1, count);
    quickSort(vec, piv + 1, right, count);
}