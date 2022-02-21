#include "word.h"

#include <string>
#include <istream>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <iterator>
#include <sstream>
#include <stdexcept>



namespace text {
/**
 * Modifiction of for_each with prediction
 */

template<typename _InputIterator, typename _Function, class _Pr>
_Function for_each_until(_InputIterator __first, _InputIterator __last, _Function __f, _Pr _Pred) {
	// concept requirements
	__glibcxx_function_requires(_InputIteratorConcept<_InputIterator>)
	__glibcxx_requires_valid_range(__first, __last);
	for (; __first != __last; ++__first) {
		if (_Pred(*__first))
			break;
		__f(*__first);
	}
	return __f; // N.B. [alg.foreach] says std::move(f) but it's redundant.
}
Word::Word(){}

Word::Word(std::string const str) {

	if(str == "") throw std::invalid_argument("Empty string");

	std::istringstream is (str);
	using input = std::istreambuf_iterator<char>;
	input s{is};
	input eof{};

	std::istreambuf_iterator<char> const i = std::find_if(s, eof, [](char c) {
		return !std::isalpha(c);
	});
	if(!i.equal(eof)) throw std::invalid_argument("string can only contain alpha");
	this->word = str;
}

std::istream & Word::write(std::istream & is) const {
	if(is.fail()) return is;
	using input = std::istreambuf_iterator<char>;
	input s{is};
	input eof{};

	std::istreambuf_iterator<char> const i = std::find_if(s, eof, [](char c) {
		return std::isalpha(c);
	});
	if(i.equal(eof)) {
		is.setstate(std::istream::failbit);
		return is;
	}
	this->word.clear();

	//Modifizierte Version von for_each mit Predicition
	text::for_each_until(s, eof, [this](auto c) {this->word += c;} , [](char c) { return !std::isalpha(c);});
	return is;
}

std::ostream & Word::read(std::ostream & os) const {
	os << this->word;
	return os;
}



std::istream & operator>>(std::istream & lhs, const Word & rhs) {
	return rhs.write(lhs);
}

std::ostream & operator<<(std::ostream & lhs, const Word & rhs) {
	return rhs.read(lhs);
}

}
