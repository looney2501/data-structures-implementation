#include <iostream>

#include "TestScurt.h"
#include "TestExtins.h"

int main() {
	//TAD Dictionar Ordonat – reprezentare sub forma unui ABC reprezentat inlantuit, cu inlantuiri reprezentate pe tablou.
	testAll();
	testAllExtins();
	my_tests();
	std::cout << "Finished Tests!" << std::endl;
	_CrtDumpMemoryLeaks();
}