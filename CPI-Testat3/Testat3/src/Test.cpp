#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "indexableSet.h"

#include <algorithm>

#include <iostream>
#include <limits>
#include <ostream>
#include <string>
#include <cstring>


void test_singleElement_empty() {
	indexableSet<int> const iset {};
	ASSERT_THROWS(iset.at(0), std::out_of_range);
}

void test_singleElement_positiveIndex() {
	indexableSet<int> const iset { 1 };
	ASSERT_EQUAL(1, iset.at(0));
}

void test_singleElement_negativeIndex() {
	indexableSet<int> const iset { 1 };
	ASSERT_EQUAL(1, iset.at(-1));
}

void test_singleElement_exception_negativeIndex() {
	indexableSet<int> const iset { 1 };
	ASSERT_THROWS(iset.at(-2), std::out_of_range);
}

void test_singleElement_exception_positiveIndex() {
	indexableSet<int> const iset { 1 };
	ASSERT_THROWS(iset.at(2), std::out_of_range);
}

void test_multipleElement_positiveIndex() {
	indexableSet<int> const iset { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ASSERT_EQUAL(1, iset.at(0));
	ASSERT_EQUAL(2, iset.at(1));
	ASSERT_EQUAL(3, iset.at(2));
	ASSERT_EQUAL(4, iset.at(3));
	ASSERT_EQUAL(5, iset.at(4));
	ASSERT_EQUAL(6, iset.at(5));
	ASSERT_EQUAL(7, iset.at(6));
	ASSERT_EQUAL(8, iset.at(7));
	ASSERT_EQUAL(9, iset.at(8));
}

void test_multipleElement_negativeIndex() {
	indexableSet<int> const iset { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ASSERT_EQUAL(9, iset.at(-1));
	ASSERT_EQUAL(8, iset.at(-2));
	ASSERT_EQUAL(7, iset.at(-3));
	ASSERT_EQUAL(6, iset.at(-4));
	ASSERT_EQUAL(5, iset.at(-5));
	ASSERT_EQUAL(4, iset.at(-6));
	ASSERT_EQUAL(3, iset.at(-7));
	ASSERT_EQUAL(2, iset.at(-8));
	ASSERT_EQUAL(1, iset.at(-9));
}

void test_multipleElement_exception_negativeIndex() {
	indexableSet<int> const iset { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ASSERT_THROWS(iset.at(-10), std::out_of_range);
}

void test_multipleElement_exception_positiveIndex() {
	indexableSet<int> const iset { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ASSERT_THROWS(iset.at(9), std::out_of_range);
}

void test_multipleElement_front() {
	indexableSet<int> const iset { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	ASSERT_EQUAL(1, iset.front());
}

void test_multipleElement_back() {
	indexableSet<int> const iset{1,2,3,4,5,6,7,8,9};
	ASSERT_EQUAL(9, iset.back());
}

void test_multipleElement_back_equal_back() {
	indexableSet<int> const iset{1,2,3,4,5,6,7,8,9};
	ASSERT_EQUAL(iset.back(), iset.back());
}

void test_multipleElement_back_equal_at() {
	indexableSet<int> const iset{1,2,3,4,5,6,7,8,9};
	ASSERT_EQUAL(iset.at(8), iset.back());
}

void test_multipleElement_back_equal_front() {
	indexableSet<int> const iset{1};
	ASSERT_EQUAL(&iset.front(), &iset.back());
}

void test_singleElement_MAX_INT(){
	int const imax = std::numeric_limits<int>::max();
	indexableSet<int> const iset { 1 };
	ASSERT_THROWS(iset.at(imax), std::out_of_range);
}

void test_singleElement_MIN_INT(){
	int const imin = std::numeric_limits<int>::min();
	indexableSet<int> const iset { 1 };

	ASSERT_THROWS(iset.at(imin), std::out_of_range);
}


void test_singleElement_TEST_UINT16(){
	uint16_t const imax = std::numeric_limits<uint16_t>::max();
	indexableSet<uint16_t> iset {};

	for (uint16_t i = 0; i < imax; ++i) {
		iset.insert(i);
	}

	ASSERT_THROWS(iset.at(imax), std::out_of_range);
}

struct caselessCompare {
    bool operator () (std::string lhs, std::string rhs) const {
    	std::transform(lhs.begin(), lhs.end(), lhs.begin(),
    	    [](unsigned char c){ return std::tolower(c); });
    	
    	std::transform(rhs.begin(), rhs.end(), rhs.begin(),
    	    	    [](unsigned char c){ return std::tolower(c); });
    	
    	return lhs < rhs;
    }
};

void test_singleElement_CASELESS_COMPARE(){
	indexableSet<std::string, caselessCompare> iset {"cc", "CA", "AB", "aa"};

	ASSERT_EQUAL("aa", iset[0]);
	ASSERT_EQUAL("AB", iset[1]);
	ASSERT_EQUAL("CA", iset[2]);
	ASSERT_EQUAL("cc", iset[3]);

}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };
	s.push_back(CUTE(test_singleElement_positiveIndex));
	s.push_back(CUTE(test_singleElement_negativeIndex));
	s.push_back(CUTE(test_singleElement_exception_negativeIndex));
	s.push_back(CUTE(test_singleElement_exception_positiveIndex));
	s.push_back(CUTE(test_multipleElement_positiveIndex));
	s.push_back(CUTE(test_multipleElement_negativeIndex));
	s.push_back(CUTE(test_multipleElement_exception_negativeIndex));
	s.push_back(CUTE(test_multipleElement_exception_positiveIndex));
	s.push_back(CUTE(test_multipleElement_front));
	s.push_back(CUTE(test_multipleElement_back));
	s.push_back(CUTE(test_multipleElement_back_equal_back));
	s.push_back(CUTE(test_multipleElement_back_equal_at));
	s.push_back(CUTE(test_multipleElement_back_equal_front));
	s.push_back(CUTE(test_singleElement_MAX_INT));
	s.push_back(CUTE(test_singleElement_MIN_INT));
	s.push_back(CUTE(test_singleElement_TEST_UINT16));
	s.push_back(CUTE(test_singleElement_empty));
	s.push_back(CUTE(test_singleElement_CASELESS_COMPARE));

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto const runner = cute::makeRunner(lis, argc, argv);
	bool const success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
