#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
	
	if (argc != 2)
	{
		std::cout << "Use: ./programename filename.txt\n";
		return 1;
	}
	BitcoinExchange m;

	std::ifstream myfile;
	myfile.open(argv[1], std::ios::in);
	if (!myfile) {
		std::cout << "Error opening file\n";
		return 1;
	}
	std::string str;

	std::getline(myfile, str); 
	while (std::getline(myfile, str)) {
		//std::cout << str << std::endl;
		std::stringstream ss(str);
		std::tm tm = {};
		std::string word;
		ss >> word;
		
	}
	myfile.close();
}