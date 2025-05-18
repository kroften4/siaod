#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include "Node.h"
#include <iostream>
#include <vector>
#include <cstddef>

#include <cassert>

namespace krft {

template <typename T>
class LinkedList {
private:
	bool is_one_in_length() {
		return first == last;
	};

	Node<T> *find_previous(Node<T> *node) {
		if (empty() || is_one_in_length()) {
			return nullptr;
		}
		Node<T> *p = first;
		for (;p->next != node && p != nullptr; p = p->next) {}
		return p;
	}

	bool remove_node(Node<T> *node) {
		if (node == first) {
			if (is_one_in_length()) {
				last = nullptr;
			}
			Node<T> *trash = first;
			first = first->next;
			delete trash;
		} else if (node == last) {
			Node<T> *second_last = find_previous(last);
			assert(second_last != nullptr);
			delete last;
			last = second_last;
			last->next = nullptr;
		} else {
			Node<T> *previous = find_previous(node);
			if (previous == nullptr) {
				return false;
			}
			previous->next = node->next;
			delete node;
		}

		return true;
	}

public:
	Node<T> *first;
	Node<T> *last;

	LinkedList<T>() : first{nullptr}, last{nullptr} {};

	LinkedList<T>(std::vector<T> vec) {
		first = nullptr;
		last = nullptr;
		for (T ele : vec) {
			push_back(ele);
		}
	};

	LinkedList<T>(T array[], size_t size) {
		first = nullptr;
		last = nullptr;
		for (int i = 0; i < size; i++) {
			push_back(array[i]);
		}
	};

	LinkedList<T>(const LinkedList<T>& other) {
		first = nullptr;
		last = nullptr;
		for (Node<T> *p = other.first; p != nullptr; p = p->next) {
			push_back(p->value);
		}
	}

	~LinkedList() {
		Node<T> *node = first;
		while (node != nullptr) {
			Node<T> *trash = node;
			node = node->next;
			delete trash;
		}
	}

	bool empty() {
		return first == nullptr;
	};

	void pop_back(T value) {
		remove_node(last);
	}

	void pop_front(T value) {
		remove_node(first);
	}

	T back() {
		return last->value;
	}

	T front() {
		return first->value;
	}

	void push_back(T value) {
		auto *node = new Node<T>{value};
		if (empty()) {
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

	void push_front(T value) {
		auto *node = new Node<T>{value};
		if (empty()) {
			first = node;
			last = node;
		} else if (is_one_in_length()) {
			first = node;
			first->next = last;
		} else {
			Node<T> *second = first;
			first = node;
			first->next = second;
		}
		assert(first->value == value);
	}

	bool remove_value(T value) {
		Node<T> *p = first;
		for (;p != nullptr && p->value != value; p = p->next) {}
		return remove_node(p);
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& ost, const LinkedList<T> list) {
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

