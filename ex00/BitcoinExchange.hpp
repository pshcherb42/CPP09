#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>
#include <exception>

class BitcoinExchange {
    private:
        std::map<std::string, double> mymap;
    public :
        BitcoinExchange();
        ~BitcoinExchange();
        void getRate(std::string amount, std::string date);
};

bool es_fecha_valida(std::string fecha);