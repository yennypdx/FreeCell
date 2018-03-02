#include "stdafx.h"
#pragma once
#ifndef STACK_H
#define STACK_H
#include <iostream>
#include "Array.h"
#include "Exception.h"

using namespace std;
template<typename T>
class Array;

template<typename T>
class Stack {
public:
	Stack();
	Stack(int stackSize);
	Stack(const Stack<T>& originalCopy);
	Stack& operator=(const Stack<T> & inRhs);
	~Stack();
public:
	void Push(T inVal);
	T Pop();
	T Peek();
	int SizeOf();
	bool isEmpty() const;
	bool isFull() const;

private:
	Array<T> m_stack;
	int m_topOfStack; 
};

template<typename T>
inline Stack<T>::Stack()
{
	m_stack = Array<T>();
	m_topOfStack = 0;
}

template<typename T>
inline Stack<T>::Stack(int stackSize)
{
	m_stack = Array<T>(stackSize);
	m_topOfStack = stackSize - 1;
}

template<typename T>
inline Stack<T>::Stack(const Stack<T> & originalCopy)
{
	m_topOfStack = originalCopy.m_topOfStack;
	m_stack = originalCopy.m_stack;
}

template<typename T>
inline Stack<T>& Stack<T>::operator=(const Stack<T> & inRhs)
{
	if (this != &inRhs) {
		m_stack = inRhs.m_stack;
		m_topOfStack = inRhs.m_topOfStack;
	}
	return *this;
}

template<typename T>
inline Stack<T>::~Stack()
{
	m_topOfStack = 0;
}

template<typename T>
inline void Stack<T>::Push(T inVal)
{
	if (!isEmpty()) {
		m_stack[m_topOfStack] = inVal;
	}
	else {
		throw Exception("Exception caught: Stack is full");
	}
}

template<typename T>
inline T Stack<T>::Pop()
{
	if (!isEmpty()) {
		return m_stack[m_topOfStack--];
	}
	else {
		throw Exception("Exception caught: Stack is empty");
	}
}

template<typename T>
inline T Stack<T>::Peek()
{
	return m_stack[m_topOfStack];
}

template<typename T>
inline int Stack<T>::SizeOf()
{
	return m_topOfStack + 1;
}

template<typename T>
inline bool Stack<T>::isEmpty() const
{
	bool outResult = false;
	if (m_topOfStack == 0)
	{
		outResult = true;
	}
	return outResult;
}

template<typename T>
inline bool Stack<T>::isFull() const
{
	bool outResult = false;
	if (m_topOfStack == m_stack.getLength() - 1)
	{
		outResult = true;
	}
	return outResult;
}

#endif 
