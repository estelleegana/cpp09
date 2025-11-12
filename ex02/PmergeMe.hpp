#pragma once

#include <iostream>//exception cerr
#include <vector>
#include <deque>
#include <sstream>//istringstream
#include <map>

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

		void parse(int argc, char **argv);
		void sort();
		void sortVector(std::vector<int> &V);
		void sortDeque(std::deque<int> &D);
		
		std::vector<size_t> jacobstahl(size_t n);
		std::deque<size_t> jacobstahlD(size_t n);
		std::vector<size_t> ordreInsertion(size_t n);
		std::deque<size_t> ordreInsertionD(size_t n);
		void print_container(std::string container_type);
};

