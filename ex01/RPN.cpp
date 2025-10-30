#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &copy) {*this = copy;}

RPN &RPN::operator=(const RPN &other) {(void)other; return *this;}

RPN::~RPN() {}











int RPN::calculate(std::string argv)
{
	std::istringstream iss(argv);
	std::string token;

	if (argv.empty())
		throw std::runtime_error("Error: empty argv.");

	bool endToken = 1;
	while (iss >> token)
	{
		endToken = 0;
		if (token.size() == 1 && isdigit(token[0]))
			_numbers.push(atol(token.c_str()));
		else if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			// std::cout << "operateur: " << token << std::endl;
			if (_numbers.size() < 2)
				throw std::runtime_error("Error: not enough digits to calculate anything.");
			
			int a = _numbers.top();
			_numbers.pop();
			int b = _numbers.top();
			_numbers.pop();
			// std::cout << "a et b: " << a << ", " << b << std::endl;

			int res;
			if (token == "+")
				res = b + a;
			if (token == "-")
				res = b - a;
			if (token == "*")
				res = b * a;
			if (token == "/")
			{
				if (a == 0)
					throw std::runtime_error("Error: division by 0 is impossible.");
				res = b / a;
			}
			// std::cout << "res a ce stade: " << res << std::endl<< std::endl;
			_numbers.push(res);
		}
		else
			throw std::runtime_error("Error: token must be either unsigned int < 10 or operator + - * /.");
	}

	if (endToken)
		throw std::runtime_error("Error");

	if (_numbers.size() != 1)
		throw std::runtime_error("Error");
	return _numbers.top();
}