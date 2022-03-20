#pragma once

typedef int TCheie;
typedef int TValoare;

#define NULL_TVALOARE -10000000
#define NIL -1

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Iterator;

typedef bool(*Relatie)(TCheie, TCheie);

class DO {
	friend class Iterator;
private:
	int radacina, prim_liber, capacitate, dimensiune;
	TElem* elemente;
	int* urmator, * parinte, * st, * dr;
	Relatie r;

	void redimensionare();
	int aloca();
	void dealoca(int index);
	int creeaza_nod(TElem element);
	void cauta_nod(TCheie c, int& poz, int& par) const;
	int minim(int p) const;
	int maxim(int p) const;
	int sterge_rec(int p, TElem e);

public:

	// constructorul implicit al dictionarului
	DO(Relatie r);

	// adauga o pereche (cheie, valoare) in dictionar
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	TValoare cauta(TCheie c) const;

	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar
	int dim() const;

	//verifica daca dictionarul e vid
	bool vid() const;

	// se returneaza iterator pe dictionar
	// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
	Iterator iterator() const;

	// destructorul dictionarului
	~DO();
};
