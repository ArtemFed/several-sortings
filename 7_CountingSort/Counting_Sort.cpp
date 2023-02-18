#include "Counting_Sort.h"

#include <vector>

void countingSort(std::vector<int> &vec, int min, int max) {
    int k = max - min + 1;
    std::vector<int> vec_help(k, 0);
    for (int i : vec) {
        vec_help[i - min] += 1;
    }

    int it = 0;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < vec_help[i]; ++j) {
            vec[it++] = i + min;
        }
    }
}
//
//std::size_t stableCountingSort(std::vector<int> &array, int min, int max, int n) {
//    int k = max - min + 1;
//    std::size_t counter = 0;
//
//    int prefix_counting[k];
//    int temporary[n];
//    // i = 0
//    ++counter;
//    for (int i = 0; i < k; ++i) {
//        // 1 операция
//        prefix_counting[i] = 0;
//        // 1 операция выше и ещё 3 в цикле (< (1 операция) и ++i (2 операции))
//        counter += 4;
//    }
//    ++counter;// i = 0
//    for (int i = 0; i < n; ++i) {
//        // 2 операции
//        ++prefix_counting[array[i]];
//        // 1 операция
//        temporary[i] = array[i];
//        // ещё 3 операции в цикле
//        counter += 6;
//    }
//    ++counter;// i = 1
//    for (int i = 1; i < k; ++i) {
//        // 2 операции
//        prefix_counting[i] += prefix_counting[i - 1];
//        // 3 операции в цикле
//        counter += 5;
//    }
//    counter += 2;// i = n - 1
//    for (int i = n - 1; i >= 0; --i) {
//        // 2 операции (temporary[i]] - 1 и присваивание)
//        array[prefix_counting[temporary[i]] - 1] = temporary[i];
//        // 2 операции
//        --prefix_counting[temporary[i]];
//        // i >= 0 (1 операция) и --i
//        counter += 7;
//    }
//    return counter;
//}


std::size_t stableCountingSort(std::vector<int> &array, int help_size, int minimum, int n) {
    int prefix_count_array[help_size];
    int temporary[n];
    for (int i = 0; i < help_size; ++i) {
        prefix_count_array[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        // небольшое изменение в индексации, чтобы работало с отрицательными числами
        ++prefix_count_array[array[i] - minimum];
        temporary[i] = array[i];
    }

    for (int i = 1; i < help_size; ++i) {
        prefix_count_array[i] += prefix_count_array[i - 1];
    }

    for (int i = n - 1; i >= 0; --i) {
        array[prefix_count_array[temporary[i] - minimum] - 1] = temporary[i];
        --prefix_count_array[temporary[i] - minimum];
    }
}