#pragma once

#include <iostream>//exception cerr
#include <vector>
#include <deque>
#include <sstream>//istringstream
#include <unistd.h>//sleep (pour tester)
#include <algorithm>//std::sort (pour tester)

#define RED "\033[31m"
#define GREEN "\033[32m"
#define bold "\033[1m"
#define RESET "\033[0m"

class A
{
	private:
		std::vector<int> _V;
		size_t _Vsize;
		bool _Vimpair;
		double _Vtime;
		std::deque<int> _D;
		size_t _Dsize;
		double _Dtime;
		bool _Dimpair;

	public:
		A();
		A(const A &copy);
		A &operator=(const A &other);
		~A();

		void sort();
		void sortVector(std::vector<int> &V);
		void sortDeque();
		void parse(int argc, char **argv);
		void print_container(std::string container_type);
};

