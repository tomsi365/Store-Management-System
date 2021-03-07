#ifndef __ARRAY_H
#define __ARRAY_H

#include <iostream>
using namespace std;

template<class T>
class Array
{
private :
	int physicalSize, logicalSize;
	char delimeter;
	T* arr;
public:
	Array(int maxSize = 10, char delimeter = ' ');
	Array(const Array& other);
	~Array();
	const Array& operator=(const Array& other);
	const Array& operator+=(const T& newVal);
	T& operator[](int index);
	T& operator[](char index);
	T& At(int index) const;
	
	// print operator .
	friend ostream& operator<< (ostream& os, const Array<T>& arr)
	{
		for (int i = 0;i < arr.logicalSize;i++)
		{
			os << arr.arr[i] << arr.delimeter;
		}
		return os;
	}
};

// constructor .
template<class T>
Array<T>::Array(int maxSize, char delimeter) : physicalSize(maxSize), logicalSize(0), delimeter(delimeter)
{
	arr = new T[maxSize];
}

// copy constructor .
template<class T>
Array<T>::Array(const Array<T>& other) : arr(nullptr)
{
	*this = other;
}

// desturctor .
template<class T>
Array<T>::~Array()
{
	delete [] arr;
}

// placement operator .
template<class T>
const Array<T>& Array<T>::operator=(const Array<T>& other)
{
	if (arr != nullptr)
	{
		delete[] arr;
	}
	physicalSize = other.physicalSize;
	logicalSize = other.logicalSize;
	delimeter = other.delimeter;
	arr = new T[physicalSize];
	for (int i = 0;i < logicalSize;i++)
	{
		arr[i] = other.arr[i];
	}
	return *this;
}

// adding operator .
template<class T>
const Array<T>& Array<T>::operator+=(const T& newVal)
{
	if (logicalSize == physicalSize)
	{
		physicalSize = physicalSize * 2;
		T* new_arr = new T[physicalSize * 2];
		for (int i = 0;i < logicalSize;i++)
		{
			new_arr[i] = arr[i];
		}
		delete[]arr;
		arr = new_arr;
	}
	arr[logicalSize++] = newVal;
	return *this;
}

// index operator .
template<class T>
T& Array<T>::operator[](int index)
{
	return arr[index];
}

// index operator .
template<class T>
T& Array<T>::operator[](char index)
{
	return arr[index];
}

// index access function for const functions
template<class T>
T& Array<T>::At(int index) const
{
	return arr[index];
}

#endif