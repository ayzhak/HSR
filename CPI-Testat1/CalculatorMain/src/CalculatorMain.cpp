#include "pocketcalculator.h"



#include <iostream>

using namespace std;

int main() {

	cout << "Pocketcalculator 4\n";
		/**
		 * Requirement from testat week4 section 1:
		 *  For the underlying calculation use your function calc().
		 *  Read the input line by line (std::getline()) and interpret
		 *  each line as a calculation (operand operator operand).
		 *  Expected signature: void pocketcalculator(std::istream &, std::ostream&)
		 */

	pocketcalculator(cin, cout);

	cout << "quit";

	return 0;
}
