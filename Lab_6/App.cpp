#include "TestExtins.h"
#include "TestScurt.h"
#include "MyTest.h"
#include <iostream>
using namespace std;

int main() {
	testAll();
	testAllExtins();

	my_tests();

	cout << "That's all!" << endl;
	_CrtDumpMemoryLeaks();
}