#ifndef SRC_KWIC_H_
#define SRC_KWIC_H_

#include "word.h"

#include <iosfwd>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>

namespace text {



class RotateVectorWord {

	std::vector<text::Word> vector{};
	int left{};

public:
	explicit RotateVectorWord(std::vector<text::Word> const vec) : vector(vec), left(vector.size()) {}

	bool rotate(){
		std::rotate(begin(this->vector), begin(vector) + 1, end(this->vector));
		return --left != 0;
	}

	std::vector<text::Word> value() const {
		return this->vector;
	}
};

struct Comparator {
	bool operator()(const std::vector<text::Word>  & lhs, const std::vector<text::Word>  & rhs) const;
};


void kwic(std::istream & in, std::ostream & out);

std::multiset<std::vector<text::Word>> parseToLines(std::istream & in);
std::vector<text::Word> parseLineToWords(std::istream & in);
void printPermutations(std::multiset<std::vector<text::Word>, Comparator> set, std::ostream & out);
std::multiset<std::vector<text::Word>, text::Comparator> createPermutation(std::multiset<std::vector<text::Word>> list, std::multiset<std::vector<text::Word>, text::Comparator> &);
}

#endif /* SRC_KWIC_H_ */
