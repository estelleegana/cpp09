#pragma once

#include <iostream>//exception cerr
#include <vector>
#include <deque>
#include <sstream>//istringstream

#define RED "\033[31m"
#define GREEN "\033[32m"
#define bold "\033[1m"
#define RESET "\033[0m"

class A
{
	private:
		std::vector<int> _V;
		size_t _Vsize;
		double _Vtime;
		std::deque<int> _D;
		size_t _Dsize;
		double _Dtime;

	public:
		A();
		A(const A &copy);
		A &operator=(const A &other);
		~A();

		void sort();
		void sortVector(std::vector<int> &V);
		void sortDeque(std::deque<int> &D);
		void parse(int argc, char **argv);
		void print_container(std::string container_type);
};

