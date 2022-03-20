#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

using std::cout;

// pastreaza numai acele elemente care nu apar în multimea b
// returneaza numarul de elemente eliminate
// Functie diferenta(a, b):
// //pre: a, b: Multime
// //post: adevarat
//		i, dif: Intreg
//		dif<-0
//		Pentru i=0,a.t_size executa:
//			Daca (a.table[i]!=NIL) && (a.table[i]!=STERS) atunci:
//				Daca (b.cauta(table[i])==TRUE) atunci:
//					dif'<-dif+1
//					a.sterge(table[i])
//				SfDaca
//			SfDaca
//		SfPentru
//		diferenta(a, b)<-dif
// SfFunctie
// Complexitate best-case - Theta(a.t_size), worst-case - Theta(a.t_size*n), unde n e nr de elemente din b
int Multime::diferenta(const Multime& b)
{
	int i, dif = 0;
	for (i = 0; i < t_size; i++)
	{
		if (table[i] != NIL && table[i] != STERS)
		{
			if (b.cauta(table[i]))
			{
				dif++;
				this->sterge(table[i]);
				//table[i]=STERS
			}
		}
	}
	return dif;
}

//complexitate generala - Theta(2*t_size)
void Multime::rehash()
{
	int old_size = t_size;
	t_size *= 2;
	TElem* old_table = table;
	table = new TElem[t_size];
	for (int i = 0; i < t_size; i++)
	{
		table[i] = NIL;
	}
	int added = 0;
	for (int i = 0; i < old_size; i++)
	{
		if (old_table[i] != NIL && old_table[i] != STERS)
		{
			adauga(old_table[i]);
			added += 1;
		}
	}
	n -= added;
	delete[] old_table;
}

//complexitate generala - Theta(1)
const double Multime::load_factor() const
{
	return (n * 1.0) / (t_size * 1.0);
}

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
	t_size = 4;
	table = new TElem[4];
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
	//facem rehashing daca factorul de incarcare e mai mare de 0.75
	if (load_factor() >= 0.75)
	{
		rehash();
	}
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
	} while (!gasit);
	if (gasit)
	{
		n++;
		return true;
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
	delete[] table;
}

//complexitate generala - O(t_size)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}