#ifndef __DYNAMICARRAY_H__
#define __DYNAMICARRAY_H__

#include <iostream>
#include <istream>
#include <stdexcept>

namespace krft {

template <typename T>
class DynamicArray {
private:
	int capacity;
	int size;
	T *array;

	void extend() {
		capacity *= 2;
		T *new_array = new T[size * 2];
		for (int i = 0; i < size; i++) {
			new_array[i] = array[i];
		}
		delete[] array;
		array = new_array;
	}

	void shrink() {
		capacity = size;
		T *new_array = new T[size];
		for (int i = 0; i < size; i++) {
			new_array[i] = array[i];
		}
		delete[] array;
		array = new_array;
	}

public:
	DynamicArray(int arr[], int size) {
		array = new T[size];
		for (int i = 0; i < size; i++) {
			array[i] = arr[i];
		}
		capacity = size;
		this->size = size;
	}
	
	~DynamicArray() {
		delete[] array;
	}

	int get_size() {
		return size;
	}

	void push_back(int value) {
		if (size + 1 > capacity) {
			extend();
		}
		array[size] = value;
		size++;
	}

	void pop_back(int value) {
		if (size > 0)
			size--;
	}

	T& operator[](int idx) {
		if (idx >= size) 
			throw std::out_of_range("Dynamimc array index out of range");
		return array[idx];
	}

	T operator[](int idx) const {
		return array[idx];
	}

	friend std::ostream& operator<<(std::ostream& ost, DynamicArray<T> arr) {
		for (int i = 0; i < arr.get_size(); i++) {
			ost << arr[i];
		}
		return ost;
	}
};

}

#endif // __DYNAMICARRAY_H__
