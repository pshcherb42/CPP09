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

std::vector<int> fordJohnson(std::vector<int> nums) {
    size_t i;
    std::vector<Pair> pairs;
    std::vector<int> mainvec;
    std::vector<int> pendvec;
    int impar = -1;
    for (i = 0; i + 1 < nums.size(); i += 2) {
        int a = nums[i];
        int b = nums[i + 1];
        if ( a > b ) {
            pairs.push_back({a, b});
        }
        else 
            pairs.push_back({b, a});
    }

    if (nums.size() % 2 == 1) {
        impar = nums[i];
    }
    

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