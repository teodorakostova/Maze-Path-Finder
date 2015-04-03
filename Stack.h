#pragma once

template <class T>
struct Elem
{
	T data;
	Elem<T>* next;
	Elem(const T& data, Elem<T>* next = NULL)
		: data(data), next(next) {}
	~Elem()
	{
		if (next)
			delete next;
	}
};

template <class T>
class Stack
{
	Elem<T>* head;

	Stack(const Stack<T>&);
	Stack<T>& operator=(const Stack<T>&);
public:
	Stack() : head(NULL) {}

	~Stack()
	{
		delete head;
	}

	bool empty() const
	{
		return !head;
	}

	const T& top()
	{
		if (empty())
			throw "Stack is empty!";
		return head->data;
	}
	
	void push(const T& elem)
	{
		Elem<T>* newHead = new Elem<T>(elem);
		newHead->next = head;
		head = newHead;
	}

	T pop()
	{
		if (empty())
			throw "Stack is empty";
		Elem<T>* headCopy = head;
		T headDataCopy = head->data;
		head = head->next;
		headCopy->next = NULL;
		delete headCopy;
		return headDataCopy;
	}

};
