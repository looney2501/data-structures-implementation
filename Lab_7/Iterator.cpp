#include "Iterator.h"
#include "DO.h"
#include <exception>

using namespace std;

//complexitate O(adancime_arbore)
Iterator::Iterator(const DO& d) : dict(d) {
	curent = d.minim(d.radacina);
}

//complexitate O(adancime_arbore)
void Iterator::prim() {
	curent = dict.minim(dict.radacina);
}

//complexitate O(adancime_arbore)
void Iterator::urmator() {
	//arunca exceptie daca iteratorul nu e valid
	if (curent == NIL)
	{
		throw std::exception();
	}

	//verificam daca pozitia curenta indicata de iterator are subarbore drept
	if (dict.dr[curent] != NIL)
	{
		curent = dict.minim(dict.dr[curent]);
	}
	//mergem inapoi catre radacina, pana cand nu mai suntem aflati pe o ramura din dreapta
	else
	{
		auto parinte = dict.parinte[curent];
		while (parinte != NIL && dict.dr[parinte] == curent)
		{
			curent = parinte;
			parinte = dict.parinte[parinte];
		}
		curent = parinte;
	}
}

//complexitate Theta(1)
bool Iterator::valid() const {
	return curent != NIL;
}

TElem Iterator::element() const {
	//arunca exceptie daca iteratorul nu este valid
	if (curent == NIL)
	{
		throw std::exception();
	}

	return dict.elemente[curent];
}

// Subalgoritm revinoKPasi(k,it)
// {pre: k:Intreg, it:Iterator}
// {post: iteratorul refera al k-lea element inaintea celui pe care era deja sau devine invalid daca nu exista k precedenti
// sau arunca eroare daca k<=0}
// Daca (curent=NIL) sau (k<=0)
//		@arunca eroare
// SfDaca
// CatTimp (curent != NIL) si (k>0)
//		Daca (it.dict.st[it.curent] != NIL) atunci
//			curent<-it.dict.maxim(dict.st[curent])
//		Altfel
//			par<-it.dict.parinte[curent]
//			Daca (it.dict.dr[par]=curent) atunci
//				curent<-par
//			Altfel
//				curent<-NIL
//			SfDaca
//		SfDaca
//		k<-k-1
// SfCattimp
// SfSubalgoritm
// Complexitate:
//		caz favorabil: Theta(1) - iteratorul este pe primul element din container
//		caz defavorabil: Theta(adancime_arbore) - iteratorul este/ajunge sa fie pe un element
//						al carui anterior se afla la o adancime egalacu adancimea arborelui
//		complexitate generala: O(adancime_arbore)
void Iterator::revinoKPasi(int k)
{
	//arunca exceptie in cazul in care iteratorul este nevalid sau k este zero ori negativ
	if (curent == NIL || k <= 0)
	{
		throw std::exception();
	}
	while (curent != NIL && k > 0)
	{
		//verificam daca pozitia curenta indicata de iterator are subarbore stang
		if (dict.st[curent] != NIL)
		{
			curent = dict.maxim(dict.st[curent]);
		}
		else
		{
			auto parinte = dict.parinte[curent];
			while (parinte != NIL && dict.st[parinte] == curent)
			{
				curent = parinte;
				parinte = dict.parinte[parinte];
			}
			curent = parinte;
		}
		k--;
	}
}