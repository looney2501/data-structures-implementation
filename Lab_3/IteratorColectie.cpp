#include "IteratorColectie.h"
#include "Colectie.h"
#include <exception>

//complexitate theta(1)
IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	/* de adaugat */
	curent = col.primul;
}

//complexitate theta(1)
TElem IteratorColectie::element() const {
	/* de adaugat */
	if (this->valid() == true)
		return curent->get_element();
	throw _exception();
}

//complexitate theta(1)
bool IteratorColectie::valid() const {
	if (curent != nullptr)
		return true;
	return false;
}

//complexitate theta(1)
void IteratorColectie::urmator() {
	/* de adaugat */
	curent = curent->get_urmatorul();
}

//complexitate theta(1)
void IteratorColectie::prim() {
	curent = col.primul;
}