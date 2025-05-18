#ifndef __POLYNOMAILTERM_H__
#define __POLYNOMAILTERM_H__

#include <iostream>

class PolynomialTerm {
public:
	float coefficient;
	int degree;
	
	PolynomialTerm(float coefficient, int degree);

	friend bool operator==(const PolynomialTerm &l, const PolynomialTerm &r);

	friend bool operator!=(const PolynomialTerm &l, const PolynomialTerm &r);

	friend std::ostream& operator<<(std::ostream& ost, const PolynomialTerm pt);
};

#endif // __POLYNOMAILTERM_H__

