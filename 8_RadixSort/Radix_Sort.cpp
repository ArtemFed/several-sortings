#include "Radix_Sort.h"

#include <vector>
#include <algorithm>

const int kK = 256;

int digit(int elem, int i) {
    if (static_cast<int>(sizeof(elem)) <= i) {
        return -1;
    }
    // Обращение по индексу к int
    return elem >> (8 * (3 - i)) & (255);
}

void msdRadixSort(std::vector<int>& vec_a, std::vector<int>& vec_help, int l, int r, int d) {
    // d - текущий разряд для сортировки

    if ((r - l) < 1024) {
        // Вызываем обычную сортирвку, если границы близки
        std::sort(vec_a.begin() + l, vec_a.begin() + r);
        return;
    }

    std::vector<int> cnt(kK + 2, 0);

    for (int i = l; i < r; ++i) {
        ++cnt[digit(vec_a[i], d) + 2];
    }

    for (int i = 0; i < kK + 1; ++i) {
        cnt[i + 1] += cnt[i];
    }

    for (int i = l; i < r; ++i) {
        vec_help[cnt[digit(vec_a[i], d) + 1]++] = vec_a[i];
    }

    for (int i = l; i < r; ++i) {
        vec_a[i] = vec_help[i - l];
    }

    // Вызываем сортировки для значений с правильными границами и сдвигаем разряд на 1
    for (int i = 0; i < kK + 1; ++i) {
        if (cnt[i + 1] > cnt[i]) {
            msdRadixSort(vec_a, vec_help, l + cnt[i], l + cnt[i + 1], d + 1);
        }
    }
}
