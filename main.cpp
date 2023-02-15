#include <ctime>
#include <iostream>
#include <vector>

#include "Generator.cpp"
#include "Distributor.cpp"

void testBubbleSort() {
    int current_size = 50;
    for (int i = 0; i < 5; ++i) {
        std::vector<int> vector;
        vector.resize(current_size);
        Generator::randomVectorGeneratorHardcore(vector, current_size);
        Generator::printVec(vector, std::cout);
        bubbleSort(vector, current_size);
        Generator::printVec(vector, std::cout);
        std::cout << "\n";
        current_size += 50;
    }

    current_size = 100;
    for (int i = 0; i < 40; ++i) {
        std::vector<int> vector;
        vector.resize(current_size);

        current_size += 100;
    }
}

static void testAnySort(void(sortingFunc)(std::vector<int> &, int), int n) {
    std::vector<int> vec(n);

    Generator::randomVectorGeneratorHardcore(vec, n);
    std::flush(std::cout);

    Generator::printVec(vec, std::cout);

    sortingFunc(vec, n);
    Generator::printVec(vec, std::cout);
}

int main() {
    int n = 10;
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
            testAnySort(distributor.getFunc(line), n);
        } else {
            continue;
        }
    }

    return 0;
}
