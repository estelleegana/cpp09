#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}=== Tests valides ===${NC}"

echo -n "Test 1: 8 9 * 9 - 9 - 9 - 4 - 1 + => "
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
echo "attendu: 42"
echo ""

echo -n "Test 2: 7 7 * 7 - => "
./RPN "7 7 * 7 -"
echo "attendu: 42"
echo ""

echo -n "Test 3: 1 2 * 2 / 2 * 2 4 - + => "
./RPN "1 2 * 2 / 2 * 2 4 - +"
echo "attendu: 0"
echo ""

echo -n "Test 4: 5 1 2 + 4 * + 3 - => "
./RPN "5 1 2 + 4 * + 3 -"
echo "attendu: 14"
echo ""

echo -n "Test 5: 9 8 * => "
./RPN "9 8 *"
echo "attendu: 72"
echo ""

echo -n "Test de l'enonce: 1 2 * 2 / 2 * 2 4 - + => "
./RPN "1 2 * 2 / 2 * 2 4 - +"
echo "attendu: 0"
echo ""

echo -e "\n${YELLOW}=== Tests d'erreurs ===${NC}"

echo -e "${RED}Test 6: Pas d'arguments${NC}"
./RPN
echo ""

echo -e "${RED}Test 7: Trop d'arguments${NC}"
./RPN "1 2 +" "3 4 +"
echo ""

echo -e "${RED}Test 8: Parenthèses (interdites)${NC}"
./RPN "(1 + 1)"
echo ""

echo -e "${RED}Test 9: Pas assez de nombres pour l'opérateur${NC}"
./RPN "1 +"
echo ""

echo -e "${RED}Test 10: Trop de nombres (pas assez d'opérateurs)${NC}"
./RPN "1 2 3"
echo ""

echo -e "${RED}Test 11: Opérateur en premier${NC}"
./RPN "+ 1 2"
echo ""

echo -e "${RED}Test 12: Caractère invalide${NC}"
./RPN "1 2 a"
echo ""

echo -e "${RED}Test 13: Nombre >= 10${NC}"
./RPN "10 2 +"
echo ""

echo -e "${RED}Test 14: Expression vide${NC}"
./RPN ""
echo ""

echo -e "${RED}Test 15: Seulement des espaces${NC}"
./RPN "   "
echo ""

echo -e "${RED}Test 16: Division par zéro${NC}"
./RPN "1 0 /"
echo ""

echo -e "${RED}Test 17: Nombre décimal (interdit)${NC}"
./RPN "1.5 2 +"
echo ""

echo -e "${RED}Test 18: Nombre négatif${NC}"
./RPN "-1 2 +"
echo ""

echo -e "${RED}Test 19: Opérateur invalide${NC}"
./RPN "1 2 %"
echo ""

echo -e "${RED}Test 20: Multiple opérateurs consécutifs${NC}"
./RPN "1 2 + +"
echo ""