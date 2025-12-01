#include <string>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cerrno>
#include <climits>
#include <cmath>


static int nbr_of_comps = 0;

template <typename T> 
void print_vector(std::vector<T>& num) {
	for (typename std::vector<T>::iterator it = num.begin(); it != num.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << '\n';
}

std::vector<int> compute_t_vector(size_t max_k) { 
	std::vector<int> t;
	t.push_back(1); // t1 = 1
	for (size_t k = 2; k <= max_k; ++k) {
		int tk = (std::pow(2, k + 1) + std::pow(-1, k)) / 3;
		t.push_back(tk);
	}

	return t;
}



bool comp(int a, int b) {
    nbr_of_comps++;
    return a < b;
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

void merge_insertion_sort(std::vector<int>& arr) {
	if (arr.size() <= 1) return;

	size_t mid = arr.size() / 2;
	std::vector<int> left(arr.begin(), arr.begin() + mid);
	std::vector<int> right(arr.begin() + mid, arr.end());

	
	merge_insertion_sort(left);
    merge_insertion_sort(right);

	size_t i = 0, j = 0, k = 0;
	while (i < left.size() && j < right.size()) {
		if (left[i] < right[j]) {
			arr[k++] = left[i++];
		} else
			arr[k++] = right[j++];
	}
	while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}

void binary_insert(std::vector<int>& main_chain, int value) {
	std::vector<int>::iterator pos = std::lower_bound(main_chain.begin(), main_chain.end(), value, comp);
	main_chain.insert(pos, value);
}

void insert_b_into_main_chain(std::vector<int>& main_chain, std::vector<int>& smaller_numbers, int odd_element) {

	if (odd_element != -1) {
		binary_insert(main_chain, odd_element);
	}

	if (!smaller_numbers.empty()) {
        binary_insert(main_chain, smaller_numbers[0]);
		
    }
	
	size_t max_k = log2(smaller_numbers.size()) + 2; // tk depende del numero anterior y crece exponencialmente y aadimos uno por safety reasons
	std::vector<int> t = compute_t_vector(max_k);
	

	for (size_t k = 1; k < t.size(); k++) {
		int tk = t[k];
		int tk_1 = t[k - 1];
		for (int j = tk; j > tk_1; --j) {
			if (j - 1 < static_cast<int>(smaller_numbers.size())) {
				binary_insert(main_chain, smaller_numbers[j - 1]);
			}
		}
	}
	
}

std::vector<int> sort_vector(std::vector<int>& numbers) {
	size_t n = numbers.size();
	std::vector<int> larger_numbers;
	std::vector<int> smaller_numbers;
	int odd_element = -1;
	
    for (size_t i = 0; i + 1 < n; i += 2) {
		nbr_of_comps++;
        larger_numbers.push_back(std::max(numbers[i], numbers[i + 1]));
		smaller_numbers.push_back(std::min(numbers[i], numbers[i + 1]));
    }

	if (n % 2 == 1) {
        odd_element = numbers[n - 1];
    }

	
	merge_insertion_sort(larger_numbers);
	
	insert_b_into_main_chain(larger_numbers, smaller_numbers, odd_element);

	return larger_numbers;
}

int main(int argc, char** argv) {
	nbr_of_comps = 0;
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
	std::vector<int> sorted_numbers  =  sort_vector(numbers);
	std::cout << "Number of comparisons: " << nbr_of_comps << std::endl;
	std::cout << "After: ";
	for (size_t i = 0; i < sorted_numbers.size(); ++i) {
		std::cout << sorted_numbers[i];
		if (i < sorted_numbers.size() - 1) std::cout << " ";
	}
	std::cout << std::endl;
}