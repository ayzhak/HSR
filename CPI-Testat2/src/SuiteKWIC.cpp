#include "SuiteKWIC.h"
#include "cute.h"
#include "word.h"
#include "kwic.h"


#include <sstream>
#include <string>
#include <set>
#include <vector>


using namespace text;

void test_rotate(){
	text::RotateVectorWord vector(std::vector<text::Word> {text::Word{"Th"}, text::Word{"is"}});
	ASSERT_EQUAL(true, vector.rotate());

	std::vector<text::Word> expect{text::Word{"is"}, text::Word{"Th"}};
	ASSERT_EQUAL(expect, vector.value());

	expect = {text::Word{"Th"}, text::Word{"is"}};
	ASSERT_EQUAL(false, vector.rotate());
	ASSERT_EQUAL(expect, vector.value());
}


void test_rotate_4elements(){
	text::RotateVectorWord vector(std::vector<text::Word> {text::Word{"Th"}, text::Word{"is"}, text::Word{"aa"}, text::Word{"is"}});
	//First
	ASSERT_EQUAL(true, vector.rotate());
	std::vector<text::Word> expect{text::Word{"is"}, text::Word{"aa"}, text::Word{"is"}, text::Word{"Th"}};
	ASSERT_EQUAL(expect, vector.value());
	//Second
	ASSERT_EQUAL(true, vector.rotate());
	expect = {text::Word{"aa"}, text::Word{"is"}, text::Word{"Th"}, text::Word{"is"}};
	ASSERT_EQUAL(expect, vector.value());
	//Third
	ASSERT_EQUAL(true, vector.rotate());
	expect = {text::Word{"is"}, text::Word{"Th"}, text::Word{"is"}, text::Word{"aa"}};
	ASSERT_EQUAL(expect, vector.value());
	//Fourth
	ASSERT_EQUAL(false, vector.rotate());
	expect = {text::Word{"Th"}, text::Word{"is"}, text::Word{"aa"}, text::Word{"is"}};
	ASSERT_EQUAL(expect, vector.value());
}

void test_printPermutations(){
	std::istringstream expected{"abc \nefg \nhij \n"};
	std::ostringstream out{};

	std::multiset<std::vector<text::Word>, Comparator> input{};

	input.insert(std::vector<text::Word> {text::Word{"abc"}});
	input.insert(std::vector<text::Word> {text::Word{"efg"}});
	input.insert(std::vector<text::Word> {text::Word{"hij"}});

	text::printPermutations(input, out);


	ASSERT_EQUAL(expected.str(), out.str());
}

void test_printPermutations_mixed(){
	std::istringstream const expected { "abc \nefg \nhij \n" };
	std::ostringstream out{};

	std::multiset<std::vector<text::Word>, Comparator> input{};

	input.insert(std::vector<text::Word> {text::Word{"hij"}});
	input.insert(std::vector<text::Word> {text::Word{"efg"}});
	input.insert(std::vector<text::Word> {text::Word{"abc"}});

	text::printPermutations(input, out);

	ASSERT_EQUAL(expected.str(), out.str());
}


void test_parseToLinesWords(){
	std::istringstream input{"This\nTest\nTest"};

	std::multiset<std::vector<text::Word>> expected {
		std::vector<text::Word> {text::Word{"This"}},
		std::vector<text::Word> {text::Word{"Test"}},
		std::vector<text::Word> {text::Word{"Test"}}};

	ASSERT_EQUAL(expected, text::parseToLines(input));
}

void test_parseToLinesWords_WeirdInput(){
	std::istringstream input{"Th$$is\nTest\nTest"};

	std::multiset<std::vector<text::Word>> expected {
		std::vector<text::Word> {text::Word{"Th"}, text::Word{"is"}},
		std::vector<text::Word> {text::Word{"Test"}},
		std::vector<text::Word> {text::Word{"Test"}}};

	ASSERT_EQUAL(expected, text::parseToLines(input));
}


void test_parseToLinesWords_emptyLinesBetween(){
	std::istringstream input{"This\nTest\n\n\nTest"};

	std::multiset<std::vector<text::Word>> expected {
		std::vector<text::Word> {text::Word{"This"}},
		std::vector<text::Word> {text::Word{"Test"}},
		std::vector<text::Word> {text::Word{"Test"}}};

	ASSERT_EQUAL(expected, text::parseToLines(input));
}


void test_parseToLinesWords_EmptyInput(){
	std::istringstream input{""};

	ASSERT_EQUAL(true, text::parseToLines(input).empty());
}

void test_istream_to_vector_simpleLine(){
	std::istringstream input{"This Test .. Test"};
	std::vector<text::Word> expected {text::Word{"This"}, text::Word{"Test"}, text::Word{"Test"}};

	ASSERT_EQUAL(expected, text::parseLineToWords(input));
}

void test_simpleInput(){
	std::istringstream in{
			"a b c d \n"
			"a a b \n"
			"b b c \n"};

	std::ostringstream out{};

	text::kwic(in, out);

	 ASSERT_EQUAL(
			"a a b \n"
			"a b a \n"
			"a b c d \n"
			"b a a \n"
			"b b c \n"
			"b c b \n"
			"b c d a \n"
			"c b b \n"
			"c d a b \n"
			"d a b c \n", out.str());
}


void test_complexeInput(){
	std::istringstream in{
		"this is a test \n"
		"this is another test \n"};

	std::ostringstream out{};

	text::kwic(in, out);

	 ASSERT_EQUAL(
			 "a test this is \n"
			 "another test this is \n"
			 "is a test this \n"
			 "is another test this \n"
			 "test this is a \n"
			 "test this is another \n"
			 "this is a test \n"
			 "this is another test \n", out.str());
}


//Edge cases
void test_emptyInput(){
	std::istringstream in{""};

	std::ostringstream out{};

	text::kwic(in, out);

	 ASSERT_EQUAL("", out.str());
}

void test_twoEmptyLines(){
	std::istringstream in{"\n"};

	std::ostringstream out{};

	text::kwic(in, out);

	 ASSERT_EQUAL("", out.str());
}

void test_withUpperCase(){
	std::istringstream in{
		"this IS a test\n"
		"THIS is another TEST\n"};

	std::ostringstream out{};

	text::kwic(in, out);

	 ASSERT_EQUAL(
			 "a test this IS \n"
			 "another TEST THIS is \n"
			 "IS a test this \n"
			 "is another TEST THIS \n"
			 "test this IS a \n"
			 "TEST THIS is another \n"
			 "this IS a test \n"
			 "THIS is another TEST \n", out.str());
}

void test_withNonAlphabeticCharacter(){
	std::istringstream in{
		"this .........is....... ......... .....a -71729893764 $--.test\n"
		"this32456is1111another1test"};

	std::ostringstream out{};

	text::kwic(in, out);

	 ASSERT_EQUAL(
			 "a test this is \n"
			 "another test this is \n"
			 "is a test this \n"
			 "is another test this \n"
			 "test this is a \n"
			 "test this is another \n"
			 "this is a test \n"
			 "this is another test \n", out.str());
}

void test_contentWithEmptyLineBetween(){
	std::istringstream in{
		"this .........is....... ......... .....a -71729893764 $--.test\n"
		"\n"
		"this32456is1111another1test\n"};

	std::ostringstream out{};

	text::kwic(in, out);

	 ASSERT_EQUAL(
			 "a test this is \n"
			 "another test this is \n"
			 "is a test this \n"
			 "is another test this \n"
			 "test this is a \n"
			 "test this is another \n"
			 "this is a test \n"
			 "this is another test \n", out.str());
}

cute::suite make_suite_SuiteKWIC() {
	cute::suite s { };
	s.push_back(CUTE(test_contentWithEmptyLineBetween));
	s.push_back(CUTE(test_withNonAlphabeticCharacter));
	s.push_back(CUTE(test_withUpperCase));
	s.push_back(CUTE(test_twoEmptyLines));
	s.push_back(CUTE(test_emptyInput));
	s.push_back(CUTE(test_simpleInput));
	s.push_back(CUTE(test_complexeInput));
	s.push_back(CUTE(test_istream_to_vector_simpleLine));
	s.push_back(CUTE(test_parseToLinesWords));
	s.push_back(CUTE(test_parseToLinesWords_EmptyInput));
	s.push_back(CUTE(test_parseToLinesWords_WeirdInput));
	s.push_back(CUTE(test_rotate));
	s.push_back(CUTE(test_parseToLinesWords_emptyLinesBetween));
	s.push_back(CUTE(test_printPermutations));
	s.push_back(CUTE(test_printPermutations_mixed));
	s.push_back(CUTE(test_rotate_4elements));
	return s;
}
