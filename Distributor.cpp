#include "10_QuickSort/Quick_Sort.h"
#include "11_HeapSort/Heap_Sort.h"
#include "12-13_ShellSort/Shell_Sort.h"
#include "1_SelectionSort/Selection_Sort.h"
#include "2-4_BubbleSort/Bubble_Sort.h"
#include "5-6_InsertionSort/Insertion_Sort.h"
#include "7_CountingSort/Counting_Sort.h"
#include "8_RadixSort/Radix_Sort.h"
#include "9_MergeSort/Merge_Sort.h"
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <unordered_map>

using func = size_t (*)(std::vector<int>&, int);

class Distributor {
    static void isSorted(const std::vector<int> &vec, const std::string &name) {
        for (int i = 0; i < int(vec.size()) - 1; ++i) {
            if (vec[i] > vec[i + 1]) {
                throw std::runtime_error(name);
            }
        }
    }

    static size_t adapterSelectionSort(std::vector<int> &vec, int n) {
        size_t count = selectionSort(vec, n);
        //        isSorted(vec, "selectionSort");
        return count;
    }

    static size_t adapterBubbleSort(std::vector<int> &vec, int n) {
        size_t count = bubbleSort(vec, n);
        //        isSorted(vec, "bubbleSort");
        return count;
    }

    static size_t adapterBubbleIversonOneSort(std::vector<int> &vec, int n) {
        size_t count = bubbleSortIversonOne(vec, n);
        //        isSorted(vec, "bubbleSortIversonOne");
        return count;
    }

    static size_t adapterBubbleIversonTwoSort(std::vector<int> &vec, int n) {
        size_t count = bubbleSortIversonTwo(vec, n);
        //        isSorted(vec, "bubbleSortIversonTwo");
        return count;
    }

    static size_t adapterInsertionSort(std::vector<int> &vec, int n) {
        size_t count = insertionSort(vec.begin(), vec.end());
        //        isSorted(vec, "insertionSort");
        return count;
    }

    static size_t adapterInsertionBinarySort(std::vector<int> &vec, int n) {
        size_t count = 0;
        insertionBinarySort(vec, n, &count);
        //        isSorted(vec, "insertionBinarySort");
        return count;
    }

    static size_t adapterCountingSort(std::vector<int> &vec, int n) {
        if (n <= 1) {
            return 1;
        }
        int max = INT16_MIN, min = INT16_MAX, count = 1;
        for (int i = 0; i < n; ++i) {
            max = std::max(max, vec[i]);
            min = std::min(min, vec[i]);
            count += 11;
        }
        size_t countS = stableCountingSort(vec, max - min + 1, min, n) + count;
        //        isSorted(vec, "stableCountingSort");
        return countS;
    }

    static size_t adapterRadixSort(std::vector<int> &vec, int n) {
        size_t count = 0;
        std::vector<int> vec_tmp(n);
        msdRadixSort(vec, vec_tmp, 0, n, 0, &count);
        //        isSorted(vec, "msdRadixSort");
        return count;
    }

    static size_t adapterMergeSort(std::vector<int> &vec, int n) {
        size_t count = 0;
        std::vector<int> vectorTemp(n);
        mergeSort(vec, vectorTemp, 0, n - 1, &count);
        //        isSorted(vec, "mergeSort");
        return count;
    }

    static size_t adapterQuickSort(std::vector<int> &vec, int n) {
        size_t count = 0;
        quickSort(vec, 0, n - 1, &count);
        //        isSorted(vec, "quickSort");
        return count;
    }

    static size_t adapterHeapSort(std::vector<int> &vec, int n) {
        size_t count = 0;
        heapSort(vec, &count);
        //        isSorted(vec, "heapSort");
        return count;
    }

    static size_t adapterShellSort(std::vector<int> &vec, int n) {
        size_t count = shellSort(vec, n);
        //        isSorted(vec, "shellSort");
        return count;
    }

    static size_t adapterShellCiurSort(std::vector<int> &vec, int n) {
        size_t count = shellSortCiur(vec, n);
        //        isSorted(vec, "shellSortCiur");
        return count;
    }

    void initializeMap() {
        map["selection"] = adapterSelectionSort;
        map["bubble"] = adapterBubbleSort;
        map["bubbleiv1"] = adapterBubbleIversonOneSort;
        map["bubbleiv2"] = adapterBubbleIversonTwoSort;
        map["insertion"] = adapterInsertionSort;
        map["insertionbinary"] = adapterInsertionBinarySort;
        map["counting"] = adapterCountingSort;
        map["radix"] = adapterRadixSort;
        map["merge"] = adapterMergeSort;
        map["quick"] = adapterQuickSort;
        map["heap"] = adapterHeapSort;
        map["shell"] = adapterShellSort;
        map["shellciur"] = adapterShellCiurSort;

        sortNames = std::vector<std::string>();
        sortNames.reserve(map.size());
        for (auto const &item : map) {
            sortNames.emplace_back(item.first);
        }
    }

    std::unordered_map<std::string, func> map = std::unordered_map<std::string, func>();
    std::vector<std::string> sortNames;

public:
    Distributor() {
        initializeMap();
    }

    explicit Distributor(const std::unordered_map<std::string, func> &map) : map(map) {
        sortNames = std::vector<std::string>(map.size());
        for (auto const &item : map) {
            sortNames.push_back(item.first);
        }
    }

    func getFunc(const std::string &key) const {
        return map.at(key);
    }

    bool containsKey(const std::string &key) const {
        return map.find(key) != map.end();
    }

    friend std::ostream &operator<<(std::ostream &_stream, Distributor const &dist) {
        for (const auto &key : dist.sortNames) {
            _stream << " - <" << key << ">" << std::endl;
        }
        return _stream;
    }

    std::vector<std::string> getNames() const {
        return sortNames;
    }

    int getSize() const {
        return int(sortNames.size());
    }

    void printTests(int num, const std::string &path) {
        std::string line, fileName;
        // Получаем пару { название сортировки, map с различными видами тестов }
        for (auto &sortItem : tests) {

            // Получаем пару { название типа генерации, vector с различными возрастающими замерами }
            for (auto &typeItem : sortItem.second) {
                fileName = sortItem.first + "_" + typeItem.first + "_" + std::to_string(num);
                std::cout << fileName << "\n";

                std::ofstream file{path + fileName + ".csv"};
                file << "size;time;operations\n";

                for (auto &testItem : typeItem.second) {
                    file << testItem + "\n";
                }
                file << "\n";
                file.close();
            }
        }
    }

    void clearTests() {
        tests.clear();
    }


    // map< sortName -> map<genName -> vec< time of test > > >
    std::map<std::string, std::map<std::string, std::vector<std::string>>> tests{};
};
