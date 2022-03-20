#include <iostream>

#include "TestExtins.h"
#include "TestScurt.h"
#include "Colectie.h"
#include <assert.h>

using namespace std;

void my_test()
{
	Colectie c;

	for (int i = -100; i < 100; i++) {
		c.adauga(i);
	}
	assert(c.dim() == 200);
	for (int i = -100; i < 100; i = i + 2) {
		assert(c.eliminaAparitii(1, i) == 1);
		assert(c.eliminaAparitii(1, i - 1000) == 0);
		assert(c.eliminaAparitii(1, i + 1000) == 0);
	}
	assert(c.dim() == 100);
	for (int i = -100; i < 100; i++) {
		if (i % 2 == 0) {
			assert(c.nrAparitii(i) == 0);
			assert(c.cauta(i) == false);
			assert(c.sterge(i) == false);
		}
		else {
			assert(c.nrAparitii(i) == 1);
			assert(c.cauta(i) == true);
		}
		c.adauga(i);
		c.adauga(i);
		c.adauga(i);
	}
	assert(c.dim() == 700);
	for (int i = -100; i < 100; i++)
	{
		if (i % 2 == 0)
		{
			assert(c.eliminaAparitii(4, i) == 3);
		}
		else
		{
			assert(c.eliminaAparitii(4, i) == 4);
		}
	}
	assert(c.dim() == 0);
}

int main() {
	/*5. TAD Colectie cu elemente de tip comparabil (TElement=TComparabil) – reprezentare folosind
	o LSI de perechi de forma (element, frecventa) ordonate în raport cu relatia de ordine
	<= intre elemente.
	*/
	testAllExtins();
	testAll();
	my_test();
}