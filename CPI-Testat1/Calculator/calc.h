#ifndef CALC_H_
#define CALC_H_
#include <iosfwd>

int calc(int const lhs, int const rhs, char const op);
int calc(std::istream & in);

#endif /* CALC_H_ */
