#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

using std::cout;

//complexitate generala - Theta(1)
const int Multime::hash_code(TElem e) const
{
	return abs(e);
}

//complexitate generala - Theta(1)
const int Multime::d1(TElem e) const
{
	return e % t_size;
}

//complexitate generala - Theta(1)
const int Multime::d2(TElem e) const
{
	int val = 1 + e % (t_size - 1);
	if (val % 2 == 0)
		val++;
	return val;
}

//complexitate generala - Theta(1)
const int Multime::d(TElem e, int i) const
{
	int hash_e = hash_code(e);
	return (d1(hash_e) + i * d2(hash_e)) % t_size;
}

//complexitate best-case - Theta(1), worst-case - Theta(n) (toate elementele sunt dispersate in acelasi loc)
const int Multime::cauta_poz(TElem e) const
{
	int i = 0, j;
	do
	{
		j = d(e, i);
		if (table[j] == e)
		{
			return j;
		}
		i++;
	} while (table[j] != NIL && i < t_size);
	return -1;
}

//complexitate generala - Theta(t_size)
Multime::Multime() {
	for (int i = 0; i < t_size; i++)
	{
		table[i] = NIL;
	}
	n = 0;
}

//complexitate best-case - Theta(1), worst-case - Theta(n)
bool Multime::adauga(TElem elem) {
	//elementul exista deja
	if (cauta_poz(elem) != -1)
		return false;
	//parcurgem secventa de locatii pana gasim una libera
	int i = 0, j;
	bool gasit = false;
	do
	{
		j = d(elem, i);
		if (table[j] == NIL || table[j] == STERS)
		{
			table[j] = elem;
			gasit = true;
		}
		else
		{
			i++;
		}
	} while (!gasit && i < t_size);
	if (gasit)
	{
		n++;
		return true;
	}
	else
	{
		std::cout << "depasire tabela!\n";
		return false;
	}
}

//complexitate best-case - Theta(1), worst-case - Theta(n)
bool Multime::sterge(TElem elem) {
	int poz = cauta_poz(elem);
	if (poz == -1)
	{
		return false;
	}
	table[poz] = STERS;
	n--;
	return true;
}

//complexitate best-case - Theta(1), worst-case - Theta(n) (toate elementele sunt dispersate in acelasi loc)
bool Multime::cauta(TElem elem) const {
	if (cauta_poz(elem) == -1)
		return false;
	return true;
}

//complexitate generala - Theta(1)
int Multime::dim() const {
	return n;
}

//complexitate generala - Theta(1)
bool Multime::vida() const {
	return n == 0;
}

//complexitate generala - Theta(1)
Multime::~Multime() {
}

//complexitate generala - O(t_size)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}