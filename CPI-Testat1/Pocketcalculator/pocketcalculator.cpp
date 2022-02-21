#include "pocketcalculator.h"
#include "calc.h"
#include "sevensegment.h"

#include <ostream>
#include <istream>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

void pocketcalculator(std::istream &in, std::ostream &out) {

	string line;

	while(in.good() && getline(in, line)){
		istringstream lineStream{line};
		try {
			int const result = calc(lineStream);
			printLargeNumber(result, out);
		} catch (std::invalid_argument const& e) {
			printLargeError(out);
		}
	};
}
