// АиСД-2, 2023, задание 5
// Федоров Артём Олегович БПИ217
// Clion для C++ и VS Code для python (.ipynb)
// Сделано: всё

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ostream>
#include <sstream>
#include <vector>

/**
 * Генератор массивов
 */
class Generator {
public:

    /**
     * Генератор массива с числами от 0 до 5
     * @param vec Массив
     * @param n Размер массива
     */
    static void randOrderGeneratorMedium(std::vector<int> &vec, int n) {
        srand(std::time(nullptr) + n);
        for (int i = 0; i < n; ++i) {
            vec[i] = rand() % 6;
        }
    }

    /**
     * Генератор массива с числами от 0 до 4001
     * @param vec Массив
    * @param n Размер массива
     */
    static void randOrderGeneratorHard(std::vector<int> &vec, int n) {
        srand(std::time(nullptr) + n);
        for (int i = 0; i < n; ++i) {
            vec[i] = rand() % 4001;
        }
    }

    /**
     * Почти отсортированный массив от 0 до n с случаными count перестоновок
     * @param vec Массив
    * @param n Размер массива
     */
    static void nearlySortedGenerator(std::vector<int> &vec, int n, int count) {
        srand(std::time(nullptr));
        for (int i = 0; i < n; ++i) {
            vec[i] = i;
        }
        for (int i = 0; i < count; ++i) {
            std::swap(vec[rand() % n], vec[rand() % n]);
        }
    }

    /**
     * Обратно отсортированный массив от n до 1
     * @param vec Массив
     * @param n Размер массива
     */
    static void descendingOrderGenerator(std::vector<int> &vec, int n) {
        for (int i = 0; i < n; ++i) {
            vec[i] = n - i;
        }
    }

    /**
     * Прочить вектор из файла по пути по строркам
     * @param filepath Путь к файлу от .exe
     * @return Массив инт
     */
    static std::vector<int> getVecFromFile(const std::string&filepath) {
        std::ifstream infile(filepath);
        std::vector<int> numbers;
        std::string line;

        while (std::getline(infile, line)) {
            std::stringstream ss(line);
            int number;

            while (ss >> number) {
                numbers.push_back(number);
            }
        }

        return numbers;
    }

    /**
     * Напечатать вектор в поток
     * @tparam T Тип вектора
     * @param vec Вектор
     * @param so Поток
     */
    template<typename T>
    static void printVec(std::vector<T> &vec, std::ostream &so) {
        so << " [ ";
        for (auto item : vec) {
            so << item << " ";
        }
        so << "]\n";
    }
};