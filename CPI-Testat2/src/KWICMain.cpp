//============================================================================
// Name        : KWICMain.cpp
// Author      : Isaac Würth
// Version     : 1.9
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "kwic.h"

#include <iostream>
#include <ostream>


using namespace std;

int main(int argc, char const *argv[]) {
	cout << "---- Input lines ----" << endl;
	text::kwic(cin, cout);
}
