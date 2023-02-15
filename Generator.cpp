#include <cstdlib>
#include <ctime>
#include <ostream>
#include <vector>

class Generator {
public:
    static void randomVectorGeneratorEasy(std::vector<int> &vec, int n) {
        srand(std::time(nullptr));
        for (int i = 0; i < n; ++i) {
            vec[i] = rand() % 6;
        }
    }

    static void randomVectorGeneratorHardcore(std::vector<int> &vec, int n) {
        srand(std::time(nullptr));
        for (int i = 0; i < n; ++i) {
            vec[i] = rand() % 1000;
        }
    }

    static void descendingOrderVectorGenerator(std::vector<int> &vec, int n) {
        int current = n;
        for (int i = 0; i < n; ++i) {
            vec[i] = current--;
        }
    }

    static void nearlySortedVectorGenerator(std::vector<int> &vec, int n) {
        int current = 0;
        for (int i = 0; i < n; ++i) {
            vec[i] = current++;
        }
        for (int i = 0; i < int(n * 0.2 + 1); ++i) {
            std::swap(vec[rand() % n], vec[rand() % n]);
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