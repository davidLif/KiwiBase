/*
 * DummyMain.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: david
 */

#include <iostream>
#include "KiwiPQ.h"

int main() {
	KiwiPQ * test = new KiwiPQ();
	test->insert(3,5);
	std::cout << "Hello World!" << std::endl;
	delete test;
	return 0;
}

