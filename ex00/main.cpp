#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
		std::cerr << "./btc <input.txt>" << std::endl;
	else
	{
		std::ifstream fichier(argv[1]);
		if (!fichier)
			std::cerr << RED << "Error: could not open file." << RESET << std::endl;	
		else
		{
			BitcoinExchange btc;
			btc.start(argv[1]);
		}
		fichier.close();
	}
}