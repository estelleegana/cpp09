#pragma once

#include <iostream>//std::cout
#include <fstream>//std::ifstream
#include <map>
#include <cstdlib>//atoi

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
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(BitcoinExchange &autre);
		~BitcoinExchange();

		std::map<std::string, float> getData();
		void setPair(const std::string& date, float value);
};

bool parsing_inputfile(std::string argv);
bool parsing_line(std::string &line);
void calcul(std::string argv);
void print_map_classic(const std::map<std::string, float>& ma_map);