#pragma once
#include "IteratorColectie.h"

class Nod;
class IteratorColectie;

typedef int TElem;
typedef bool(*Relatie)(TElem, TElem);
typedef Nod* Pnod;

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class Nod
{
	friend class Colectie;
private:
	//elementul
	TElem element;

	//frecventa sa
	int frecventa;

	//legatura catre urmatorul nod
	Pnod urmatorul;
public:
	//constructorul
	Nod(TElem element);

	//get element
	TElem get_element();

	//get frecventa
	int get_frecventa();

	//get urmator
	Pnod get_urmatorul();
};

class Colectie {
	friend class IteratorColectie;

private:
	/* aici e reprezentarea */

	//pointer catre primul nod
	Pnod primul;
public:
	//constructorul implicit
	Colectie();

	//adauga un element in colectie
	void adauga(TElem e);

	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	// elimina nr aparitii ale elementului elem. In cazul in care elementul apare mai putin de nr ori, toate aparitiile sale vor fi eliminate.
	// returneaza numarul de aparitii eliminate ale elementului.
	// arunca exceptie in cazul in care este nr este negativ.
	int eliminaAparitii(int nr, TElem elem);

	//verifica daca un element se afla in colectie
	bool cauta(TElem elem) const;

	//returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem) const;

	//intoarce numarul de elemente din colectie;
	int dim() const;

	//verifica daca colectia e vida;
	bool vida() const;

	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();
};
