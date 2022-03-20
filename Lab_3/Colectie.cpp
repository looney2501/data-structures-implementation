#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>
#include <exception>

using namespace std;

bool rel(TElem e1, TElem e2) {
	/* de adaugat */
	if (e1 <= e2)
		return true;
	return false;
}

//complexitate Theta(1)
Nod::Nod(TElem element)
{
	this->element = element;
	this->frecventa = 1;
	this->urmatorul = nullptr;
}

//complexitate Theta(1)
TElem Nod::get_element()
{
	return element;
}

//complexitate Theta(1)
int Nod::get_frecventa()
{
	return frecventa;
}

//complexitate Theta(1)
Pnod Nod::get_urmatorul()
{
	return urmatorul;
}

//complexitate Theta(1)
Colectie::Colectie() {
	/* de adaugat */
	this->primul = nullptr;
}

//complexitate O(n)
void Colectie::adauga(TElem e) {
	/* de adaugat */

	//daca lista e goala sau daca elementul e mai mic decat toate celelalte (caz favorabil) - Theta(1)
	if (this->primul == nullptr || rel(primul->element, e) == false)
	{
		Pnod nod_nou = new Nod(e);
		nod_nou->urmatorul = primul;
		primul = nod_nou;
	}
	//se cauta locul elementului in lista in functie de relatia de ordine - O(n)
	else
	{
		Pnod nod_curent = primul;
		Pnod nod_anterior = nullptr;
		bool gasit = false;
		while (nod_curent != nullptr && rel(nod_curent->element, e)==true && gasit==false)
		{
			if(nod_curent->element== e)
			{
				gasit = true;
			}
			else
			{
			nod_anterior = nod_curent;
			nod_curent = nod_curent->urmatorul;
			}
		}
		//daca e este mai mare decat toate celelalte din lista, se adauga la sfarsit
		if (nod_curent == nullptr)
		{
			Pnod nod_nou = new Nod(e);
			nod_nou->urmatorul = nullptr;
			nod_anterior->urmatorul = nod_nou;
		}
		else
		{
			//daca elementul este egal cu elementul din nodul curent, se incrementeaza frecventa acestuia
			if (nod_curent->element == e)
			{
				nod_curent->frecventa++;
			}
			//daca e nu este in lista, dar lista mai are elemente, se adauga intre nod anterior si nod curent
			else
			{
				Pnod nod_nou = new Nod(e);
				nod_nou->urmatorul = nod_curent;
				nod_anterior->urmatorul = nod_nou;
			}
		}
	}
}

//complexitate O(n)
bool Colectie::sterge(TElem e) {
	//daca nu exista niciun element in lista sau daca primul element e mai mare decat e, returneaza fals - Theta(1)
	if (this->primul == nullptr || rel(primul->element, e) == false)
	{
		return false;
	}
	//daca elementul se afla pe prima pozitie
	if (primul->element == e)
	{
		primul->frecventa--;
		if (primul->frecventa == 0)
		{
			Pnod q = primul;
			primul = primul->urmatorul;
			delete q;
		}
		return true;
	}

	//altfel, cauta elementul in lista de la al doilea element la final- O(n)
	Pnod nod_curent = primul;
	Pnod nod_anterior = nullptr;
	while (nod_curent != nullptr && rel(e, nod_curent->element) == false)
	{
		nod_anterior = nod_curent;
		nod_curent = nod_curent->urmatorul;
	}
	//elementul e mai mare decat toate celelalte
	if (nod_curent == nullptr)
		return false;
	//daca elementul este egal cu elementul din nodul curent, se decrementeaza frecventa acestuia
	if (nod_curent->element == e)
	{
		nod_curent->frecventa--;
		//daca noua frecventa e 0, se elimina nodul din lista
		if (nod_curent->frecventa == 0)
		{
			nod_anterior->urmatorul = nod_curent->urmatorul;
			nod_curent->urmatorul = nullptr;
			delete nod_curent;
		}
		return true;
	}
	return false;
}

/*caz favorabil - elementul e pe prima pozitie - theta(1)
caz defavorabil - elementul e mai mare decat toate celelalte elemenete - theta(n)
complexitate totala - O(n)
precizare!!! - n nu e numarul de elemenente, ci numarul de elemenete distincte!

Pseudocod:
	Subalgoritm eliminaAparitii(c, nr, e)
		{pre: c - Colectie, nr - intreg pozitiv, e - TElem}
		{post: se sterg nr aparitii ale elementului e din c, pastrand relatia de ordine R}
		{@arunca exceptie daca nr e negativ}
		Daca (nr < 0) atunci
			@arunca exceptie
		SfDaca
		Daca (c.primul == NIL) || not([c.primul].element R e) atunci
			eliminaAparitii(c, nr, e) <- 0
		SfDaca
		Daca ([c.primul].element == e) atunci
			Daca [c.primul].frecventa <= nr atunci
				elem_sterse <- [c.primul].frecventa
				q <- c.primul
				c.primul <- [c.primul].urmatorul
				{se sterge nodul q}
			altfel
				elem_sterse <- nr
				([c.primul].frecventa)' <- [c.primul].frecventa - nr
			SfDaca
			eliminaAparitii(c, nr, e) <- elem_sterse
		SfDaca
		nod_curent <- c.primul
		nod_anterior <- NIL
		CatTimp (nod_curent != NIL && not([nod_curent].element R e))
			nod_anterior <- nod_curent
			nod_curent <- [nod_curent].urmatorul
		SfCatTimp
		Daca (nod_curent == NIL)
			eliminaAparitii(c, nr, e) <- 0
		SfDaca
		Daca ([nod_curent].element == e) atunci
			Daca ([nod_curent].frecventa <= nr)
				elem_sterse <- [nod_curent].frecventa
				[nod_anterior].urmatorul <- [nod_curent].urmatorul
				{se sterge nodul nod_curent}
			altfel
				elem_sterse <- nr
				([nod_curent].frecventa)' <- [nod_curent].frecventa - nr
			SfDaca
			eliminaAparitii(c, nr, e) <- elem_sterse
		SfDaca
		eliminaAparitii(c, nr, e) <- 0

*/
int Colectie::eliminaAparitii(int nr, TElem e)
{
	//daca nr e negativ, arunca exceptie
	if (nr < 0)
		throw _exception();
	//daca nu exista niciun element in lista sau daca primul element e mai mare decat e, returneaza 0 - Theta(1)
	if (this->primul == nullptr || rel(primul->element, e) == false)
	{
		return 0;
	}
	//daca elementul se afla pe prima pozitie
	if (primul->element == e)
	{
		int elem_sterse;
		//daca nr>=frecventa, sterge nodul din lista
		if (primul->frecventa <= nr)
		{
			elem_sterse = primul->frecventa;
			Pnod q = primul;
			primul = primul->urmatorul;
			delete q;
		}
		//altfel, scade nr din frecventa
		else
		{
			elem_sterse = nr;
			primul->frecventa -= nr;
		}
		return elem_sterse;
	}

	//altfel, cauta elementul in lista de la al doilea element la final- O(n)
	Pnod nod_curent = primul;
	Pnod nod_anterior = nullptr;
	while (nod_curent != nullptr && rel(e, nod_curent->element) == false)
	{
		nod_anterior = nod_curent;
		nod_curent = nod_curent->urmatorul;
	}
	//elementul e mai mare decat toate celelalte
	if (nod_curent == nullptr)
		return 0;
	//daca elementul este egal cu elementul din nodul curent, se decrementeaza frecventa acestuia
	if (nod_curent->element == e)
	{
		int elem_sterse;
		//daca nr>=frecventa, sterge nodul din lista
		if (nod_curent->frecventa <= nr)
		{
			elem_sterse = nod_curent->frecventa;
			nod_anterior->urmatorul = nod_curent->urmatorul;
			nod_curent->urmatorul = nullptr;
			delete nod_curent;
		}
		//altfel, scade nr din frecventa
		else
		{
			elem_sterse = nr;
			nod_curent->frecventa -= nr;
		}
		return elem_sterse;
	}
	return 0;
}

//complexitate O(n)
bool Colectie::cauta(TElem e) const {
	//daca nu exista niciun element in lista sau daca primul element e mai mare decat e, returneaza fals - Theta(1)
	if (this->primul == nullptr || rel(primul->element, e) == false)
	{
		return false;
	}
	//altfel, cauta elementul in lista
	Pnod nod_curent = primul;
	while (nod_curent->urmatorul != nullptr && rel(e, nod_curent->element) == false)
	{
		nod_curent = nod_curent->urmatorul;
	}
	//daca elementul este egal cu elementul din nodul curent, se retruneaza true
	if (nod_curent->element == e)
	{
		return true;
	}
	return false;
}

//complexitate O(n)
int Colectie::nrAparitii(TElem e) const {
	//daca nu exista niciun element in lista sau daca primul element e mai mare decat e, returneaza 0 - Theta(1)
	if (this->primul == nullptr || rel(primul->element, e) == false)
	{
		return 0;
	}
	//altfel, cauta elementul in lista
	Pnod nod_curent = primul;
	while (nod_curent->urmatorul != nullptr && rel(e, nod_curent->element) == false)
	{
		nod_curent = nod_curent->urmatorul;
	}
	//daca elementul este egal cu elementul din nodul curent, se retruneaza frecventa acestuia
	if (nod_curent->element == e)
	{
		return nod_curent->frecventa;
	}
	return 0;
}

//complexitate theta(n)
int Colectie::dim() const {
	//daca nu exista noduri in lista, returneaza 0
	if (primul == nullptr)
		return 0;
	int dimn = 0;
	Pnod nod_curent = primul;
	while (nod_curent != nullptr)
	{
		dimn += nod_curent->frecventa;
		nod_curent = nod_curent->urmatorul;
	}
	return dimn;
}

//complexitate theta(1)
bool Colectie::vida() const {
	/* de adaugat */
	if (primul == nullptr)
		return true;
	return false;
}

//complexitate theta(1)
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

//complexitate theta(n)
Colectie::~Colectie() {
	Pnod nod_anterior = primul;
	while (primul != nullptr)
	{
		primul = primul->urmatorul;
		nod_anterior->urmatorul = nullptr;
		delete nod_anterior;
		nod_anterior = primul;
	}
}