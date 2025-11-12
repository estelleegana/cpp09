#!/bin/bash

# Couleurs pour l'affichage
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo "======================================"
echo "         TESTS PmergeMe"
echo "======================================"
echo ""

# Test 1 : Exemple simple (5 éléments)
echo -e "${YELLOW}Test 1: Exemple simple (5 éléments)${NC}"
./PmergeMe 3 5 9 7 4
echo ""

# Test 2 : Déjà trié
echo -e "${YELLOW}Test 2: Déjà trié${NC}"
./PmergeMe 1 2 3 4 5 6 7 8 9 10
echo ""

# Test 3 : Ordre inverse
echo -e "${YELLOW}Test 3: Ordre inverse${NC}"
./PmergeMe 10 9 8 7 6 5 4 3 2 1
echo ""

# Test 4 : Un seul élément
echo -e "${YELLOW}Test 4: Un seul élément${NC}"
./PmergeMe 42
echo ""

# Test 5 : Deux éléments
echo -e "${YELLOW}Test 5: Deux éléments${NC}"
./PmergeMe 5 3
echo ""

# Test 6 : Nombre impair d'éléments
echo -e "${YELLOW}Test 6: Nombre impair (7 éléments)${NC}"
./PmergeMe 8 3 5 1 9 7 4
echo ""

# Test 7 : Nombre pair d'éléments
echo -e "${YELLOW}Test 7: Nombre pair (8 éléments)${NC}"
./PmergeMe 8 3 5 1 9 7 4 2
echo ""

# Test 8 : Erreur - nombre négatif
echo -e "${YELLOW}Test 8: Erreur - nombre négatif${NC}"
./PmergeMe "-1" "2"
echo ""

# Test 9 : Erreur - pas un nombre
echo -e "${YELLOW}Test 9: Erreur - pas un nombre${NC}"
./PmergeMe 1 2 abc 4
echo ""

# Test 10 : Erreur - nombre trop grand
echo -e "${YELLOW}Test 10: Erreur - nombre trop grand${NC}"
./PmergeMe 1 2 2147483648 4
echo ""

# Test 11 : Beaucoup d'éléments (100 éléments)
echo -e "${YELLOW}Test 11: 100 éléments aléatoires${NC}"
if command -v shuf &> /dev/null; then
    ./PmergeMe $(shuf -i 1-1000 -n 100 | tr "\n" " ")
elif command -v jot &> /dev/null; then
    ./PmergeMe $(jot -r 100 1 1000 | tr '\n' ' ')
else
    echo "shuf ou jot non disponible, test skippé"
fi
echo ""

