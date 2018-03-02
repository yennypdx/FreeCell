#pragma once
#ifndef DOUBLELL_H
#define DOUBLELL_H
#include <iostream>
#include "Node.h"
#include "Exception.h"

using namespace std;
template<typename T>
class Node;

template<typename T>
class DoubleLL
{
public:
	DoubleLL();
	DoubleLL(const DoubleLL<T> & sourceToCopy);
	DoubleLL<T>& operator=(const DoubleLL<T> & rhs);
	~DoubleLL();
public:
	void setHead(Node<T> inNode);
	Node<T>* getHead() const;
	void setTail(Node<T> inNode);
	Node<T>* getTail() const;
public:
	bool isEmpty() const;
	const T First();
	const T Last();
	void Prepend(T inValue);
	void Append(T inValue);
	void Purge();
	void Extract(T inValue);
	void InsertBefore(T inVal_i, T inVal_ii);
	void InsertAfter(T inVal_i, T inVal_ii);

private:
	Node<T>* Head;
	Node<T>* Tail;

};

template<typename T>
inline DoubleLL<T>::DoubleLL()
{
	Head = nullptr;
	Tail = nullptr;
}

template<typename T>
inline DoubleLL<T>::DoubleLL(const DoubleLL<T> & originalCopy)
{
	Head = nullptr;
	Tail = nullptr;
	Node<T>* currPointer = nullptr;

	if (originalCopy.isEmpty() == false) {
		currPointer = originalCopy.getHead();
		while (currPointer != nullptr) {
			Append(currPointer->getData());
			currPointer = currPointer->getNext();
		}
	}
	delete currPointer;
}

template<typename T>
inline DoubleLL<T> & DoubleLL<T>::operator=(const DoubleLL<T> & rhs)
{
	Head = nullptr;
	Tail = nullptr;
	Node<T>* currPointer;

	if (rhs.isEmpty() == false) {
		currPointer = rhs.getHead();
		while (currPointer != nullptr) {
			Append(currPointer->getData());
			currPointer = currPointer->getNext();
		}
	}
	return *this;
	delete currPointer;
}

template<typename T>
inline DoubleLL<T>::~DoubleLL()
{
	while (Head != nullptr) {
		Node<T>* currPointer = Head;
		Head = Head->getNext();
		delete currPointer;
	}
	Head = nullptr;
	Tail = nullptr;
}

template<typename T>
inline void DoubleLL<T>::setHead(Node<T> inNode)
{
	Head = First();
}

template<typename T>
inline Node<T>* DoubleLL<T>::getHead() const
{
	return Head;
}

template<typename T>
inline void DoubleLL<T>::setTail(Node<T> inNode)
{
	Tail = Last();
}

template<typename T>
inline Node<T>* DoubleLL<T>::getTail() const
{
	return Tail;
}

template<typename T>
inline bool DoubleLL<T>::isEmpty() const
{
	bool empty = false;
	if (Head == nullptr && Tail == nullptr) {
		empty = true;
	}
	return empty;
}

template<typename T>
inline const T DoubleLL<T>::First()
{
	return Head->getData();
}

template<typename T>
inline const T DoubleLL<T>::Last()
{
	return Tail->getData();
}

template<typename T>
inline void DoubleLL<T>::Prepend(T inValue)
{
	Node<T>* nodeToInsert = new Node<T>();
	nodeToInsert->setData(inValue);

	if (Head == nullptr) {
		Head = nodeToInsert;
		Tail = nodeToInsert;
	}
	else {
		//Make next of new node as tail
		nodeToInsert->setNext(Head);
		Head->setPrev(nodeToInsert);
		Head = nodeToInsert;

	}
}

template<typename T>
inline void DoubleLL<T>::Append(T inValue)
{
	Node<T>* nodeToInsert = new Node<T>();
	nodeToInsert->setData(inValue);

	if (Head == nullptr) {
		Head = nodeToInsert;
		Tail = nodeToInsert;
	}
	else {
		//Make next of new node as tail
		nodeToInsert->setPrev(Tail);
		Tail->setNext(nodeToInsert);
		Tail = nodeToInsert;

	}
}

template<typename T>
inline void DoubleLL<T>::Purge()
{
	while (Head != nullptr) {
		Node<T>* currPointer = Head;
		Head = Head->getNext();
		delete currPointer;
	}
	Head = nullptr;
	Tail = nullptr;
}

template<typename T>
inline void DoubleLL<T>::Extract(T inValue)
{
	Node<T>* current = Head;

	//Find the value to extract
	while (current != nullptr && current->getData() != inValue) {
		current = current->getNext();
	}

	//We found the data point
	if (current != nullptr) {

		//Only one item in the list
		if (Head == Tail) {
			Head = nullptr;
			Tail = nullptr;
		}
		else {
			//Check if beginning of list
			if (current->getPrev() == nullptr) {
				Head = current->getNext();
				Head->setPrev(nullptr);
			}

			//Check if end of list
			if (current->getNext() == nullptr) {
				Tail = current->getPrev();
				Tail->setNext(nullptr);
			}

			if ((current->getNext() != nullptr) && (current->getPrev() != nullptr)) {
				current->getPrev()->setNext(current->getNext());
				current->getNext()->setPrev(current->getPrev());
			}
		}
		delete current;
	}
}

template<typename T>
inline void DoubleLL<T>::InsertBefore(T inVal_i, T inVal_ii)
{
	Node<T>* current = Head;
	current->setData(inVal_ii);

	if (current->getData() == inVal_ii) {
		Prepend(inVal_i);
	}
}

template<typename T>
inline void DoubleLL<T>::InsertAfter(T inVal_i, T inVal_ii)
{
	Node<T>* current = Tail;
	current->setData(inVal_ii);

	if (current->getData() == inVal_ii) {
		Append(inVal_i);
	}
}

#endif