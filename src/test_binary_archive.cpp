#include "test_binary_archive.h"
#include <iostream>

using namespace std;

int main()
{
	test_binary_archive tba;
	// if any test failed, it will cause an assert error
	tba.run_test();
	cout << "all test success" << endl;
	return 0;
}