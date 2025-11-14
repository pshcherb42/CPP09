#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <ctime>

void print_vector(std::vector<int>& num) {
    for (std::vector<int>::iterator it = num.begin(); it != num.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}



bool already_sorted(const std::vector<int>& num) {
    size_t count = 1;
    for (std::vector<int>::const_iterator it = num.begin(); (it + 1) != num.end(); ++it) {
        int a = *it;
        int b = *(it + 1);
        if (a < b) {
            count++;
        }
    }
    if (count == num.size()) {
        return 1;
    }
    return 0;
}

void build_main_and_pend(std::vector<int>& numbers, std::vector<int>& main_seq, std::vector<int>& pend, size_t block_len) {
    size_t n = numbers.size();
    main_seq.clear();
    (void)pend.clear();
    
    // push al main las sequencias b1 y a1
    size_t i = 0;
    // we pushed first two elements in main
    while (i < block_len * 2) {
        main_seq.push_back(numbers[i]);
        i++;
    }
    
    // i now is at the beningin of the b2 block
    // on the last(first here, the 4th one in the example) recursion it doesnt enter the loop whcih is perfecto
    while (i + block_len < n) {
            //std::cout << i << "\n";
            size_t b_block_start = i;
            size_t a_block_start = i + block_len;
            // insertar bloque b en pend y bloque a en main
            for (size_t k = 0; k < block_len && b_block_start + k < n; ++k) {
                pend.push_back(numbers[b_block_start + k]);
            }
            for (size_t k = 0; k < block_len && a_block_start + k < n; ++k) {
                main_seq.push_back(numbers[a_block_start + k]);
            }
           i += 2 * block_len;
        }
    std::cout << "main: ";
    print_vector(main_seq);
    std::cout << "\n" << "pend: ";
    print_vector(pend);
    std::cout << "\n";
}

void sort_vector(std::vector<int>& numbers, size_t recursion_lvl) {
    size_t n = numbers.size();
    if ((recursion_lvl * 2) >= n) return;
    if (recursion_lvl == 1) {
        for (size_t i = 0; i + 1 < numbers.size(); i += 2) {
            if (numbers[i] > numbers[i + 1]) {
                std::swap(numbers[i], numbers[i + 1]);
            }
        }
    }
    size_t block_len = std::pow(2, recursion_lvl - 1);
    if (block_len * 2 > n) {
        //std::cout << "fin de la recursion\n";
        return ;
    }
    if (recursion_lvl > 1) {
        for (size_t i = 0; i + block_len < n; i += 2 * block_len) {
            //std::cout << i << "\n";
            size_t first_block_start = i;
            size_t second_block_start = i + block_len;
            if (second_block_start + block_len > n) continue;
            int first_max = numbers[i + block_len - 1];
            int second_max = numbers[second_block_start + block_len - 1];
            if (first_max > second_max) {
                for (size_t k = 0; k < block_len; ++k) {
                    std::swap (numbers[first_block_start + k], numbers[second_block_start + k]);
                }
            }
        }
    }
    sort_vector(numbers, recursion_lvl + 1);
    std::vector<int> main_seq, pend;
    build_main_and_pend(numbers, main_seq, pend, block_len);
    //insert_pend_using_jacobsthal(main_seq, pend);
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
    if (already_sorted(numbers)) {
        std::cerr << "Error: numbers are already sorted\n";
        return 1;
    }
    clock_t before = clock();   
    sort_vector(numbers, 1);
    clock_t after = clock() - before;
    std::cout << "duration:" << (float)after / CLOCKS_PER_SEC << std::endl;
}