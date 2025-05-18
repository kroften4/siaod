#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include "Node.h"
#include <iostream>
#include <vector>

#include <cassert>

namespace krft {

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

}

#endif // __LINKEDLIST_H__

