#pragma once

#define NIL -2147483648
#define STERS 2147483647
typedef int TElem;

class IteratorMultime;

class Multime {
	friend class IteratorMultime;

private:
	int t_size;
	int n;
	TElem* table;
	const int hash_code(TElem e) const;
	const int d1(TElem e) const;
	const int d2(TElem e) const;
	const int d(TElem e, int i) const;
	const int cauta_poz(TElem e) const;
	const double load_factor() const;
	void rehash();

public:

	int diferenta(const Multime& b);

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

	//returneaza un iterator pe multime
	IteratorMultime iterator() const;

	// destructorul multimii
	~Multime();
};
