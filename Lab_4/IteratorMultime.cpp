#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>

//complexitate Theta(1)
IteratorMultime::IteratorMultime(const Multime& m) : multime(m) {
	curent = m.prim;
}

//complexitate Theta(1)
void IteratorMultime::prim() {
	curent = multime.prim;
}

//complexitate Theta(1)
void IteratorMultime::urmator() {
	if (!valid())
		throw std::exception();
	curent = multime.urmator[curent];
}

//complexitate Theta(1)
TElem IteratorMultime::element() const {
	if (!valid())
		throw std::exception();
	return multime.elemente[curent];
}

//complexitate Theta(1)
bool IteratorMultime::valid() const {
	if (curent != -1)
		return true;
	return false;
}