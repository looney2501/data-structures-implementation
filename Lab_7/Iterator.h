#pragma once

#include "DO.h"

class Iterator {
	friend class DO;
private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	Iterator(const DO& dictionar);

	//contine o referinta catre containerul pe care il itereaza
	const DO& dict;

	int curent;

public:

	//reseteaza pozitia iteratorului la inceputul containerului
	void prim();

	//muta iteratorul in container
	//arunca exceptie daca iteratorul nu e valid
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	bool valid() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	TElem element() const;

	//muta cursorul iteratorului a.i. sa refere al k-lea element in urma, incepand de la cel curent. Iteratorul devine nevalid in cazul in
	//care exista mai putin de k elemente anterioare elementului curent in dictionar.
	//arunca exceptie in cazul in care iteratorul este nevalid sau k este zero ori negativ.
	void revinoKPasi(int k);
};
