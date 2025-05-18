#ifndef __DYNAMICARRAY_H__
#define __DYNAMICARRAY_H__

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cstddef>

namespace krft {

template <typename T>
class DynamicArray {
private:
	std::size_t capacity;
	std::size_t _size;
	T *array;

	void extend() {
		capacity *= 2;
		T *new_array = new T[_size * 2];
		for (std::size_t i = 0; i < _size; i++) {
			new_array[i] = array[i];
		}
		delete[] array;
		array = new_array;
	}

	void shrink() {
		capacity = _size;
		T *new_array = new T[_size];
		for (std::size_t i = 0; i < _size; i++) {
			new_array[i] = array[i];
		}
		delete[] array;
		array = new_array;
	}

	void increment_size() {
		if (++_size > capacity) {
			extend();
		}
	}

public:
	DynamicArray<T>(T array[], std::size_t size) : _size(size), capacity(capacity), array(new T[size]) {
		std::copy(array, array + size, this->array);
	}

	DynamicArray<T>(const DynamicArray<T>& other) : _size(other._size), capacity(other.capacity), array(new T[other._size]) {
		std::copy(other.array, other.array + other._size, this->array);
	}
	
	~DynamicArray() {
		delete[] array;
	}

	int size() {
		return _size;
	}

	bool empty() {
		return _size == 0;
	}

	void push_back(T value) {
		array[_size] = value;
		increment_size();
	}

	void pop_back(T value) {
		if (_size > 0)
			_size--;
	}

	void insert_at(std::size_t index, T value) {
		if (index < 0 || index >= _size) 
			throw std::out_of_range("Bad index passed to insert_at()");
		for (std::size_t i = _size; i > index; i--) {
			array[i] = array[i - 1];
		}
		array[index] = value;
		increment_size();
	}

	void remove_at(std::size_t index) {
		if (index < 0 || index >= _size) 
			throw std::out_of_range("Bad index passed to remove_at()");
		for (std::size_t i = index; i < _size; i++) {
			array[i] = array[i + 1];
		}
		_size--;
	}

	T& at(size_t index) const {
		if (index < 0 || index >= _size) 
			throw std::out_of_range("Bad index passed to at()");
		return array[index];
	}

	T at(size_t index) {
		if (index < 0 || index >= _size) 
			throw std::out_of_range("Bad index passed to at()");
		return array[index];
	}

	T& operator[](std::size_t index) {
		return array[index];
	}

	T operator[](std::size_t index) const {
		return array[index];
	}

	friend std::ostream& operator<<(std::ostream& ost, DynamicArray<T> arr) {
		for (std::size_t i = 0; i < arr.size(); i++) {
			ost << arr[i] << ' ';
		}
		return ost;
	}
};

}

#endif // __DYNAMICARRAY_H__
