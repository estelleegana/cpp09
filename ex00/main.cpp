#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
		std::cerr << "./btc <input.txt>" << std::endl;
	else
	{
		if (parsing_inputfile(argv[1]))
			calcul(argv[1]);
	}
}