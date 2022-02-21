#ifndef WORD_H_
#define WORD_H_
#include <iosfwd>
#include <string>
#include <algorithm>
#include <cctype>
#include <iterator>
#include <ostream>

namespace text {

class Word {
	mutable std::string word{""};
public:
	Word();
	explicit Word(std::string const);

	friend std::istream & operator>>(std::istream &, const Word &);

	friend std::ostream & operator<<(std::ostream &, const Word &);


	std::istream & write(std::istream &) const;
	std::ostream & read(std::ostream & os) const;

	//---- Operations ----

	bool operator==(const Word rhs) const{
		return this->compare(rhs) == 0;
	}

	bool operator!=(const Word rhs) const {
		return !(this->operator ==(rhs));
	}
	bool operator<(const Word rhs) const{
		return this->compare(rhs) < 0;
	}

	bool operator>(const Word rhs) const{
		return this->compare(rhs) > 0;
	}

	bool operator<=(const Word rhs) const {
		return this-operator<(rhs)  || this->operator==(rhs);
	}

	bool operator>=(const Word rhs) const {
		return this->operator>(rhs)  || this->operator==(rhs);
	}

	int compare(Word const w) const {
		return str2LowCase(this->word).compare(str2LowCase(w.word));
	}

private:
	bool wordvalidate(std::string);

	std::string str2LowCase(std::string str) const {
		std::transform(std::begin(str), std::end(str), std::begin(str), [](unsigned char c) {
			return std::tolower(c);
		});
		return str;
	}
};


}

#endif /* WORD_H_ */
