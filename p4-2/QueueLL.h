#ifndef __QUEUELL_H__
#define __QUEUELL_H__

#include "LinkedList.h"

namespace krft {

template <typename T>
class QueueLL : private LinkedList<T> {
public:
	QueueLL<T>(): LinkedList<T>() {};
	QueueLL<T>(std::vector<T> v): LinkedList<T>(v) {};

	using LinkedList<T>::push_back;
	using LinkedList<T>::pop_front;
	using LinkedList<T>::back;
	using LinkedList<T>::front;
	using LinkedList<T>::empty;
};

}

#endif //__QUEUELL_H__
