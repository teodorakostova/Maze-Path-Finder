#pragma once
#include <iostream>
using namespace std;

template <class T>
struct QElement
{
	QElement<T>* next;
	T data;

	QElement(const T& data, QElement<T>* next = NULL) : data(data), next(next) {}

};

template <class T>
class Queue
{
public:
	Queue()
	{
		this->first = NULL;
		this->last = NULL;
		size = 0;
	}
	~Queue()
	{
		QElement<T>* temp;
		 
		while (first)
		{
			temp = first->next;
			delete first;
			first = temp;
		}
	}

	void push(const T& element)
	{
		QElement<T>* toBePushed = new QElement<T>(element);
		if (isEmpty())
			first = toBePushed;
		else
			last->next = toBePushed;
		last = toBePushed;
		++size;
	}

	T pop() 
	{
		if (isEmpty())
			throw "Queue is empty!";
	
		T tempData = first->data;
		QElement<T>* temp = first;
		first = first->next;
		delete temp;
		--size;
		return tempData;
	}
	int getSize() const
	{
		return size;
	}
	bool isEmpty()
	{
		return size == 0;
	}
private:
	QElement<T>* first;
	QElement<T>* last;
	int size;
};
