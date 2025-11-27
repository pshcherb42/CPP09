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

int binary_search(std::vector<int> stack, int needle, int low, int high) {
	while (low < high) {
		int mid = low + (high - low) / 2;
		if (comp(stack[mid], needle)) // stack[mid] < needle
			low = mid + 1;
		else
			high = mid;
	}
	return low;
}

long _jacobsthal_number(long n) { return round((pow(2, n + 1) + pow(-1, n)) / 3); }

void insert_pend_using_jacobsthal(std::vector<int>& main_seq, std::vector<int>& pend, int block_len) {
	if (pend.empty()) return;
	int curr_jac = 3;
	size_t idx;
	int loc;
	std::vector<int> max_values;
	std::vector<size_t> indices;
	for (size_t i = block_len - 1; i < main_seq.size(); i += block_len) {
		max_values.push_back(main_seq[i]);
		indices.push_back(i);
	}
	/*std::cout << "max_values: ";
	print_vector(max_values);
	std::cout << "indices: ";
	print_vector(indices);*/
	while(!pend.empty()) {
		idx = _jacobsthal_number(curr_jac) - _jacobsthal_number(curr_jac - 1);
		//std::cout << "idx: " << idx << "\n";
		if (idx * block_len > pend.size()) {
			idx = _jacobsthal_number(curr_jac - 1) - _jacobsthal_number(curr_jac - 2);
			//std::cout << "new index: " << idx << "\n";
		} 
		idx = std::min(idx, pend.size() / block_len);
		while (idx) {
			//std::cout << "idx dentro de loop: " << idx << std::endl;
			loc = binary_search(max_values, pend[block_len * idx - 1], 0, static_cast<int>(max_values.size()));
			//std::cout << "pend[block_len * idx - 1]: "<< pend[block_len * idx - 1] << "\n";
			//std::cout << "loc: " << loc << "\n";
			std::vector<int> block_to_insert(pend.begin() + block_len * (idx - 1), pend.begin() + block_len * idx);
			/*std::cout << "block_to_insert: ";
			print_vector(block_to_insert);*/
			if (comp(pend[block_len * idx - 1], max_values[0])) { // pend[block_len * idx - 1] < max_values[0]
				main_seq.insert(main_seq.begin(), block_to_insert.begin(), block_to_insert.end());
			} else {
				size_t insert_pos = indices[loc - 1];
				//std::cout << "insert_pos: " << insert_pos << "\n";
				//std::cout << "posicion de insercion: " << main_seq[insert_pos + 1] << "\n";
				main_seq.insert(main_seq.begin() + insert_pos + 1, block_to_insert.begin(), block_to_insert.end());
				/*std::cout << "main_seq dentro de loop: ";
				print_vector(main_seq);*/
			}
			pend.erase(pend.begin() + block_len * (idx - 1), pend.begin() + block_len * idx);
			/*std::cout << "pend dentro de loop: ";
			print_vector(pend);*/
			max_values.clear();
			indices.clear();
			for (size_t i = block_len - 1; i < main_seq.size(); i += block_len) {
				max_values.push_back(main_seq[i]);
				indices.push_back(i);
			}
			/*std::cout << "max_values dentro de loop: ";
			print_vector(max_values);
			std::cout << "indices dentro de loop: ";
			print_vector(indices);*/
			idx--;
		}
		curr_jac++;
	}
}

void build_main_and_pend(std::vector<int>& numbers, std::vector<int>& main_seq, std::vector<int>& pend, size_t block_len) {
	size_t n = numbers.size();
	std::vector<int> non_participating;
	main_seq.clear();
	pend.clear();
	size_t i = 0;
	/*std::cout << "numbers: ";
	print_vector(numbers);*/
	while (i < block_len * 2) {
		main_seq.push_back(numbers[i]);
		i++;
	}
	if (i + block_len > n) {
		while(i < n) {
			non_participating.push_back(numbers[i]);
			i++;
		}
	}
	while (i + block_len <= n) {
		size_t b_block_start = i;
		size_t a_block_start = i + block_len;
		for (size_t k = 0; k < block_len && b_block_start + k < n; ++k) {
			pend.push_back(numbers[b_block_start + k]);
		}
		if (a_block_start + block_len > n) {	
			break;
		}
		for (size_t k = 0; k < block_len && a_block_start + k < n; ++k) {
			main_seq.push_back(numbers[a_block_start + k]);
		}
		i += 2 * block_len;
	}
	i += block_len;
	if (i < n) {
		while(i < n) {
			non_participating.push_back(numbers[i]);
			i++;
		}
	}
	/*std::cout << "main: ";
	print_vector(main_seq);
	std::cout << "pend: ";
	print_vector(pend);
	std::cout << "non aticipating: ";
	print_vector(non_participating);*/
	insert_pend_using_jacobsthal(main_seq, pend, block_len);
	if (!non_participating.empty()) {
		for (size_t i = 0; i != non_participating.size(); i++)
			main_seq.push_back(non_participating[i]);
	}
	/*std::cout << "main_seq after insertion: ";
	print_vector(main_seq);
	std::cout << "pend after insertion: ";
	print_vector(pend);*/
}

void sort_vector(std::vector<int>& numbers, size_t recursion_lvl) {
	size_t n = numbers.size();
	if ((recursion_lvl * 2) >= n) return;
	if (recursion_lvl == 1) {
		for (size_t i = 0; i + 1 < numbers.size(); i += 2) {
			if (comp(numbers[i + 1], numbers[i])) { //if (numbers[i] > numbers[i + 1])
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
			if (comp(second_max, first_max)) { //if (first_max > second_max)
				for (size_t k = 0; k < block_len; ++k) {
					std::swap (numbers[first_block_start + k], numbers[second_block_start + k]);
				}
			}
		}
	}
	sort_vector(numbers, recursion_lvl + 1);
	std::vector<int> main_seq, pend;
	build_main_and_pend(numbers, main_seq, pend, block_len);
	numbers = main_seq;
	//insert_pend_using_jacobsthal(main_seq, pend);
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
	//clock_t before = clock();   
	sort_vector(numbers, 1);
	std::cout << "Number of comparisons: " << nbr_of_comps << std::endl;
	for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << numbers[i];
        if (i < numbers.size() - 1) std::cout << " ";
    }
    std::cout << std::endl;
	//clock_t after = clock() - before;
	//std::cout << "duration:" << (float)after / CLOCKS_PER_SEC << std::endl;
}