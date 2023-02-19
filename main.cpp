#include <chrono>
#include <ctime>
#include <iostream>
#include <map>
#include <vector>

#include "Distributor.cpp"
#include "Generator.cpp"

#define COUNT_OF_REPETITIONS 10
#define COUNT_OF_GENERATORS 4
#define ALL true

void testOneSort(size_t(sortingFunc)(std::vector<int> &, int), int step1 = 50, int step2 = 100, int mode = 1) {
    std::string funcName, genName;

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
        Generator::printVec(vec, std::cout);

        for (int i = 0; i < COUNT_OF_REPETITIONS; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            sortingFunc(vec, current_size);
            auto diff = std::chrono::high_resolution_clock::now() - start;
            sumOfTimes += std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
        }

        Generator::printVec(vec, std::cout);

        std::cout << sumOfTimes / COUNT_OF_REPETITIONS << "\n";

        std::cout << "\n";
    }

    for (int current_size = step2; current_size < 4100; current_size += 100) {
        std::vector<int> vector;
        vector.resize(current_size);
    }
}

void requestGetter() {
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
            testOneSort(distributor.getFunc(line), 50, 100, 2);
        } else {
            continue;
        }
    }
}

void testAllSorts(std::vector<int> &vec,
                  const int currentSize,
                  const std::vector<std::string> &vecOfSortsNames,
                  Distributor &distributor) {

    std::string genName;
    uint64_t sumOfTimes = 0;
    size_t countOfOperations = 0;

    for (int mode = 1; mode <= COUNT_OF_GENERATORS; mode++) {
        // Генерирую случайный вектор выбранным генератором
        switch (mode) {
            case 2:
                Generator::randOrderGeneratorHard(vec, currentSize);
                genName = "hard";
                break;
            case 3:
                Generator::nearlySortedGenerator(vec, currentSize, int(currentSize * 0.01 + 1));
                genName = "near";
                break;
            case 4:
                Generator::descendingOrderGenerator(vec, currentSize);
                genName = "desc";
                break;
            default:
                Generator::randOrderGeneratorMedium(vec, currentSize);
                genName = "medm";
        }

        // Вызываем все сортировки для тестирования на одном и том же векторе
        for (int ind = 0; ind < vecOfSortsNames.size(); ++ind) {
            const auto sortName = &vecOfSortsNames[ind];

            if (distributor.containsKey(*sortName)) {
                sumOfTimes = 0;
                std::vector<int> tmpVec1(vec.begin(), vec.end());

                countOfOperations = (distributor.getFunc(*sortName))(tmpVec1, currentSize);
                for (int j = 0; j < COUNT_OF_REPETITIONS; ++j) {

                    std::vector<int> tmpVec(vec.begin(), vec.end());

                    auto start = std::chrono::high_resolution_clock::now();
                    // Вызываю функцию сортировки из map
                    (distributor.getFunc(*sortName))(tmpVec, currentSize);
                    auto diff = std::chrono::high_resolution_clock::now() - start;

                    sumOfTimes += std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
                }
                distributor.tests[*sortName][genName].emplace_back(
                        std::to_string(currentSize) + ";" + std::to_string(sumOfTimes / COUNT_OF_REPETITIONS) + ";" + std::to_string(countOfOperations));
            }
        }
    }
}

void callAllSorts() {
    Distributor distributor = Distributor();

    std::vector<std::string> vecOfSortsNames = distributor.getNames();

    std::map<std::string, std::ofstream> outStreams{};


    int step1 = 50;
    for (int currentSize = step1; currentSize <= 300; currentSize += 50) {
        std::vector<int> vec(currentSize);

        testAllSorts(vec, currentSize, vecOfSortsNames, distributor);
    }

    distributor.printTests(300, R"(..\tests\size300\)");


    std::cout << "==========================================\n";

    distributor.clearTests();

    int step2 = 100;
    for (int currentSize = step2; currentSize <= 4100; currentSize += 100) {
        std::vector<int> vec(currentSize);

        testAllSorts(vec, currentSize, vecOfSortsNames, distributor);
    }

    distributor.printTests(4100, R"(..\tests\size4100\)");
}

int main() {

    if (ALL) {
        callAllSorts();
    } else {
        requestGetter();
    }

    return 0;
}
