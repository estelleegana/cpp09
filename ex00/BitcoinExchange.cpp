#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}//{std::cout << GREEN << "BitcoinExchange - Constructor (default) called " << RESET << std::endl;}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : _data(copy._data) {}//{std::cout << GREEN << "BitcoinExchange - Constructor copy called " << RESET << std::endl;}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange &autre) {(void)autre; return *this;}

BitcoinExchange::~BitcoinExchange() {}//{std::cout << RED << "BitcoinExchange - Destructor called " << RESET << std::endl;}

void BitcoinExchange::start(std::string argv)
{
	std::ifstream fichier(argv.c_str());
	std::string line;
	std::getline(fichier, line);
	if 
	if (line != "date | value")
		std::cerr << RED << "Error: no header \"date | value\" in input.txt file" << RESET<< std::endl;
	else
	{
		while(std::getline(fichier, line))
		{
			std::cout << line<< std::endl;
		} 
	}
	fichier.close();
}