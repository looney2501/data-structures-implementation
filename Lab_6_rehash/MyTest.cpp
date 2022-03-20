#include "MyTest.h"
#include "Multime.h"
#include "IteratorMultime.h"
#include <cassert>

void my_tests()
{
	Multime a, b;
	a.adauga(1);
	assert(a.diferenta(b) == 0);
	b.adauga(1);
	assert(a.diferenta(b) == 1);
	assert(a.vida());
	a.adauga(1);
	b.sterge(1);
	assert(a.diferenta(b) == 0);
	for (int i = 1; i <= 32; i++)
	{
		a.adauga(i);
		b.adauga(i);
	}
	assert(a.diferenta(b) == 32);
	assert(a.vida());
	for (int i = 1; i <= 64; i++)
	{
		a.adauga(i);
	}
	b.adauga(100);
	assert(a.diferenta(b) == 32);
	for (int i = 33; i <= 64; i++)
	{
		assert(a.cauta(i));
	}
}