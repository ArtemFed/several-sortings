// АиСД-2, 2023, задание 5
// Федоров Артём Олегович БПИ217
// Clion для C++ и VS Code для python (.ipynb)
// Сделано: всё

#include <chrono>
#include <ctime>
#include <iostream>
#include <map>
#include <vector>

#include "Distributor.cpp"
#include "Generator.cpp"

#define COUNT_OF_REPETITIONS 8
#define COUNT_OF_GENERATIONS 3
#define COUNT_OF_GENERATORS 4

/**
 * Метод для тестирования одной сортировки с выьранным генератором (не используется)
 * @param sortingFunc Функция
 * @param step1 Шаг для первого генератора
 * @param step2 Шаг для второго генератора
 * @param mode Мод генерации
 */
void testOneSort(size_t(sortingFunc)(std::vector<int> &, int), int step1 = 50, int step2 = 100, int mode = 1) {
    std::string funcName, genName;

    for (int current_size = step1; current_size <= 300; current_size += 50) {
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

    for (int current_size = step2; current_size <= 4100; current_size += 100) {
        std::vector<int> vector;
        vector.resize(current_size);
    }
}


/**
 * Метод для тестирования одной сортировки с проверкой массива из файла и выводом результата в файл
 * @param sortingFunc Функция для проверки
 */
void testOneSortFile(size_t(sortingFunc)(std::vector<int> &, int)) {
    std::string funcName, genName;

    std::vector<int> vec = Generator::getVecFromFile("../input.txt");
    uint64_t sumOfTimes = 0;

    Generator::printVec(vec, std::cout);
    std::vector<int> tmpVec(vec.size());

    for (int i = 0; i < COUNT_OF_REPETITIONS; ++i) {
        std::copy(vec.begin(), vec.end(), tmpVec.begin());

        auto start = std::chrono::high_resolution_clock::now();
        sortingFunc(tmpVec, int(vec.size()));
        auto diff = std::chrono::high_resolution_clock::now() - start;
        sumOfTimes += std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
    }

    std::ofstream file{"../output.txt"};

    Generator::printVec(tmpVec, file);
    Generator::printVec(tmpVec, std::cout);

    file.close();

    std::cout << sumOfTimes / COUNT_OF_REPETITIONS << "\n";
}


/**
 * Распределитель по запросам (вызывает выбранную сортировку)
 */
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
            // testOneSort(distributor.getFunc(line));
            testOneSortFile(distributor.getFunc(line));
        } else {
            continue;
        }
    }
}


/**
 * Метод для тестирования всех сортировок со всеми генераторами по несколько раз
 * @param vec Пустой вектор заданного размера
 * @param currentSize Заданный размер
 * @param vecOfSortsNames Вектор имён всех сортировок для вызова
 * @param distributor Распределитель
 */
void testAllSorts(std::vector<int> &vec,
                  const int currentSize,
                  const std::vector<std::string> &vecOfSortsNames,
                  Distributor &distributor) {

    uint64_t sumOfTimes = 0;
    size_t countOfOperations = 0;

    for (int mode = 1; mode <= COUNT_OF_GENERATORS; mode++) {
        // name -> map<type, sum of times>
        std::map<std::string, std::map<std::string, std::pair<uint64_t, size_t>>> mapOfTimes{};
        for (int rep = 0; rep < COUNT_OF_GENERATIONS; ++rep) {
            std::string type;
            // Генерирую случайный вектор выбранным генератором
            switch (mode) {
                case 2:
                    Generator::randOrderGeneratorHard(vec, currentSize);
                    type = "hard";
                    break;
                case 3:
                    Generator::nearlySortedGenerator(vec, currentSize, int(currentSize * 0.01 + 1));
                    type = "near";
                    break;
                case 4:
                    Generator::descendingOrderGenerator(vec, currentSize);
                    type = "desc";
                    break;
                default:
                    Generator::randOrderGeneratorMedium(vec, currentSize);
                    type = "medm";
            }

            // Вызываем все сортировки для тестирования на одном и том же векторе
            for (const auto &sortName : vecOfSortsNames) {

                if (distributor.containsKey(sortName)) {
                    sumOfTimes = 0;
                    std::vector<int> tmpVec1(vec.begin(), vec.end());

                    countOfOperations = (distributor.getFunc(sortName))(tmpVec1, currentSize);
                    for (int j = 0; j < COUNT_OF_REPETITIONS; ++j) {

                        std::vector<int> tmpVec(vec.begin(), vec.end());

                        auto start = std::chrono::high_resolution_clock::now();
                        // Вызываю функцию сортировки из map
                        (distributor.getFunc(sortName))(tmpVec, currentSize);
                        auto diff = std::chrono::high_resolution_clock::now() - start;

                        sumOfTimes += std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
                    }
                    mapOfTimes[sortName][type].first += sumOfTimes / COUNT_OF_REPETITIONS;
                    mapOfTimes[sortName][type].second = countOfOperations;
                }
            }
        }

        // Сохранение всех результатов тестов в map map'ов
        for (const auto &mapOfSortTypes : mapOfTimes) {
            for (const auto &testTime : mapOfSortTypes.second) {
                distributor.tests[mapOfSortTypes.first][testTime.first].emplace_back(
                        std::to_string(currentSize) + ";" +
                        std::to_string(testTime.second.first / COUNT_OF_GENERATIONS) + ";" +
                        std::to_string(testTime.second.second));
            }
        }
    }
}


/**
 * Метод для вызова всех сортировок на каждой итерации двух запусков (50 -> 300 и 100 -> 4100)
 */
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


/**
 * Точка входа в программу
 * @return Результат работы программы
 */
int main() {

    std::cout << "Test one sort  - 1 \nTest all sorts - else\n";
    std::string line;
    std::cin >> line;

    if (line != "1") {
        // Среднее время выполнения 10-15 минут
        auto start = std::chrono::high_resolution_clock::now();
        callAllSorts();
        auto diff = std::chrono::high_resolution_clock::now() - start;
        std::cout << double(std::chrono::duration_cast<std::chrono::seconds>(diff).count()) / 60.0;
    } else {
        requestGetter();
    }

    return 0;
}
