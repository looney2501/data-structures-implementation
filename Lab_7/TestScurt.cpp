#include <assert.h>

#include "DO.h"
#include "Iterator.h"

#include <exception>
using namespace std;

bool relatie1(TCheie cheie1, TCheie cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll() {
	DO dictOrd = DO(relatie1);
	assert(dictOrd.dim() == 0);
	assert(dictOrd.vid());
	dictOrd.adauga(1, 2);
	assert(dictOrd.dim() == 1);
	assert(!dictOrd.vid());
	assert(dictOrd.cauta(1) != NULL_TVALOARE);
	TValoare v = dictOrd.adauga(1, 3);
	assert(v == 2);
	assert(dictOrd.cauta(1) == 3);
	Iterator it = dictOrd.iterator();
	it.prim();
	while (it.valid()) {
		TElem e = it.element();
		assert(e.second != NULL_TVALOARE);
		it.urmator();
	}
	assert(dictOrd.sterge(1) == 3);
	assert(dictOrd.vid());
}

void my_tests()
{
	DO d(relatie1);
	for (int i = 1; i <= 5; i++)
	{
		d.adauga(i, i);
	}
	auto it = d.iterator();
	for (int i = 1; i <= 4; i++)
		it.urmator();
	it.revinoKPasi(4);
	assert(it.element().first == 1);
	for (int i = 1; i <= 4; i++)
		it.urmator();
	it.revinoKPasi(5);
	assert(it.valid() == false);
	it.prim();
	for (int i = 1; i <= 4; i++)
		it.urmator();
	it.revinoKPasi(3);
	assert(it.element().first == 2);
	d.sterge(3);
	auto it2 = d.iterator();
	for (int i = 1; i <= 3; i++)
		it2.urmator();
	it2.revinoKPasi(3);
	assert(it2.element().first == 1);
	DO d2(relatie1);
	d2.adauga(3, 3);
	d2.adauga(1, 1);
	d2.adauga(2, 2);
	d2.adauga(5, 5);
	d2.adauga(4, 4);
	auto it3 = d2.iterator();
	for (int i = 1; i <= 4; i++)
		it3.urmator();
	it3.revinoKPasi(4);
	assert(it3.element().first == 1);
	for (int i = 1; i <= 4; i++)
		it3.urmator();
	it3.revinoKPasi(5);
	assert(it3.valid() == false);
}