#include "MyTest.h"
#include "Multime.h"
#include "IteratorMultime.h"
#include <cassert>

void my_tests()
{
	Multime m;
	for (int i = 1; i <= 128; i++)
	{
		m.adauga(i);
		m.adauga(-i);
	}
	auto it = m.iterator();
	assert(it.valid() == true);
	while (it.valid())
	{
		TElem e = it.element();
		assert(m.cauta(e) == true);
		it.urmator();
	}
}