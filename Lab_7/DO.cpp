#include "Iterator.h"
#include "DO.h"
#include <iostream>
#include <exception>

using namespace std;

//complexitate Theta(dimensiune)
void DO::redimensionare()
{
	auto elemente_noi = new TElem[2 * capacitate];
	auto urmatori_noi = new int[2 * capacitate];
	auto parinti_noi = new int[2 * capacitate];
	auto st_noi = new int[2 * capacitate];
	auto dr_noi = new int[2 * capacitate];
	for (int i = 0; i < capacitate; i++)
	{
		elemente_noi[i] = elemente[i];
		urmatori_noi[i] = urmator[i];
		parinti_noi[i] = parinte[i];
		st_noi[i] = st[i];
		dr_noi[i] = dr[i];
	}
	delete[] parinte;
	delete[] elemente;
	delete[] urmator;
	delete[] st;
	delete[] dr;
	elemente = elemente_noi;
	urmator = urmatori_noi;
	parinte = parinti_noi;
	st = st_noi;
	dr = dr_noi;
	//setare noi urmatori pt spatiul liber
	for (int i = capacitate; i < 2 * capacitate - 1; i++)
		urmator[i] = i + 1;
	urmator[2 * capacitate - 1] = -1;
	//pozitionarea corecta a lui prim_liber
	if (prim_liber != -1)
		urmator[prim_liber] = capacitate;
	else
		prim_liber = capacitate;
	capacitate *= 2;
}

//Complexitate Theta(1)
int DO::aloca()
{
	int index = prim_liber;
	prim_liber = urmator[prim_liber];
	return index;
}

//complexitate Theta(1)
void DO::dealoca(int index)
{
	parinte[index] = NIL;
	st[index] = NIL;
	dr[index] = NIL;
	urmator[index] = prim_liber;
	prim_liber = index;
}

//complexitate O(n)
int DO::creeaza_nod(TElem element)
{
	//redimensioneaza daca nu mai e loc
	if (dimensiune == capacitate)
		redimensionare();
	int nod = aloca();
	urmator[nod] = NIL;
	parinte[nod] = NIL;
	st[nod] = NIL;
	dr[nod] = NIL;
	elemente[nod] = element;
	return nod;
}

//complexitate O(adancime_arbore)
void DO::cauta_nod(TCheie c, int& poz, int& par) const
{
	poz = radacina;
	par = NIL;
	while (poz != NIL && c != elemente[poz].first)
	{
		if (!r(elemente[poz].first, c))
		{
			par = poz;
			poz = st[poz];
			continue;
		}
		if (!r(c, elemente[poz].first))
		{
			par = poz;
			poz = dr[poz];
			continue;
		}
	}
}

//complexitate O(adancime_arbore)
int DO::minim(int p) const
{
	if (p != NIL)
	{
		while (st[p] != NIL)
		{
			p = st[p];
		}
	}
	return p;
}

//complexitate O(adancime_arbore)
int DO::maxim(int p) const
{
	if (p != NIL)
	{
		while (dr[p] != NIL)
		{
			p = dr[p];
		}
	}
	return p;
}

int DO::sterge_rec(int p, TElem e)
{
	if (p == NIL)
	{
		return NIL;
	}
	if (!r(elemente[p].first, e.first))
	{
		//se sterge din subarborele stang
		st[p] = sterge_rec(st[p], e);
		if (st[p] != NIL)
		{
			parinte[st[p]] = p;
		}
		return p;
	}
	else
	{
		if (!r(e.first, elemente[p].first))
		{
			//se sterge din subarborele drept
			dr[p] = sterge_rec(dr[p], e);
			if (dr[p] != NIL)
			{
				parinte[dr[p]] = p;
			}
			return p;
		}
		else
		{
			//am ajuns la nodul care trebuie sters
			if (st[p] != NIL && dr[p] != NIL)
			{
				//nodul are ambii subarbori
				auto temp = minim(dr[p]);
				elemente[p] = elemente[temp];
				dr[p] = sterge_rec(dr[p], elemente[p]);
				return p;
			}
			else
			{
				auto temp = p;
				int repl;
				if (st[p] == NIL)
				{
					//nu exista subarbore stang
					repl = dr[p];
				}
				else
				{
					//nu exista subarbore drept
					repl = st[p];
				}
				dealoca(temp);
				return repl;
			}
		}
	}
}

//complexitate Theta(1)
DO::DO(Relatie r) {
	this->r = r;
	elemente = new TElem[1];
	urmator = new int[1];
	parinte = new int[1];
	st = new int[1];
	dr = new int[1];
	radacina = NIL;
	parinte[0] = NIL;
	st[0] = NIL;
	dr[0] = NIL;
	capacitate = 1;
	dimensiune = 0;
	prim_liber = 0;
	urmator[prim_liber] = NIL;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
//complexitate O(adancime_arbore)
TValoare DO::adauga(TCheie c, TValoare v) {
	int poz, par;
	//daca radacina e NIL, adaugam
	if (radacina == NIL)
	{
		auto nod_nou = creeaza_nod(make_pair(c, v));
		radacina = nod_nou;
		dimensiune++;
		return NULL_TVALOARE;
	}
	//caut sa vad daca exista cheia sau care ar trebui sa fie parintele ei
	cauta_nod(c, poz, par);
	//am gasit cheia in dictionar
	if (poz != NIL)
	{
		auto old_val = elemente[poz].second;
		elemente[poz].second = v;
		return old_val;
	}
	//nu am gasit cheia in dictionar dar stiu pozitia parintelui
	else
	{
		auto nod_nou = creeaza_nod(make_pair(c, v));
		//verific daca trebuie sa adaug la stanga sau la dreapta lui par
		if (!r(elemente[par].first, c))
		{
			st[par] = nod_nou;
			parinte[nod_nou] = par;
		}
		else
		{
			dr[par] = nod_nou;
			parinte[nod_nou] = par;
		}
		dimensiune++;
		return NULL_TVALOARE;
	}
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
//complexitate O(adancime_arbore)
TValoare DO::cauta(TCheie c) const {
	int poz, par;
	cauta_nod(c, poz, par);
	if (poz != NIL)
		return elemente[poz].second;
	return NULL_TVALOARE;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
//complexitate O(adancime_arbore)
TValoare DO::sterge(TCheie c) {
	auto val_stearsa = cauta(c);
	if (val_stearsa != NULL_TVALOARE)
	{
		radacina = sterge_rec(radacina, make_pair(c, val_stearsa));
		if (radacina != NIL)
		{
			parinte[radacina] = NIL;
		}
		dimensiune--;
	}
	return val_stearsa;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
//complexitate Theta(1)
int DO::dim() const {
	return dimensiune;
}

//verifica daca dictionarul e vid
//complexitate Theta(1)
bool DO::vid() const {
	return dimensiune == 0;
}

Iterator DO::iterator() const {
	return  Iterator(*this);
}

DO::~DO() {
	delete[] elemente;
	delete[] urmator;
	delete[] parinte;
	delete[] st;
	delete[] dr;
}