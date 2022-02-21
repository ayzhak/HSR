#include "calc.h"
#include <stdexcept>
#include <istream>

int calc(int const lhs, int const rhs, char const op) {
	if((op == '%' || op == '/') && rhs == 0)
		throw std::invalid_argument{"devision by 0"};

	switch(op) {
		case '+':
			return lhs + rhs;
		case '-':
			return lhs - rhs;
		case '*':
			return lhs * rhs;
		case '/':
			return lhs / rhs;
		case '%':
			return lhs % rhs;
		default:
			throw std::invalid_argument{"unknown argument"};
	 }
	 return 0;
}


int calc(std::istream& in){
	int lhs{0};
	int rhs{0};
	char op{};

	if(in >> lhs >> op >> rhs){
		return calc(lhs, rhs, op);
	} else {
		throw std::invalid_argument{"input doesn't match parsing rules"};
	}

	return 0;
}
