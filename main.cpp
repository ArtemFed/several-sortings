#include <chrono>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <vector>

#include "Distributor.cpp"
#include "Generator.cpp"

#define COUNT_OF_REPETITIONS 50
#define SOLO false

void testAnySortOnesWithPrint(void(sortingFunc)(std::vector<int> &, int), int n, int mode) {
    std::vector<int> vec(n);

    switch (mode) {
        case 2:
            Generator::randOrderGeneratorHard(vec, n);
            break;
        case 3:
            Generator::nearlySortedGenerator(vec, n, int(n * 0.2 + 1));
            break;
        case 4:
            Generator::descendingOrderGenerator(vec, n);
            break;
        default:
            Generator::randOrderGeneratorMedium(vec, n);
    }

    std::flush(std::cout);

    Generator::printVec(vec, std::cout);

    sortingFunc(vec, n);
    Generator::printVec(vec, std::cout);
}

void testAnySort(void(sortingFunc)(std::vector<int>, int), int step1 = 50, int step2 = 100, int mode = 1) {
    for (int current_size = step1; current_size < 300; current_size += 50) {
        std::vector<int> vec(current_size);
        uint64_t sumOfTimes = 0;

        switch (mode) {
            case 2:
                Generator::randOrderGeneratorHard(vec, current_size);
                break;
            case 3:
                Generator::nearlySortedGenerator(vec, current_size,
                                                 int(current_size * 0.2 + 1));
                break;
            case 4:
                Generator::descendingOrderGenerator(vec, current_size);
                break;
            default:
                Generator::randOrderGeneratorMedium(vec, current_size);
        }
        //        Generator::printVec(vec, std::cout);

        for (int i = 0; i < COUNT_OF_REPETITIONS; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            sortingFunc(vec, current_size);
            auto diff = std::chrono::high_resolution_clock::now() - start;
            sumOfTimes += std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
        }

        std::cout << sumOfTimes / COUNT_OF_REPETITIONS << "\n";

        //        Generator::printVec(vec, std::cout);

        //        std::cout << "\n";
    }

    for (int current_size = step2; current_size < 4100; current_size += 100) {
        std::vector<int> vector;
        vector.resize(current_size);

    }
}

void testAnySortWithVec(void(sortingFunc)(std::vector<int>, int), int step1 = 50, int step2 = 100, int mode = 1) {
    for (int current_size = step1; current_size < 300; current_size += 50) {
        std::vector<int> vec(current_size);
        uint64_t sumOfTimes = 0;

        switch (mode) {
            case 2:
                Generator::randOrderGeneratorHard(vec, current_size);
                break;
            case 3:
                Generator::nearlySortedGenerator(vec, current_size,
                                                 int(current_size * 0.2 + 1));
                break;
            case 4:
                Generator::descendingOrderGenerator(vec, current_size);
                break;
            default:
                Generator::randOrderGeneratorMedium(vec, current_size);
        }
        //        Generator::printVec(vec, std::cout);

        for (int i = 0; i < COUNT_OF_REPETITIONS; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            sortingFunc(vec, current_size);
            auto diff = std::chrono::high_resolution_clock::now() - start;
            sumOfTimes += std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
        }

        std::cout << sumOfTimes / COUNT_OF_REPETITIONS << "\n";

        //        Generator::printVec(vec, std::cout);

        //        std::cout << "\n";
    }

    for (int current_size = step2; current_size < 4100; current_size += 100) {
        std::vector<int> vector;
        vector.resize(current_size);

    }
}

void restAPI() {
    Distributor distributor = Distributor();

    std::cout << "Available commands:\n";
    std::cout << distributor;
    std::cout << " - <end>\n";

    std::string line;
    for (;;) {
        std::cout << ">>";
        std::cin >> line;
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);

        if (line == "end") {
            break;
        }

        if (distributor.containsKey(line)) {
            //            testAnySortOnesWithPrint(distributor.getFunc(line), n);
            testAnySort(distributor.getFunc(line));
        } else {
            continue;
        }
    }
}

void callAllSorts() {
    Distributor distributor = Distributor();

    std::vector<std::string> vecOfNames = distributor.getNames();

    for (std::string& name : vecOfNames) {
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);

        if (distributor.containsKey(name)) {
            testAnySort(distributor.getFunc(name));
        }
    }
}

int main() {
    int n = 0;

    if (SOLO) {
        restAPI();
    } else {
        callAllSorts();
    }

    return 0;
}
