#include <iostream>
#include <vector>
#include "PolynomialTerm.h"
#include "LinkedList.h"

// #define NDEBUG
#include <cassert>

std::ostream& operator<<(std::ostream& ost, LinkedList<PolynomialTerm> list) {
	if (list.is_empty()) {
		return ost << 0;
	}
	for (auto node = list.first; node != nullptr; node = node->next) {
		ost << node->value;
		if (node != list.last) {
			 ost << " + ";
		}
	}
	return ost;
}

float hornerStep(Node<PolynomialTerm> * node, float x, int prev_degree = -1) {
	if (node == nullptr) {
		return 0;
	}
	float coeff = node->value.coefficient;
	float degree = node->value.degree;
	if (degree - prev_degree != 1) {
		return 0 + x * hornerStep(node, x, prev_degree + 1);
	}
	return coeff + x * hornerStep(node->next, x, degree);
}

float evalPolynomial(LinkedList<PolynomialTerm> pl, float x) {
	if (pl.is_empty()) {
		return 0;
	}
	return hornerStep(pl.first, x);
}

int main() {


	std::cout << "Choose an option [1/2]:\n"
		"1. Test via pregenerated list\n"
		"2. Input your own list\n";
	int option;
	std::cin >> option;

	LinkedList<PolynomialTerm> test_list;
	switch (option) {
	case 1:
		test_list = LinkedList(std::vector{
			PolynomialTerm(3, 0), 
			PolynomialTerm(2, 2), 
			PolynomialTerm(1, 3), 
			PolynomialTerm(7, 6)
		});
		break;
	case 2:
		int length;
		std::cout << "Enter the list length (amount of polynomial terms): ";
		std::cin  >> length;
		std::cout << "Enter coefficient and degree separated by space for each term"
				"row by row in degree ascending order\n";
		for (int i = 0; i < length; i++) {
			float coefficient;
			int degree;
			std::cin >> coefficient >> degree;
			test_list.push_back(PolynomialTerm(coefficient, degree));
		}
		break;
	default:
		std::cout << "Invalid option\n";
		return -1;
	}

	std::cout << "\nTESTING `LinkedList` output\n" << test_list << '\n';

	std::cout << "\nTESTING `push_front`\n";
	std::cout << "Enter coefficient and degree separated by space \n";
	float coefficient;
	int degree;
	std::cin >> coefficient >> degree;
	std::cout << "before: " << test_list << '\n';
	test_list.push_front(PolynomialTerm(coefficient, degree));
	std::cout << "after: " << test_list << '\n';

	
	std::cout << "\nTESTING `remove_value`\n";
	std::cout << "Enter coefficient and degree separated by space \n";
	std::cin >> coefficient >> degree;
	std::cout << "before: " << test_list << '\n';
	test_list.remove_value(PolynomialTerm(coefficient, degree));
	std::cout << "after: " << test_list << '\n';


	std::cout << "\nTESTING `evalPolynomial`\n";
	std::cout << "Enter x to compute the polynomial for: ";
	float variable;
	std::cin >> variable;
	std::cout << test_list << " (for x=" << variable << ") = " 
		<< evalPolynomial(test_list, variable) << '\n';
}

