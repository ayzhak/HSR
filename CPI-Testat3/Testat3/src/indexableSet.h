#ifndef SRC_INDEXABLESET_H_
#define SRC_INDEXABLESET_H_


#include <cmath>
#include <functional>
#include <iterator>
#include <ostream>
#include <set>
#include <stdexcept>

template <typename T, typename COMPARE=std::less<T>>
class indexableSet : public std::set<T, COMPARE>{

	using container = std::set<T, COMPARE>;
	using container::container;
	using difference_type = typename container::difference_type;
	using size_type = typename container::size_type;
	using reference = typename container::reference;
	using const_reference = typename container::const_reference;

public:
	const_reference at(difference_type index) const
	{
		checkValidIndex(index);

		return *std::next(index >= 0 ? this->begin() : this->end(), index);
	}

	const_reference front() const
	{
		return this->at(0);
	}

	const_reference back() const
	{
		return this->at(-1);
	}

	const_reference operator[](difference_type index) const
	{
		return at(index);
	}

private:
	void checkValidIndex(difference_type index) const{
		// INT_MIN is -2147483648, but the would-be result 2147483648 is greater than INT_MAX, which is 2147483647.
		// https://en.cppreference.com/w/cpp/numeric/math/abs
		difference_type const imin = std::numeric_limits<difference_type>::min();
		difference_type const singedSize = static_cast<difference_type>(this->size());
		if(!(index < singedSize && std::abs(index) <= singedSize) || index == imin)
			throw std::out_of_range("Index is out of bound.");
	}
};

#endif /* SRC_INDEXABLESET_H_ */
