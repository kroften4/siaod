#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "DynamicArray.h"
#include <cstddef>

namespace krft {

template <typename T>
class QueueDA : private DynamicArray<T> {

public:
	QueueDA<T>(int array[], std::size_t size) : DynamicArray<T>(array, size) {};
	QueueDA<T>(const QueueDA<T>& other) : DynamicArray<T>(other) {};

	using DynamicArray<T>::push_back;
	using DynamicArray<T>::size;
	using DynamicArray<T>::empty;
	
	void pop_front() {
		this->remove_at(0);
	}

	T back() {
		return (*this)[size() - 1];
	}

	T front() {
		return (*this)[0];
	}

	friend std::ostream& operator<<(std::ostream& ost, QueueDA<T> q) {
		for (int i = 0; i < q.size(); i++) {
			ost << q[i] << ' ';
		}
		return ost;
	}

};

}

#endif // __QUEUE_H__
