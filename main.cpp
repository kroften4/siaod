#include <iostream>
#include <vector>

// #define NDEBUG
#include <cassert>

class PolynomialTerm {
public:
	float coefficient;
	int degree;
	
	PolynomialTerm(float coefficient, int degree) : coefficient{coefficient}, degree{degree} {}

	friend bool operator==(const PolynomialTerm &l, const PolynomialTerm &r) {
		return l.coefficient == r.coefficient && l.degree == r.degree;
	}

	friend bool operator!=(const PolynomialTerm &l, const PolynomialTerm &r) {
		return !(l == r);
	}

	friend std::ostream& operator<<(std::ostream& ost, const PolynomialTerm pt) {
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
};

template <typename DataT>
struct Node {
	DataT value;
	Node * next;
	Node(DataT value) : value{value}, next{nullptr} {};
};

template <typename DataT>
class LinkedList {
private:
	bool is_one_in_length() {
		return first == last;
	};

	Node<DataT> * find_previous(Node<DataT> * node) {
		if (is_empty() || is_one_in_length()) {
			return nullptr;
		}
		Node<DataT> * p = first;
		for (;p->next != node && p != nullptr; p = p->next) {}
		return p;
	}

	bool remove_node(Node<DataT> * node) {
		if (node == first) {
			if (is_one_in_length()) {
				last = nullptr;
			}
			Node<DataT> * trash = first;
			first = first->next;
			delete trash;
		} else if (node == last) {
			Node<DataT> * second_last = find_previous(last);
			assert(second_last != nullptr);
			delete last;
			last = second_last;
			last->next = nullptr;
		} else {
			Node<DataT> * previous = find_previous(node);
			if (previous == nullptr) {
				return false;
			}
			previous->next = node->next;
			delete node;
		}

		return true;
	}

public:
	Node<DataT> * first;
	Node<DataT> * last;

	LinkedList() : first{nullptr}, last{nullptr} {};


	LinkedList(std::vector<DataT> vec) {
		first = nullptr;
		last = nullptr;
		for (DataT ele : vec) {
			push_back(ele);
		}
	};

	// ~LinkedList() {
	// 	Node<DataT> * node = first;
	// 	while (node != nullptr) {
	// 		Node<DataT> * trash = node;
	// 		node = node->next;
	// 		delete trash;
	// 	}
	// }

	bool is_empty() {
		return first == nullptr;
	};

	void push_back(DataT value) {
		auto * node = new Node<DataT>{value};
		if (is_empty()) {
			first = node;
			last = node;
		} else if (is_one_in_length()) {
			first->next = node;
			last = node;
		} else {
			last->next = node;
			last = node;
		}
		assert(last->next == nullptr);
		assert(last->value == value);
	};

	void push_front(DataT value) {
		auto * node = new Node<DataT>{value};
		if (is_empty()) {
			first = node;
			last = node;
		} else if (is_one_in_length()) {
			first = node;
			first->next = last;
		} else {
			Node<DataT> * second = first;
			first = node;
			first->next = second;
		}
		assert(first->value == value);
	}
	
	bool remove_value(DataT value) {
		Node<DataT> * p = first;
		for (;p != nullptr && p->value != value; p = p->next) {}
		return remove_node(p);
	}
};	

template <typename DataT>
std::ostream& operator<<(std::ostream& ost, const LinkedList<DataT> list) {
	for (auto node = list.first; node != nullptr; node = node->next) {
		ost << node->value;
		if (node != list.last) {
			 ost << ' ';
		}
	}
	return ost;
}

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

