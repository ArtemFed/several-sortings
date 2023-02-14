#include "Quick_Sort.h"

int partition(std::vector<int>& vec, int left, int right) {
    int piv = vec[right];
    int i = (left - 1);

    for (int j = left; j <= right - 1; j++) {
        if (vec[j] < piv) {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i + 1], vec[right]);
    return i + 1;
}

void quickSort(std::vector<int>& vec, int low, int high) {
    if (low < high) {
        int piv = partition(vec, low, high);

        quickSort(vec, low, piv - 1);
        quickSort(vec, piv + 1, high);
    }
}