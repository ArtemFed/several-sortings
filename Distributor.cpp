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

using func = void (*)(std::vector<int>, int);

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
        stableCountingSort(vec, max - min + 1, min, n);
        //        for (auto item : vec) {
        //            std::cout << item << " ";
        //        }
        //        std::cout << "]\n";
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

    void printTests(bool flag, const std::string &path) {
        std::map<std::string, std::ofstream> outStreams{};

        for (int i = 0; i < sortNames.size(); ++i) {
            std::ofstream file{path + sortNames[i] + ".csv"};
            file.close();
            outStreams[sortNames[i]].open(path + sortNames[i] + ".csv", std::ios::app);
        }

        std::string line;
        // Получаем пару { название сортировки, map с различными видами тестов }
        for (auto &sortItem : tests) {
            line = sortItem.first + "\n";
            if (flag) {
                outStreams[sortItem.first] << line;
            } else {
                std::cout << line;
            }

            // Получаем пару { название типа генерации, vector с различными возрастающими замерами }
            for (auto &typeItem : sortItem.second) {
                line = typeItem.first + "\n";
                if (flag) {
                    outStreams[sortItem.first] << line;
                } else {
                    std::cout << line;
                }
                for (auto &testItem : typeItem.second) {
                    line =  testItem + "\n";
                    // По имени сортировки берём
                    if (flag) {
                        outStreams[sortItem.first] << line;
                    } else {
                        std::cout << line;
                    }
                }
            }
            line = "\n";
            if (flag) {
                outStreams[sortItem.first] << line;
            } else {
                std::cout << line;
            }
        }

        for (auto &outStream : outStreams) {
            outStream.second.close();
        }
    }

    void clearTests() {
        tests.clear();
    }


    // map< sortName -> map<genName -> vec< time of test > > >
    std::map<std::string, std::map<std::string, std::vector<std::string>>> tests{};
};