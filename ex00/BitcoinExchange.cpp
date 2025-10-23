#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : _data(copy._data) {}//{std::cout << GREEN << "BitcoinExchange - Constructor copy called " << RESET << std::endl;}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange &autre) {(void)autre; return *this;}

BitcoinExchange::~BitcoinExchange() {}//{std::cout << RED << "BitcoinExchange - Destructor called " << RESET << std::endl;}

std::map<std::string, float> BitcoinExchange::getData()
{
	return _data;
}

void BitcoinExchange::setPair(const std::string& date, float value)
{
	_data[date] = value;
}

bool parsing_inputfile(std::string argv)
{
	std::ifstream fichier(argv.c_str());
	if (!fichier)
	{
		std::cerr << RED << "Error: could not open file." << RESET << std::endl;
		return 0;
	}

	std::string line;
	if (!std::getline(fichier, line))
	{
		std::cerr << RED << "Error: empty input file." << RESET << std::endl;
		fichier.close();
		return 0;
	}
	fichier.close();
	return 1;
}

bool parsing_line(std::string &line)
{
	// '|' pas a la bonne place, existe pas tt court, ou si > 1)
	size_t pos_separateur = line.find('|');
	if (pos_separateur != 11 || pos_separateur == std::string::npos || line.find('|', pos_separateur + 1) != std::string::npos)
	{
		std::cerr << RED << "Error: invalid line format (date | value)." << RESET << std::endl;
		return 0;
	}

	// format de la date
	size_t pos_tiret1 = line.find('-');
	size_t pos_tiret2 = line.find('-', pos_tiret1);
	// std::cout << pos_tiret1 << ", " << pos_tiret2 << std::endl;
	if (pos_tiret1 != 4 || pos_tiret2 != 4)
	{
		std::cerr << RED << "Error: invalid date format (YYYY-MM-DD)." << RESET << std::endl;
		return 0;
	}

	unsigned int year = atoi(line.substr(0, 4).c_str());
	if (year > 2025)
	{
		std::cerr << RED << "Error: invalid year. " << RESET << std::endl;
		return 0;
	}
	
	unsigned int month = atoi(line.substr(5, 6).c_str());
	if (month > 12)
	{
		std::cerr << RED << "Error: invalid month. " << RESET << std::endl;
		return 0;
	}

	unsigned int day = atoi(line.substr(8, 9).c_str());
	if (day > 31)
	{
		std::cerr << RED << "Error: invalid day. " << RESET << std::endl;
		return 0;
	}

	if (!atof(line.substr(13, line.length()).c_str()))
	{
		std::cerr << RED << "Error: wrong value. " << RESET << std::endl;
		return 0;
	}

	return 1;
}

void calcul(std::string argv)
{
	BitcoinExchange btc;
	std::ifstream fichier(argv.c_str());
	std::string line;
	std::getline(fichier, line);//passer la 1ere ligne (header)

	while (std::getline(fichier, line))
	{
		//ligne vide, on passe
        if (line.empty() || line.find_first_not_of(" \t\n\r") == std::string::npos)
			continue;

		std::cout << line << std::endl;
		if (parsing_line(line))
		{
			std::cout << GREEN << "ligne valide, stockage de date et value dans std::map" << RESET<< std::endl;
			std::string date = line.substr(0, 10).c_str();
			float value = atof(line.substr(13, line.length()).c_str());
			btc.setPair(date, value);
		}
	}
	fichier.close();
	print_map_classic(btc.getData());
}



void print_map_classic(const std::map<std::string, float>& _data)
{
    std::cout << YELLOW << "\n--- std::map _data ---" << RESET << std::endl;
    
	for (std::map<std::string, float>::const_iterator it = _data.begin(); it != _data.end(); ++it) 
        std::cout << "date: " << it->first << " | value: " << it->second << std::endl;
}