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
#include <ostream>
#include <string>
#include <unordered_map>

using func = void (*)(std::vector<int> , int);

class Distributor {
    static void adapterSelectionSort(std::vector<int> vec, int n) {
        selectionSort(vec, n);
    }

    static void adapterBubbleSort(std::vector<int> vec, int n) {
        bubbleSort(vec, n);
    }

    static void adapterBubbleIversonOneSort(std::vector<int> vec, int n) {
        bubbleSortIversonOne(vec, n);
    }

    static void adapterBubbleIversonTwoSort(std::vector<int> vec, int n) {
        bubbleSortIversonTwo(vec, n);
    }

    static void adapterInsertionSort(std::vector<int> vec, int n) {
        insertionSort(vec.begin(), vec.end());
    }

    static void adapterInsertionBinarySort(std::vector<int> vec, int n) {
        insertionBinarySort(vec);
    }

    static void adapterCountingSort(std::vector<int> vec, int n) {
        if (n <= 1) {
            return;
        }
        int max = INT16_MIN, min = INT16_MAX;
        for (int i = 0; i < n; ++i) {
            max = std::max(max, vec[i]);
            min = std::min(min, vec[i]);
        }
        countingSort(vec, min, max);
    }

    static void adapterRadixSort(std::vector<int> vec, int n) {
        std::vector<int> vec_tmp(n);
        msdRadixSort(vec, vec_tmp, 0, n, 0);
    }

    static void adapterMergeSort(std::vector<int> vec, int n) {
        std::vector<int> vectorTemp(n);
        mergeSort(vec, vectorTemp, 0, n - 1);
    }

    static void adapterQuickSort(std::vector<int> vec, int n) {
        quickSort(vec, 0, n - 1);
    }

    static void adapterHeapSort(std::vector<int> vec, int n) {
        heapSort(vec);
    }

    static void adapterShellSort(std::vector<int> vec, int n) {
        shellSort(vec, n);
    }

    static void adapterShellCiurSort(std::vector<int> vec, int n) {
        shellSortCiur(vec, n);
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

        info.emplace_back("Selection");
        info.emplace_back("Bubble");
        info.emplace_back("BubbleIv1");
        info.emplace_back("BubbleIv2");
        info.emplace_back("Insertion");
        info.emplace_back("InsertionBinary");
        info.emplace_back("Counting");
        info.emplace_back("Radix");
        info.emplace_back("Merge");
        info.emplace_back("Quick");
        info.emplace_back("Heap");
        info.emplace_back("Shell");
        info.emplace_back("ShellCiur");
    }

    std::unordered_map<std::string, func> map = std::unordered_map<std::string, func>();
    std::vector<std::string> info = std::vector<std::string>();

public:
    Distributor() {
        initializeMap();
    }

    explicit Distributor(const std::unordered_map<std::string, func> &map) : map(map) {
    }

    func getFunc(const std::string &key) {
        return map[key];
    }

    bool containsKey(const std::string &key) {
        return map.find(key) != map.end();
    }

    friend std::ostream &operator<<(std::ostream &_stream, Distributor const &dist) {
        for (const auto& key : dist.info) {
            _stream << " - <" << key << ">" << std::endl;
        }
        return _stream;
    }

    std::vector<std::string> getNames() const {
        return info;
    }
};