#include "kwic.h"

#include "word.h"

#include <istream>
#include <ostream>
#include <vector>
#include <set>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

using vecWord = std::vector<text::Word>;
using setVecWord = std::multiset<std::vector<text::Word>>;
using setVecWordComp = std::multiset<std::vector<text::Word>, text::Comparator>;

bool text::Comparator::operator()(const vecWord  & lhs,const vecWord & rhs) const {
	return lhs < rhs;
}

void text::kwic(std::istream & in, std::ostream & out) {
	setVecWordComp permutations{};
	setVecWord const set = text::parseToLines(in);
	text::createPermutation(set, permutations);

	text::printPermutations(permutations, out);
}

setVecWord text::parseToLines(std::istream & in) {
	setVecWord result{};
	std::istreambuf_iterator const isb_i { in };
	std::string line{};
	while(std::getline(in, line)){
		std::istringstream iline{line};
		vecWord const lineAsWords = text::parseLineToWords(iline);
		if(lineAsWords.capacity() != 0) result.insert(lineAsWords); // Removes empty lines
	}
	return result;
}


vecWord text::parseLineToWords(std::istream & in){
	vecWord vec{};
	text::Word emptyWord { };

	while(in.good()) {
		text::Word w { };
		in >> w;
		if(w != emptyWord) {
			vec.push_back(w);
		}
	}

	return vec;
}

setVecWordComp text::createPermutation(setVecWord list, setVecWordComp & permutations){
	for_each(begin(list), end(list), [&permutations](vecWord vec) mutable {
		text::RotateVectorWord rotator(vec);
		do {
			auto const val = rotator.value();
			permutations.insert(rotator.value());
		} while(rotator.rotate());
	});

	return permutations;
}

void text::printPermutations(setVecWordComp set, std::ostream & out){
	std::ostream_iterator<text::Word> const iter{out, " "};
	for_each(begin(set), end(set), [&iter,&out](vecWord vec){
		copy(vec.begin(), vec.end(), iter);
		out << "\n";
	});
}
