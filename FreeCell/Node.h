#pragma once
#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

template<typename T>
class Node
{
public:
	Node();
	Node(const Node<T>& copy);
	Node<T>& operator=(const Node<T> & rhs);
	~Node();
public:
	void setData(T inData);
	T getData();
	void setPrev(Node<T>* inPrev);
	Node<T>* getPrev() const;
	void setNext(Node<T>* inNext);
	Node<T>* getNext() const;

private:
	T Data;
	Node<T>* Prev;
	Node<T>* Next;
};

template<typename T>
inline Node<T>::Node()
{
	Prev = nullptr;
	Next = nullptr;
}

template<typename T>
inline Node<T>::Node(const Node<T> & copy)
{
	Data = copy.getData();
	Prev = copy.getPrev();
	Next = copy.getNext();
}

template<typename T>
inline Node<T>& Node<T>::operator=(const Node<T>& rhs)
{
	Data = rhs.getData();
	Prev = rhs.getPrev();
	Next = rhs.getNext();
}

template<typename T>
inline Node<T>::~Node()
{
	Prev = nullptr;
	Next = nullptr;
}

template<typename T>
inline void Node<T>::setData(T inData)
{
	Data = inData;
}

template<typename T>
inline T Node<T>::getData()
{
	return Data;
}

template<typename T>
inline void Node<T>::setPrev(Node<T>* inPrev)
{
	Prev = inPrev;
}

template<typename T>
inline Node<T>* Node<T>::getPrev() const
{
	return Prev;
}

template<typename T>
inline void Node<T>::setNext(Node<T>* inNext)
{
	Next = inNext;
}

template<typename T>
inline Node<T>* Node<T>::getNext() const
{
	return Next;
}

#endif