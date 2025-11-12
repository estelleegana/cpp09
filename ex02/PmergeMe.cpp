#include "PmergeMe.hpp"

A::A() {}

A::A(const A &copy) : _V(copy._V), _D(copy._D) {}

A &A::operator=(const A &other) {(void)other; return *this;}

A::~A() {}






//parsing
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

//tri : print le container initial,
//trier 1 container (vector)
//puis l'autre (deque) *en calculant le temps mis*, 
//print le container trie et les temps 
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


	std::cout << bold << "\nAfter : " << RESET;
	print_container("vector");
	// std::cout << std::endl;
	// print_container("deque");

	std::cout << "\nTime to process a range of " << _Vsize << " elements with std::vector<int> : " << _Vtime << " us" << std::endl;
	std::cout << "Time to process a range of " << _Dsize << " elements with std::deque<int> : " << _Dtime << " us" << std::endl;
}

//tri : 
void A::sortVector(std::vector<int> &V)
{
    size_t Vsize = V.size();
    
    if (Vsize <= 1)
        return;//evite la boucle infinie de la recursion
    
    std::vector<int> grands;
    std::vector<int> petits;
    
    bool Vimpair = (Vsize % 2 == 1);
    int der_elem_Vimpair = Vimpair ? V[Vsize - 1] : 0;
    
    // 1 creer paires grands/petits
    for (size_t i = 0; i < Vsize - (Vimpair ? 1 : 0); i += 2)
    {
        if (V[i] > V[i + 1])
        {
            grands.push_back(V[i]);
            petits.push_back(V[i+1]);
        }
        else
        {
            grands.push_back(V[i+1]);
            petits.push_back(V[i]);
        }
    }
    
    // 2 trier grands recursivement
    sortVector(grands);
    
    // 3 inserer petits ds l'ordre jacobstahl
    std::vector<int> resultat = grands;

	if (!petits.empty())
	{
		std::vector<size_t> insertionOrder = ordreInsertion(petits.size());

		for (size_t i = 0; i < insertionOrder.size(); ++i)
		{
			size_t idx = insertionOrder[i];
			int val = petits[idx];
			
			std::vector<int>::iterator pos = std::lower_bound(resultat.begin(), resultat.end(), val);
			resultat.insert(pos, val);
		}
	}
    else
    {
        resultat = petits;
    }
    
    // 4 inserer elem impair
    if (Vimpair)
    {
        std::vector<int>::iterator pos = std::lower_bound(resultat.begin(), resultat.end(), der_elem_Vimpair);
        resultat.insert(pos, der_elem_Vimpair);
    }

    V = resultat;
}

void A::sortDeque(std::deque<int> &D)
{
    size_t Dsize = D.size();
    
    if (Dsize <= 1)
        return;//evite la boucle infinie de la recursion
    
    std::deque<int> grands;
    std::deque<int> petits;
    
    bool Dimpair = (Dsize % 2 == 1);
    int der_elem_Dimpair = Dimpair ? D[Dsize - 1] : 0;
    
    // 1 creer paires grands/petits
    for (size_t i = 0; i < Dsize - (Dimpair ? 1 : 0); i += 2)
    {
        if (D[i] > D[i + 1])
        {
            grands.push_back(D[i]);
            petits.push_back(D[i+1]);
        }
        else
        {
            grands.push_back(D[i+1]);
            petits.push_back(D[i]);
        }
    }
    
    // 2 trier grands recursivement
    sortDeque(grands);
    
    // 3 inserer petits ds l'ordre jacobstahl
    std::deque<int> resultat = grands;

	if (!petits.empty())
	{
		std::deque<size_t> insertionOrder = ordreInsertionD(petits.size());

		for (size_t i = 0; i < insertionOrder.size(); ++i)
		{
			size_t idx = insertionOrder[i];
			int val = petits[idx];
			
			std::deque<int>::iterator pos = std::lower_bound(resultat.begin(), resultat.end(), val);
			resultat.insert(pos, val);
		}
	}
    else
    {
        resultat = petits;
    }
    
    // 4 inserer elem impair
    if (Dimpair)
    {
        std::deque<int>::iterator pos = std::lower_bound(resultat.begin(), resultat.end(), der_elem_Dimpair);
        resultat.insert(pos, der_elem_Dimpair);
    }

    D = resultat;
}





//outils pr vector: suite de jacobstahl (0, 1, J(n-1) + 2J(n-2)...)
std::vector<size_t> A::jacobstahl(size_t n)
{
	std::vector<size_t> seq;
	seq.push_back(0);
	seq.push_back(1);

	size_t i = 2;
	while (true)
	{
		size_t next = seq[i - 1] + 2 * seq[i - 2];
		if (next > n)
			break;
		seq.push_back(next);
		i++;
	}

	return seq;
}

std::vector<size_t> A::ordreInsertion(size_t n)
{
    if (n == 0)
        return std::vector<size_t>();
    
    std::vector<size_t> jacobsthalSeq = jacobstahl(n + 1);
    std::vector<size_t> ordre;
    std::vector<bool> used(n, false);
    
    for (size_t i = 3; i < jacobsthalSeq.size(); ++i) {
        size_t jacobIdx = jacobsthalSeq[i];
        
        if (jacobIdx > n)
            jacobIdx = n;
        
        if (jacobIdx > 0 && !used[jacobIdx - 1]) {
            ordre.push_back(jacobIdx - 1);
            used[jacobIdx - 1] = true;
        }
        
        if (i > 3) {
            size_t prevJacob = jacobsthalSeq[i - 1];
            for (size_t j = jacobIdx - 1; j > prevJacob && j > 0; --j) {
                if (!used[j - 1]) {
                    ordre.push_back(j - 1);
                    used[j - 1] = true;
                }
            }
        }
    }
    
    for (size_t i = 0; i < n; ++i) {
        if (!used[i]) {
            ordre.push_back(i);
        }
    }
    
    return ordre;
}

//outils pr deque
std::deque<size_t> A::jacobstahlD(size_t n)
{
	std::deque<size_t> seq;
	seq.push_back(0);
	seq.push_back(1);

	size_t i = 2;
	while (true)
	{
		size_t next = seq[i - 1] + 2 * seq[i - 2];
		if (next > n)
			break;
		seq.push_back(next);
		i++;
	}

	return seq;
}

std::deque<size_t> A::ordreInsertionD(size_t n)
{
    if (n == 0)
        return std::deque<size_t>();
    
    std::deque<size_t> jacobsthalSeq = jacobstahlD(n + 1);
    std::deque<size_t> ordre;
    std::deque<bool> used(n, false);
    
    for (size_t i = 3; i < jacobsthalSeq.size(); ++i) {
        size_t jacobIdx = jacobsthalSeq[i];
        
        if (jacobIdx > n)
            jacobIdx = n;
        
        if (jacobIdx > 0 && !used[jacobIdx - 1]) {
            ordre.push_back(jacobIdx - 1);
            used[jacobIdx - 1] = true;
        }
        
        if (i > 3) {
            size_t prevJacob = jacobsthalSeq[i - 1];
            for (size_t j = jacobIdx - 1; j > prevJacob && j > 0; --j) {
                if (!used[j - 1]) {
                    ordre.push_back(j - 1);
                    used[j - 1] = true;
                }
            }
        }
    }
    
    for (size_t i = 0; i < n; ++i) {
        if (!used[i]) {
            ordre.push_back(i);
        }
    }
    
    return ordre;
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
