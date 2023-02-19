#ifndef HW1_INSERTION_SORT_H
#define HW1_INSERTION_SORT_H

#include <vector>
std::size_t insertionSort(std::vector<int>::iterator begin,
                   std::vector<int>::iterator end);

void insertionBinarySort(std::vector<int> &vec, std::size_t *count);

#endif//HW1_INSERTION_SORT_H
