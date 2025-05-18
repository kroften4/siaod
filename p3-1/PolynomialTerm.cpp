#include "PolynomialTerm.h"

PolynomialTerm::PolynomialTerm(float coefficient, int degree) : coefficient{coefficient}, degree{degree} {}

bool operator==(const PolynomialTerm &l, const PolynomialTerm &r) {
	return l.coefficient == r.coefficient && l.degree == r.degree;
}

bool operator!=(const PolynomialTerm &l, const PolynomialTerm &r) {
	return !(l == r);
}

std::ostream& operator<<(std::ostream& ost, const PolynomialTerm pt) {
	switch (pt.degree) {
	case 0:
		ost << pt.coefficient;
		break;
	case 1:
		ost << pt.coefficient << "*x";
		break;
	default:
		ost << pt.coefficient << "*x**" << pt.degree;
		break;
	}
	return ost;
}
