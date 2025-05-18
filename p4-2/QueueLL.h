#ifndef __QUEUELL_H__
#define __QUEUELL_H__

#include "DynamicArray.h"
#include "LinkedList.h"

namespace krft {

template <typename T>
class QueueLL : private LinkedList<T> {
public:
	QueueLL<T>() : LinkedList<T>() {};
	QueueLL<T>(std::vector<T> v) : LinkedList<T>(v) {};
	QueueLL<T>(T array[], size_t size) : LinkedList<T>(array, size) {};
	QueueLL<T>(const QueueLL<T>& other) : LinkedList<T>(other) {}

	using LinkedList<T>::push_back;
	using LinkedList<T>::pop_front;
	using LinkedList<T>::back;
	using LinkedList<T>::front;
	using LinkedList<T>::empty;

	friend std::ostream& operator<<(std::ostream& ost, const QueueLL<T> q) {
	for (auto node = q.first; node != nullptr; node = node->next) {
		ost << node->value;
		if (node != q.last) {
			 ost << ' ';
		}
	}
	return ost;
}
};

}

#endif // __QUEUELL_H__
