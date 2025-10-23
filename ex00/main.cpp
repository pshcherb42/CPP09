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
		std::string date;
		std::string amount;
		std::getline(ss, date, '|');
		std::getline(ss, amount);
		size_t start = amount.find_first_not_of(" \t");
		size_t end = amount.find_last_not_of(" \t");
		if (start != std::string::npos) {
			amount = amount.substr(start, end - start + 1);
		}
		size_t start_d = date.find_first_not_of(" \t");
		size_t end_d = date.find_last_not_of(" \t");
		if (start_d != std::string::npos) {
			date = date.substr(start_d, end_d - start_d + 1);
		}
		try {
			es_fecha_valida(date);
			
			// Valida amount ANTES de pasarlo a getRate
			double amountVal = std::stod(amount);
			if (amountVal < 0 || amountVal > 2147483647)  // Investiga límite del proyecto
				throw std::runtime_error("Invalid amount");
			
			m.getRate(date, amount);
		} catch (std::exception& e) {
				std::cout << "Error: " << e.what() << std::endl;
		}
				
	}
	myfile.close();
}