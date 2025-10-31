#include "PmergeMe.hpp"

A::A() {}

A::A(const A &copy) {*this = copy;}

A &A::operator=(const A &other) {(void)other; return *this;}

A::~A() {}




void A::parse(int argc, char **argv)
{

	for (int i = 1; i < argc; i++)
	{
		std::istringstream iss(argv[i]);
		int nb;

		if (!(iss >> nb) || !iss.eof())//!iss.eof() lire jusqu'au bout de la ligne (au cas ou y a qqch colle a un nombre)
			throw std::runtime_error(RED"Error: must only be unsigned int."RESET);
		else if (nb < 0)
			throw std::runtime_error(RED"Error: only positive integers."RESET);
		// else if (nb > INT_MAX)//gere ds le !iss >> nb
		// 	throw std::runtime_error(RED"Error: overflow."RESET);
		_D.push_back(nb);
		_V.push_back(nb);
	}
	if (_D.empty())//on aurait pu prendre _V aussi
		throw std::runtime_error(RED"Error: no input."RESET);
	_Vsize = _V.size();
	_Dsize = _D.size();
	_Vimpair = (_Vsize % 2 == 1) ? 1 : 0;
	_Dimpair = (_Dsize % 2 == 1) ? 1 : 0;

	std::cout << bold << "_Vsize: " << RESET << _Vsize << std::endl; 
	std::cout << bold << "_Dsize: " << RESET << _Dsize << std::endl; 
	std::cout << bold << "_Vimpair?: " << RESET << _Vimpair << std::endl; 
	std::cout << bold << "_Dimpair?: " << RESET << _Dimpair << std::endl; 
}

void A::sortVector(std::vector<int> &V)
{
	clock_t start = clock();
	size_t Vsize = V.size();
	if (Vsize <= 1)
		return;
	
	//creation des paires
	std::vector<int> petits;
	std::vector<int> grands;

	//trier les paires
	for (size_t i = 0; i < Vsize + 1; i += 2)
	{
		if (V[i] > V[i + 1])
		{
			grands.push_back(V[i]);
			petits.push_back(V[i + 1]);
		}
		else
		{
			grands.push_back(V[i + 1]);
			petits.push_back(V[i]);
		}
	}
	// std::sort(_V.begin(), _V.end());

	std::cout << "\ngrands : ";
	for (size_t g = 0; g < grands.size() - 1; g++)
		std::cout << grands[g] << " ";

	std::cout << "\npetits : ";
	for (size_t p = 0; p < petits.size() - 1
	; p++)
		std::cout << petits[p] << " ";

	// sortVector(grands);
	std::vector<int> res = grands;

	V = res;
	clock_t end = clock();
	_Vtime = double(end - start) / CLOCKS_PER_SEC * 1000000;
}

void A::sortDeque()
{
	clock_t start = clock();
	// sleep(3);
	clock_t end = clock();
	_Dtime = double(end - start) / CLOCKS_PER_SEC * 1000000;
}

void A::sort()
{
	std::cout << bold << "Before: " << RESET;
	print_container("vector");

	sortVector(_V);
	sortDeque();


	std::cout << bold << "\nAfter: " << RESET;
	print_container("vector");

	std::cout << "\nTime to process a range of " << _Vsize << " elements with std::vector<int> : " << _Vtime << " us" << std::endl;
	std::cout << "Time to process a range of " << _Dsize << " elements with std::deque<int> : " << _Dtime << " us" << std::endl;
}

void A::print_container(std::string container_type)
{
	if (container_type == "vector")
	{
		for (unsigned int i = 0; i < _V.size(); i++)
			std::cout << _V[i] << " ";
	}
	else if (container_type == "deque")
	{
		for (unsigned int i = 0; i < _D.size(); i++)
			std::cout << _D[i] << " ";
	}
}
