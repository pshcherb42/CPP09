#include "BitcoinExchange.hpp"
#define es_anio_bisiesto(y)  ((((y)%400)==0)||((((y)%4)==0)&&(((y)%100)!=0)))

BitcoinExchange::BitcoinExchange() {
    
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

void BitcoinExchange::getRate(std::string date, std::string amount) {
    double a = std::stod(amount);
    std::map<std::string, double>::const_iterator it = mymap.lower_bound(date);
    if (it != mymap.end() && it->first == date) {
        std::cout << it->first << " => " << amount << " = " << (it->second * a) << std::endl;
        return ;
    }
    if (it != mymap.begin()) {
        --it;
        std::cout << it->first << " => " << amount << " = " << (it->second * a) << std::endl;
        return ;
    }
    
    throw std::runtime_error("date too early");
}

BitcoinExchange::~BitcoinExchange() {}

bool es_fecha_valida(std::string fecha) {
    if (fecha.size() != 10 || fecha[4] != '-' || fecha[7] != '-') {
        throw std::runtime_error("Invalid date format");
    }
    std::string año, mes, dia;
    std::stringstream ss(fecha);
    std::getline(ss, año, '-');
    std::getline(ss, mes, '-');
    std::getline(ss, dia);
    int a = std::stoi(año);
    int m = std::stoi(mes);
    int d = std::stoi(dia);
    if (a > 2025)
        throw std::runtime_error("Invalid year format");
    if (m > 12 || m < 1)
        throw std::runtime_error("Invalid month format");
    if (d > 31 || d < 1)
        throw std::runtime_error("Invalid day format");
    return true;
}