#include "cute.h"
#include "sevensegment.h"
#include "pocketcalculator.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "calc.h"
#include <sstream>

void testOnePlusOne() {
	auto result = calc(1, 1, '+');
	ASSERT_EQUAL(2, result);
}

void testTwoMinusOne() {
	auto result = calc(2, 1, '-');
	ASSERT_EQUAL(1, result);
}

void testFourTimesThree() {
	auto result = calc(4, 3, '*');
	ASSERT_EQUAL(12, result);
}

void testEightDevidedBy4() {
	auto result = calc(8, 4, '/');
	ASSERT_EQUAL(2, result);
}

void testTenModulo3() {
	auto result = calc(10, 3, '%');
	ASSERT_EQUAL(1, result);
}

void testCalcWithStream() {
	std::istringstream input { "95\n/\n5" };
	auto result = calc(input);
	ASSERT_EQUAL(19, result);
}
// sevensegment Tests
void test_printLargeDigit_5(){
	std::ostringstream out{};
	// std::istringstream in {"Input"};
	printLargeDigit(5, out);
	ASSERT_EQUAL(" - \n|  \n - \n  |\n - \n", out.str());
}
void test_printLargeDigit_underflow(){
	std::ostringstream out{};
	ASSERT_THROWS(printLargeDigit(-1, out), std::invalid_argument);
}
void test_printLargeDigit_overflow(){
	std::ostringstream out{};
	ASSERT_THROWS(printLargeDigit(10, out), std::invalid_argument);
}
void test_printLargeNumber_plus(){
	std::ostringstream out{};
	printLargeNumber(1234567890, out);
	ASSERT_EQUAL("    -  -     -  -  -  -  -  - \n  |  |  || ||  |    || || || |\n    -  -  -  -  -     -  -    \n  ||    |  |  || |  || |  || |\n    -  -     -  -     -  -  - \n" \
			, out.str());
}
void test_printLargeNumber_minus(){
	std::ostringstream out{};
	printLargeNumber(-1234567890, out);
	ASSERT_EQUAL("       -  -     -  -  -  -  -  - \n     |  |  || ||  |    || || || |\n -     -  -  -  -  -     -  -    \n     ||    |  |  || |  || |  || |\n       -  -     -  -     -  -  - \n" \
			, out.str());
}
void test_printLargeError(){
	std::ostringstream out{};
	printLargeError(out);
	ASSERT_EQUAL(	" -             \n|              \n -  -  -  -  - \n|  |  |  | ||  \n -        -    \n", out.str());
}


//Pocket Calculator
void pocketcalculator_emptyInput(){
	std::istringstream in{""};
	std::ostringstream out{};
	pocketcalculator(in, out);
	ASSERT_EQUAL("", out.str());
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };

	// Calculator Test
	s.push_back(CUTE(testOnePlusOne));
	s.push_back(CUTE(testTwoMinusOne));
	s.push_back(CUTE(testFourTimesThree));
	s.push_back(CUTE(testEightDevidedBy4));
	s.push_back(CUTE(testTenModulo3));
	s.push_back(CUTE(testCalcWithStream));

	// Sevensegment Test
	s.push_back(CUTE(test_printLargeDigit_5));
	s.push_back(CUTE(test_printLargeDigit_underflow));
	s.push_back(CUTE(test_printLargeDigit_overflow));
	s.push_back(CUTE(test_printLargeNumber_plus));
	s.push_back(CUTE(test_printLargeNumber_minus));
	s.push_back(CUTE(test_printLargeError));

	// Pocket Calculator Test
	s.push_back(CUTE(pocketcalculator_emptyInput));

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
	return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
