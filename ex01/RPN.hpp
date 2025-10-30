#pragma once

#include <iostream>//cerr, endl
#include <stack>
#include <sstream>//istringstream
#include <cctype>
#include <cstdlib>//atol

class RPN
{
	private:
		std::stack<int> _numbers;

	public:
	RPN();
	RPN(const RPN &copy);
	RPN &operator=(const RPN &other);
	~RPN();

	int calculate(std::string argv);
};

