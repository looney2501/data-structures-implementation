#include "IteratorColectie.h"
#include <exception>

//complexitate timp theta(1)
IteratorColectie::IteratorColectie(const Colectie& c) : col(c)
{
	pozitie = 0;
}

//complexitate timp theta(1)
TElem IteratorColectie::element() const {
	if (this->valid() == false)
	{
		throw std::exception("Iterator invalid!");
	}
	return col.vector[pozitie];
}

//complexitate timp theta(1)
bool IteratorColectie::valid() const {
	if (pozitie < col.dimensiune)
		return true;
	return false;
}

//complexitate timp theta(1)
void IteratorColectie::urmator() {
	if (this->valid() == false)
	{
		throw std::exception("Iterator invalid!");
	}
	pozitie++;
}

//complexitate timp theta(1)
void IteratorColectie::prim() {
	pozitie = 0;
}