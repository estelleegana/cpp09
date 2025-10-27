#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		std::cerr << "./btc <input.txt>" << std::endl;
		return 1;
	}

	try
	{
		BitcoinExchange btc("data.csv");
		btc.rateXvalue(argv[1]);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}