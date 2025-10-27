#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(std::string csvfile)
{
	std::ifstream fichier_csv(csvfile.c_str());
	if (!fichier_csv)
		throw std::runtime_error(RED "Error: could not open database file." RESET);
	
	std::string line;
	if (!std::getline(fichier_csv, line))
	{
		fichier_csv.close();
		throw std::runtime_error(RED "Error: empty csv file."RESET);
	}

	std::getline(fichier_csv, line);
	while (std::getline(fichier_csv, line))
	{
		std::istringstream ss(line);
		std::string date;
		float rate;
		if (std::getline(ss, date, ',') && ss >> rate)
			_data[date] = rate;
	}
	fichier_csv.close();
	// print_map_classic();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : _data(copy._data) {}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange &autre) {(void)autre; return *this;}

BitcoinExchange::~BitcoinExchange() {}



void BitcoinExchange::rateXvalue(std::string argv)
{
	std::ifstream fichier_input(argv.c_str());
	if (!fichier_input)
		throw std::runtime_error(RED "Error: could not open input file." RESET);

	std::string line;
	if (!std::getline(fichier_input, line))
	{
		fichier_input.close();
		throw std::runtime_error(RED "Error: empty input file."RESET);
	}

	// std::getline(fichier_input, line);
	while (std::getline(fichier_input, line))
	{
		//ligne vide, on passe
		if (line.empty() || line.find_first_not_of(" \t\n\r") == std::string::npos)
			continue;

		if (parsing_line(line))
		{
			std::string date = line.substr(0, 10);
			float value = atof(line.substr(13, line.length()).c_str());
			float rate = getExchangeRate(date.c_str());
			if (rate < 0)
				throw std::runtime_error(RED "Error: no exchange rate at this date."RESET);
			else
				std::cout << date << " => " << value << " = " << rate * value << std::endl;
		}
	}
} 

float BitcoinExchange::getExchangeRate(const std::string &date) const
{
    std::map<std::string, float>::const_iterator it = _data.find(date);
    
    if (it != _data.end()) {
        return it->second;//date exacte
	}
    
	it = _data.lower_bound(date);
	//pas de date anterieur
    if (it == _data.begin())
        throw std::runtime_error("Error: no earlier date in database");
    
	//pas de date exacte, on prend la précédente
    --it;//on recule d'un élément pour avoir la date inférieure
    return it->second;
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
	
	unsigned int month = atoi(line.substr(5, 2).c_str());
	if (month > 12 || month < 1)
	{
		std::cerr << RED << "Error: invalid month. " << RESET << std::endl;
		return 0;
	}

	unsigned int day = atoi(line.substr(8, 2).c_str());
	if (day > 31 || ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30))
	{
		std::cerr << RED << "Error: invalid day. " << RESET << std::endl;
		return 0;
	}
	if (month == 2)
	{
		bool leapYear = (year % 4 == 0);
		if (day > (leapYear ? 29 : 28))
		{
			std::cerr << RED << "Error: leap year. " << RESET << std::endl;
			return 0;
		}
	}

	if (!atof(line.substr(13, line.length()).c_str()))
	{
		std::cerr << RED << "Error: no value. " << RESET << std::endl;
		return 0;
	}
	else if (atof(line.substr(13, line.length()).c_str()) < 0)
	{
		std::cerr << RED << "Error: not a positive number. " << RESET << std::endl;
		return 0;
	}
	else if (atof(line.substr(13, line.length()).c_str()) > 1000)
	{
		std::cerr << RED << "Error: too large a number. " << RESET << std::endl;
		return 0;
	}
	return 1;
}





void BitcoinExchange::print_map_classic()
{
    std::cout << YELLOW << "\n--- std::map _data ---" << RESET << std::endl;
    
	for (std::map<std::string, float>::const_iterator it = _data.begin(); it != _data.end(); ++it) 
        std::cout << "date: " << it->first << " | rate: " << it->second << std::endl;
}