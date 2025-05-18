#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "DynamicArray.h"

namespace krft {

template <typename T>
class Queue : private DynamicArray<T> {

public:
	Queue<T>(int array[], int size) : DynamicArray<T>(array, size) {};

	using DynamicArray<T>::push_back;
	using DynamicArray<T>::operator[];

	void push_front(T value) {
		if (++this->size > this->capacity) {
			this->extend();
		}
		for (int i = this->size; i > 0; i--) {
			this->array[i] = this->array[i - 1];
		}
		this->array[0] = value;
	}

	friend std::ostream& operator<<(std::ostream& ost, Queue<T> q) {
		for (int i = 0; i < q.get_size(); i++) {
			ost << q[i];
		}
		return ost;
	}

};

}

#endif //__QUEUE_H__
