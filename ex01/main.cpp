#include "RPN.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "./RPN \"<numbers and operators>\"" << std::endl;
		return 1;
	}

	try
	{
		RPN suite;
		int res = suite.calculate(argv[1]);
		std::cout << res << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}