#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

struct Pair {
    int larger;
    int smaller;
};

void printVector(const std::vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i < v.size() - 1) std::cout << " ";
    }
    std::cout << std::endl;
}



int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error: no arguments\n";
        return 1;
    }
    
    std::set<int> seen;
    std::vector<int> numbers;

    for (int i = 1; i < argc; ++i) {
        int num = std::stoi(argv[i]);
        if (num < 0) {
            std::cerr << "Error: negative numbers\n";
            return 1;
        }
        if (!seen.insert(num).second) {
            std::cerr << "Error: duplicate number\n";
            return 1;
        }
        numbers.push_back(num);
    }
}