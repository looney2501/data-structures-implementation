#include "Multime.h"
#include "IteratorMultime.h"

#include <iostream>

//complexitate Theta(n)
void Multime::redimensionare()
{
	auto elemente_noi = new TElem[2 * capacitate];
	auto urmatori_noi = new TElem[2 * capacitate];
	auto precedenti_noi = new TElem[2 * capacitate];
	for (int i = 0; i < capacitate; i++)
	{
		elemente_noi[i] = elemente[i];
		urmatori_noi[i] = urmator[i];
		precedenti_noi[i] = precedent[i];
	}
	delete[] precedent;
	delete[] elemente;
	delete[] urmator;
	elemente = elemente_noi;
	urmator = urmatori_noi;
	precedent = precedenti_noi;
	for (int i = capacitate; i < 2 * capacitate - 1; i++)
		urmator[i] = i + 1;
	urmator[2 * capacitate - 1] = -1;
	if (prim_liber != -1)
		urmator[prim_liber] = capacitate;
	else
		prim_liber = capacitate;
	capacitate *= 2;
}

//Complexitate Theta(1)
int Multime::aloca()
{
	int index = prim_liber;
	prim_liber = urmator[prim_liber];
	return index;
}

//complexitate Theta(1)
void Multime::dealoca(int index)
{
	precedent[index] = -1;
	urmator[index] = prim_liber;
	prim_liber = index;
}

int Multime::creeaza_nod(TElem element)
{
	//redimensioneaza daca nu mai e loc
	if (prim_liber == -1)
		redimensionare();
	int nod = aloca();
	urmator[nod] = -1;
	precedent[nod] = -1;
	elemente[nod] = element;
	return nod;
}

//complexitate O(n)
int Multime::cauta_nod(TElem element) const
{
	if (element == elemente[ultim])
		return ultim;
	int pozitie_element = -1;
	for (int i = prim; i != -1 && pozitie_element == -1; i = urmator[i])
		if (elemente[i] == element)
			pozitie_element = i;
	return pozitie_element;
}

//complexitate Theta(1)
Multime::Multime() {
	elemente = new TElem[1];
	urmator = new int[1];
	precedent = new int[1];
	prim = -1;
	ultim = -1;
	capacitate = 1;
	dimensiune = 0;
	prim_liber = 0;
	urmator[prim_liber] = -1;
}

//complexitate O(n)
bool Multime::adauga(TElem elem) {
	//daca elementul e deja in multime, nu il mai adaugam
	if (cauta_nod(elem) != -1)
		return false;
	auto nod = creeaza_nod(elem);

	//adaugam la final

	//caz lista vida
	if (ultim == -1)
	{
		prim = ultim = nod;
	}
	//lista nu e vida
	else
	{
		urmator[ultim] = nod;
		precedent[nod] = ultim;
		ultim = nod;
	}
	dimensiune++;
	return true;
}

//complexitate O(n)
bool Multime::sterge(TElem elem) {
	auto nod = cauta_nod(elem);
	//elementul nu exista in lista
	if (nod == -1)
		return false;
	//cazul in care elementul exista

	//daca nod e pe prima pozitie sau pe ultima, tratam si cazul in care lista e formata dintr-un singur element
	if (nod == prim)
	{
		//exista un singur element
		if (prim == ultim)
		{
			prim = ultim = -1;
		}
		//exista cel putin 2 elemente
		else
		{
			prim = urmator[prim];
			precedent[prim] = -1;
		}
	}
	else if (nod == ultim)
	{
		ultim = precedent[ultim];
		urmator[ultim] = -1;
	}
	//daca nod e undeva intre primul si ultimul
	else
	{
		urmator[precedent[nod]] = urmator[nod];
		precedent[urmator[nod]] = precedent[nod];
	}
	dealoca(nod);
	dimensiune--;
	return true;
}

//complexitate O(n)
bool Multime::cauta(TElem elem) const {
	if (cauta_nod(elem) != -1)
		return true;
	return false;
}

//complexitate Theta(1)
int Multime::dim() const {
	return dimensiune;
}

//complexitate Theta(1)
bool Multime::vida() const {
	if (ultim == -1)
		return true;
	return false;
}

//complexitate Theta(1)
Multime::~Multime() {
	delete[] elemente;
	delete[] urmator;
	delete[] precedent;
}

// PSEUDOCOD
// //pre: m:Multime
// //post: diferenta_max_min(m)=-1 daca m e vida sau diferenta_max_min(m)=max-min, unde max e cea mai mare valoare din multime, iar min e cea mai mica
// Functia diferenta_max_min(m):
//		Daca vida(m) atunci:
//			diferenta_max_min <- -1
//		SfDaca
//		min, max : TElem
//		min <- m.elemente[prim]
//		max <- m.elemente[prim]
//		Pentru i<-prim, i!=-1, i <- m.urmator[i] executa:
//			Daca m.elemente[i] < min atunci:
//				min <- m.elemente[i]
//			SfDaca
//			Daca m.elemente[i] > max atunci:
//				max < m.elemente[i]
//			SfDaca
//		SfPentru
//		diferenta_max_min <- max-min
// SfFunctie
// caz favorabil = caz defavorabil = caz mediu - Theta(n)
int Multime::diferenta_max_min() const
{
	if (vida())
		return -1;
	TElem min = elemente[prim];
	TElem max = elemente[prim];
	for (int i = prim; i != -1; i = urmator[i])
	{
		if (elemente[i] < min)
			min = elemente[i];
		if (elemente[i] > max)
			max = elemente[i];
	}
	return max - min;
}

//complexitata Theta(1)
IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}