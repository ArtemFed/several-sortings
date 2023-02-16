#include <cstdlib>
#include <ctime>
#include <ostream>
#include <vector>

class Generator {
public:
    static void randOrderGeneratorMedium(std::vector<int> &vec, int n) {
        srand(std::time(nullptr));
        for (int i = 0; i < n; ++i) {
            vec[i] = rand() % 6;
        }
    }

    static void randOrderGeneratorHard(std::vector<int> &vec, int n) {
        srand(std::time(nullptr));
        for (int i = 0; i < n; ++i) {
            vec[i] = rand() % 1000;
        }
    }

    static void nearlySortedGenerator(std::vector<int> &vec, int n, int count) {
        srand(std::time(nullptr));
        for (int i = 0; i < n; ++i) {
            vec[i] = i;
        }
        for (int i = 0; i < count; ++i) {
            std::swap(vec[rand() % n], vec[rand() % n]);
        }
    }

    static void descendingOrderGenerator(std::vector<int> &vec, int n) {
        for (int i = n - 1; i >= 0; --i) {
            vec[i] = i;
        }
    }

    template<typename T>
    static void printVec(std::vector<T> &vec, std::ostream &so) {
        so << " [ ";
        for (auto item : vec) {
            so << item << " ";
        }
        so << "]\n";
    }
};