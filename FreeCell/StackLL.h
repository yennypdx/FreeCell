#pragma once
#ifndef StackLL_H
#define StackLL_H
#include <iostream>
#include "Node.h"
#include "DoubleLL.h"
#include "Exception.h"

using namespace std;
template<typename T>
class Node;

template<typename T>
class DoubleLL;

template<typename T>
class StackLL {
public:
	StackLL();
	StackLL(const StackLL<T> & originalCopy);
	StackLL & operator=(const StackLL<T> & inRhs);
	~StackLL();
public:
	void Push(T inValue);
	T Pop();
	T Peek();
	int SizeOf();
	bool isEmpty() const;

private:
	DoubleLL<T> m_StackLL;
	int elementLength;
};

template<typename T>
inline StackLL<T>::StackLL()
{
	m_StackLL = DoubleLL<T>();
	elementLength = 0;
}

template<typename T>
inline StackLL<T>::StackLL(const StackLL<T> & originalCopy)
{
	m_StackLL = originalCopy.m_StackLL;
	elementLength = originalCopy.elementLength;
}

template<typename T>
inline StackLL<T>& StackLL<T>::operator=(const StackLL<T> & inRhs)
{
	m_StackLL = inRhs.m_StackLL;
	elementLength = inRhs.elementLength;

	return *this;
}

template<typename T>
inline StackLL<T>::~StackLL()
{}

template<typename T>
inline void StackLL<T>::Push(T inValue)
{
	m_StackLL.Append(inValue);
	elementLength++;
}

template<typename T>
inline T StackLL<T>::Pop()
{
	T tempVal;
	if (isEmpty() != true) {
		tempVal = m_StackLL.Last();
		m_StackLL.Extract(m_StackLL.Last());
		elementLength--;
	}
	else {
		throw Exception("Stack is empty. Cannot Pop() your stack.");
	}
	return tempVal;
}

template<typename T>
inline T StackLL<T>::Peek()
{
	return m_StackLL.Last();
}

template<typename T>
inline int StackLL<T>::SizeOf()
{
	return elementLength;
}

template<typename T>
inline bool StackLL<T>::isEmpty() const
{
	return m_StackLL.isEmpty();
}

#endif 