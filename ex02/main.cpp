#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	(void)argv;
	if (argc < 2)
	{
		std::cerr << RED"Error: not enough argv."RESET << std::endl;
		return 1;
	}

	try
	{
		A tri;
		tri.parse(argc, argv);
		tri.sort();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}