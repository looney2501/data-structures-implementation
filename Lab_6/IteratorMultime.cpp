#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>

//complexitate generala - O(t_size-curent)
void IteratorMultime::deplasare()
{
	while (curent < multime.t_size && (multime.table[curent] == NIL || multime.table[curent] == STERS))
	{
		curent++;
	}
}

//complexitate generala - O(t_size)
IteratorMultime::IteratorMultime(const Multime& m) : multime(m) {
	curent = 0;
	deplasare();
}

//complexitate generala - O(t_size)
void IteratorMultime::prim() {
	curent = 0;
	deplasare();
}

//complexitate generala - O(t_size)
void IteratorMultime::urmator() {
	if (!valid())
	{
		throw std::exception();
	}
	curent++;
	deplasare();
}

//complexitate generala - Theta(1)
TElem IteratorMultime::element() const {
	if (!valid())
	{
		throw std::exception();
	}
	return multime.table[curent];
}

//complexitate generala - Theta(1)
bool IteratorMultime::valid() const {
	return curent < multime.t_size;
}