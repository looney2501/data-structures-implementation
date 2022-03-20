#pragma once

#define NULL_TELEM -1
typedef int TElem;

class IteratorMultime;

class Multime {
	friend class IteratorMultime;

private:
	/* aici e reprezentarea */
	int prim, prim_liber, capacitate, dimensiune, ultim;
	TElem* elemente;
	int* urmator, * precedent;

	void redimensionare();
	int aloca();
	void dealoca(int index);
	int creeaza_nod(TElem element);
	int cauta_nod(TElem element) const;

public:
	//constructorul implicit
	Multime();

	//adauga un element in multime
	//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
	bool adauga(TElem e);

	//sterge un element din multime
	//returneaza adevarat daca elementul a existat si a fost sters
	bool sterge(TElem e);

	//verifica daca un element se afla in multime
	bool cauta(TElem elem) const;

	//intoarce numarul de elemente din multime;
	int dim() const;

	//verifica daca multimea e vida;
	bool vida() const;

	//returneaza diferenta dintre valoarea maxima si cea minima (presupunem valori intregi)
	//daca multimea este vida, se returneaza -1
	int diferenta_max_min() const;

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	// destructorul multimii
	~Multime();
};
