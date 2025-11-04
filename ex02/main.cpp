#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

void print_vector(const std::vector<int>& num) {
    for (std::vector<int>::const_iterator it = num.begin(); it != num.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}

bool already_sorted(const std::vector<int>& num) {
    size_t count = 1;
    for (std::vector<int>::const_iterator it = num.begin(); (it + 1) != num.end(); ++it) {
        int a = *it;
        int b = *it + 1;
        if (a < b) {
            count++;
        }
    }
    if (count == num.size()) {
        return 1;
    }
    return 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error: no arguments\n";
        return 1;
    }
    if (argc == 2) {
        std::cerr << "Error: write more arguments\n";
        return 1;
    }
    
    std::set<int> seen;
    std::vector<int> numbers;

    for (int i = 1; i < argc; ++i) {
        char* endptr = NULL;
        errno = 0;
        long val = std::strtol(argv[i], &endptr, 10);
        if (*endptr != '\0') {
            std::cerr << "Error: non-digit character\n";
            return 1;
        }
        if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
            std::cerr << "Error: number out of range\n";
            return 1;
        }
        int num = static_cast<int>(val);
        
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
    print_vector(numbers);
    if (already_sorted(numbers)) {
        std::cerr << "Error: numbers are already sorted\n";
        return 1;
    }
}