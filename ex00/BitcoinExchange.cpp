#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {
    std::map<std::string, double> mymap;
	std::ifstream myfile;
	std::string str;
	std::string date;
    std::string rate;
	myfile.open("data.csv", std::ios::in);
	if (!myfile) {
		std::cout << "No such file is present\n";
        return;
	} 
    // read a particular record
    std::getline(myfile, str);
    while (std::getline(myfile, str)) {
        std::stringstream ss(str);
        
        if (std::getline(ss, date, ',')) {
            if (std::getline(ss, rate)) {
                double rateVal = std::strtod(rate.c_str(), NULL);
                mymap[date] = rateVal;
            }
        }
    }
    myfile.close();
}

BitcoinExchange::~BitcoinExchange() {}