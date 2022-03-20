#include "Colectie.h"
#include <deque>

using namespace std;

bool rel(TElem e1, TElem e2) {
	if (e1 <= e2)
		return true;
	return false;
}

void Colectie::redim()
{
	//creare vector de capacitate dubla si copiere elemente din vechiul vector
	capacitate *= 2;
	TElem* vector_nou = new TElem[capacitate];
	for (int i = 0; i < dimensiune; i++)
		vector_nou[i] = vector[i];

	//distrugere vector vechi
	delete[] vector;
	vector = vector_nou;
}

//complexitate timp theta(1)
Colectie::Colectie() {
	capacitate = 1;
	dimensiune = 0;
	vector = new TElem[capacitate];
}

//complexitate timp O(n)
void Colectie::adauga(TElem e) {
	//daca nu mai este loc in vector, redimensioneaza
	if (dimensiune == capacitate)
		redim();

	//daca elementul e mai mare decat toate celelalte elemente, locul lui e pe vector[dimensiune]
	if (dimensiune != 0 && rel(e, vector[dimensiune - 1]) == false)
	{
		vector[dimensiune] = e;
		dimensiune++;
	}
	else
	{
		//pune elementul la locul lui
		int i = dimensiune;
		while (i > 0 && rel(vector[i - 1], e) == false)
		{
			vector[i] = vector[i - 1];
			i--;
		}
		vector[i] = e;
		dimensiune++;
	}
}

//complexitate timp O(n)
bool Colectie::sterge(TElem e) {
	//daca dimensiunea e 0, nu se poate sterge nimic
	if (dimensiune == 0)
		return false;

	//daca e este mai mare sau mai mic decat toate celelalte elemente, inseamna ca el nu exista
	if (rel(vector[0], e) == false || rel(e, vector[dimensiune - 1]) == false)
		return false;

	//daca e = vector[dimensiune-1] se face stergerea logica prin decrementarea dimensiunii
	if (rel(e, vector[dimensiune - 1]) == true && rel(vector[dimensiune - 1], e) == true)
	{
		dimensiune--;
		return true;
	}

	//cauta elementul e in vector
	int i = 0;
	while (i < dimensiune - 1 && rel(e, vector[i]) == false)
		i++;

	//elementul nu exista
	if (i == dimensiune - 1 || rel(vector[i], e) == false)
		return false;

	//daca i < dimensiune - 1, se va realiza stergerea logica
	while (i < dimensiune - 1)
	{
		vector[i] = vector[i + 1];
		i++;
	}
	dimensiune--;
	return true;
}

//complexitate timp O(logn)
bool Colectie::cauta(TElem e) const {
	//daca dimensiunea e 0
	if (dimensiune == 0)
		return false;

	//daca e este mai mare sau mai mic decat toate celelalte elemente, inseamna ca el nu exista
	if (rel(vector[0], e) == false || rel(e, vector[dimensiune - 1]) == false)
		return false;

	//cautare binara
	int left = 0, right = dimensiune - 1;
	while (left <= right)
	{
		int m = (right + left) / 2;
		if (rel(vector[m], e) == true && rel(e, vector[m]) == true)
		{
			return true;
		}
		if (rel(e, vector[m]))
		{
			right = m - 1;
		}
		else
		{
			left = m + 1;
		}
	}
	return false;
}

//complexitate timp O(n)
int Colectie::nrAparitii(TElem e) const {
	//daca dimensiunea e 0
	if (dimensiune == 0)
		return 0;

	//daca e este mai mare sau mai mic decat toate celelalte elemente, inseamna ca el nu exista
	if (rel(vector[0], e) == false || rel(e, vector[dimensiune - 1]) == false)
		return 0;

	//numarare aparitii
	int aparitii = 0;
	for (int i = 0; i < dimensiune; i++)
	{
		if (rel(vector[i], e) == true && rel(e, vector[i]) == true)
		{
			aparitii++;
		}
	}
	return aparitii;
}

//complexitate timp theta(1)
int Colectie::dim() const {
	return dimensiune;
	return 0;
}

//complexitate timp theta(1)
bool Colectie::vida() const {
	if (dimensiune != 0)
		return false;
	return true;
}

//complexitate timp theta(1)
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}

//complexitate timp theta(1)
Colectie::~Colectie() {
	delete[] vector;
}