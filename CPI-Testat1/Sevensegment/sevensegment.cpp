#include "sevensegment.h"

#include <ostream>
#include <array>
#include <string>
#include <stdexcept>

#define ODD_SET " - "
#define NOT_SET "   "
#define EVEN_SET "| |"
#define EVEN_LEFT "|  "
#define EVEN_RIGHT "  |"
#define DIGITS_MAX 12
#define DIGIT_MINUS_SIGN 10
#define DIGIT_EMPTY 11
#define ASCII_NUMBER_OFFSET 48
#define SPACE_BETWEEN_NUMBERS " "

using namespace std;

const array<array<string, 5>, DIGITS_MAX > digits = {{
		{ ODD_SET, EVEN_SET, NOT_SET, EVEN_SET, ODD_SET },
		{ NOT_SET, EVEN_RIGHT, NOT_SET, EVEN_RIGHT, NOT_SET },
		{ ODD_SET, EVEN_RIGHT, ODD_SET, EVEN_LEFT, ODD_SET },
		{ ODD_SET, EVEN_RIGHT, ODD_SET, EVEN_RIGHT, ODD_SET },
		{ NOT_SET, EVEN_SET, ODD_SET, EVEN_RIGHT, NOT_SET },
		{ ODD_SET, EVEN_LEFT, ODD_SET, EVEN_RIGHT, ODD_SET },
		{ ODD_SET, EVEN_LEFT, ODD_SET, EVEN_SET, ODD_SET },
		{ ODD_SET, EVEN_RIGHT, NOT_SET, EVEN_RIGHT, NOT_SET },
		{ ODD_SET, EVEN_SET, ODD_SET, EVEN_SET, ODD_SET },
		{ ODD_SET, EVEN_SET, ODD_SET, EVEN_RIGHT, ODD_SET }, /* 10 =minus sing*/
		{ NOT_SET, NOT_SET, ODD_SET, NOT_SET, NOT_SET } /* 11 = empty digit */
	}};


static void addDigitToSevenSegment(int d, array<string, 5>& lines){
	for (auto i=0u; i<lines.size(); i++){
			lines.at(i).append(digits.at(d).at(i));
	}
}

static array<string, 5> numberToSevenSegment(int v){
	array<string, 5> lines;
	// Add minus sing
	if (v<0){
		addDigitToSevenSegment(DIGIT_MINUS_SIGN, lines);
		v=abs(v);
	}
	// Add numbers
	auto s = to_string(v);
	for (char c : s){
		addDigitToSevenSegment(c - ASCII_NUMBER_OFFSET, lines);
	}
	return lines;
}

static void printSevenSegment(array<string, 5>& lines, ostream& out){
	for (string line : lines){
		out << line << endl;
	}
}

void printLargeDigit(int i, ostream &out){
	if (i<0 || i>9) throw invalid_argument("Digit out of Range");
	array<string, 5> lines;
	addDigitToSevenSegment(i, lines);
	printSevenSegment(lines, out);
}


void printLargeNumber(int v, ostream & out) {
	array<string, 5> lines = numberToSevenSegment(v);
	printSevenSegment(lines, out);
}

void printLargeError(ostream & out) {
	out << " -             " << '\n';
	out << "|              " << '\n';
	out << " -  -  -  -  - " << '\n';
	out << "|  |  |  | ||  " << '\n';
	out << " -        -    " << endl;
}

