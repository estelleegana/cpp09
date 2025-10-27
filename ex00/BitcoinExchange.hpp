#pragma once

#include <iostream>//std::cout
#include <fstream>//std::ifstream
#include <map>
#include <cstdlib>//atoi
#include <sstream>//ss

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define bold "\033[1m"
#define RESET "\033[0m"

class BitcoinExchange
{
	private:
		std::map<std::string, float> _data;
	public:
		BitcoinExchange();
		BitcoinExchange(std::string csvfile);
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(BitcoinExchange &autre);
		~BitcoinExchange();

		void rateXvalue(std::string argv);
		float getExchangeRate(const std::string &date) const;

		void print_map_classic();
};

bool parsing_line(std::string &line);
