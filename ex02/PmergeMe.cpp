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
}

void A::sortVector(std::vector<int> V)
{
	size_t Vsize = V.size();
	
	if (Vsize <= 1)
		return;

	//creation des paires
	std::vector<int> petits;
	std::vector<int> grands;

	//stocker le dernier elem si la liste est impaire
	bool Vimpair = (Vsize % 2 == 1);
	int der_elem_Vimpair = Vimpair ? V[Vsize - 1] : 0;
	// std::cout << "\nder_elem: " << der_elem_Vimpair;

	//1 ------------ trier les paires
	for (size_t i = 0; i < Vsize - (Vimpair ? 1 : 0); i += 2)
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

	std::cout << "\n\ngrands : ";
	for (size_t g = 0; g < grands.size(); g++)
		std::cout << grands[g] << " ";

	std::cout << "\npetits : ";
	for (size_t p = 0; p < petits.size(); p++)
		std::cout << petits[p] << " ";

	//2 ----------- trier les grands (recursivement)
	sortVector(grands);
	// std::cout << "\npetits[0]: " << petits[0];

	//3 ----------- inserer les petits
	std::vector<int> res = grands;
	//ajouter le premier petit
	// if (!petits.empty())
	// 	res.push_back(petits[0]);

	
	for (size_t j = 0; j < petits.size(); j++)
	{
		std::vector<int>::iterator pos = std::lower_bound(res.begin(), res.end(), petits[j]);
		res.insert(pos, petits[j]);
	}

	//4 ---------- inserer l'element impair s'il y a 
	if (Vimpair)
	{
		std::vector<int>::iterator pos_e = std::lower_bound(res.begin(), res.end(), der_elem_Vimpair);
		res.insert(pos_e, der_elem_Vimpair);
	}

	V = res;
	std::cout << "\n\ntri final: ";
	for (unsigned int i = 0; i < V.size(); i++)
			std::cout << V[i] << " ";
	// _V = V;
}

void A::sortDeque(std::deque<int> D)
{
	size_t Dsize = D.size();
	
	//si grands contient plus qu'1 elem, renverser la recursivite
	if (Dsize <= 1)
		return;
	
	bool Dimpair = (Dsize % 2 == 1);
	int der_elem_Dimpair = Dimpair ? D[Dsize - 1] : 0;
	std::deque<int> petits;
	std::deque<int> grands;

	//1 ------------ trier les paires
	for (size_t i = 0; i < Dsize - (Dimpair ? 1 : 0); i += 2)
	{
		if (D[i] > D[i + 1])
		{
			grands.push_back(D[i]);
			petits.push_back(D[i + 1]);
		}
		else
		{
			grands.push_back(D[i + 1]);
			petits.push_back(D[i]);
		}
	}

	//2 ----------- trier les grands (recursivement)
	sortDeque(grands);

	//3 ----------- inserer les petits
	std::deque<int> res = grands;
	for (size_t j = 0; j < petits.size(); j++)
	{
		std::deque<int>::iterator pos = std::lower_bound(res.begin(), res.end(), petits[j]);
		res.insert(pos, petits[j]);
	}


	//4 ---------- inserer l'element impair s'il y a 
	if (Dimpair)
	{
		std::deque<int>::iterator pos_e = std::lower_bound(res.begin(), res.end(), der_elem_Dimpair);
		res.insert(pos_e, der_elem_Dimpair);
	}

	D = res;
	_D = D;
}

void A::sort()
{
	std::cout << bold << "\nBefore: " << RESET;
	print_container("vector");

	clock_t Vstart = clock();
	sortVector(_V);
	clock_t Vend = clock();
	_Vtime = double(Vend - Vstart) / CLOCKS_PER_SEC * 1000000;

	clock_t Dstart = clock();
	sortDeque(_D);
	clock_t Dend = clock();
	_Dtime = double(Dend - Dstart) / CLOCKS_PER_SEC * 1000000;


	// std::cout << bold << "\nAfter: " << RESET;
	// print_container("vector");

	// std::cout << "\nTime to process a range of " << _Vsize << " elements with std::vector<int> : " << _Vtime << " us" << std::endl;
	// std::cout << "Time to process a range of " << _Dsize << " elements with std::deque<int> : " << _Dtime << " us" << std::endl;
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
