#pragma once
#include <iostream>

template <class T>
struct Element
{
    Element<T>* next;
    T data;
    Element(const T& data, Element<T>* next = NULL)
        : data(data), next(next) {};
    Element(const Element& elem)
    {
        if (elem.next)
            next = new Element(*elem.next);
        else
            next = NULL;
        data = elem.data;

    }
    ~Element()
    {
        delete next;
        data = NULL;
    }
    T getData() { return data; }
};

template <class T>
class List
{
    Element<T>* first;
    Element<T>* last;
    size_t size;
public:
    List()
    {
        first = NULL;
        last = NULL;
        size = 0;
    }
    List(const T& d)
    {
        first = last = new Element<T>(d);
        size = 1;
    }
    List(const List<T>& other)
    {
        copyFrom(other);
    }
    size_t getSize() const { return size; }
    void copyFrom(const List<T>& other)
    {
        if (other.isEmpty())
        {
            first = last = NULL;
            size = 0;
        }
        else
        {
            first = new Element<T>(*other.first);
            this->size = other.size;
            last = first;
            while (last->next)
                last = last->next;
        }
    }

    bool isEmpty() 
    {
        return size == 0;
    }

    ~List()
    {
        delete first;
    }

    void addFront(const T& data)
    {
        if (isEmpty())
        {
            first = last = new Element<T>(data);
        }
        else
        {
            Element<T>* toBeAdded = new Element<T>(data, this->first);
            first = toBeAdded;
        }
        ++size;

    }

    void addLast(const T& data)
    {
        if (isEmpty())
        {
            first = last = new Element<T>(data);
        }
        else
        {
            last->next = new Element<T>(data);
            last = last->next;
        }
        ++size;
    }

    T removeFront()
    {
        if (isEmpty())
            throw "List is empty!";
        Element<T>* toBeRemoved = first;
        T cpyData = first->data;
        first = first->next;
        toBeRemoved->next = NULL;
        delete toBeRemoved;
        --size;
        return cpyData;
    }

    T removeLast()
    {
        if (isEmpty())
            throw "List is empty";
        if (size == 1)
            return removeFront();
        else
        {
            Element<T>* temp = getElementAt(size-2);
            T tmpData = temp->next->data;
            --size;
            last = temp;
            delete temp->next;
            temp->next = NULL;
            return tmpData;
        }
    }

    Element<T>* getElementAt(int pos)
    {
        Element<T>* tmp = first;
        while(pos > 0)
        {
            --pos;
            tmp = tmp->next;
        }
        return tmp;
    }

    T getDataAt(size_t pos)
    {
        if (pos > size || pos < 0)
            throw "invalid index";
        Element<T>* tmp = first;
        while(pos)
        {
            --pos;
            tmp = tmp->next;
        }
        return tmp->data;
    }

    void insertAt(size_t pos, const T& element)
    {
        if (pos == 0)
            addFront(element);
        if (pos == size)
            addLast(element);
        else
        {
            Element<T>* x = getElementAt(pos-1);
            Element<T>* toBeInserted = new Element<T>(element, x->next);
            x->next = toBeInserted;
            ++size;
        }
    }
    T removeAt(size_t pos)
    {
        if (pos >= size)
            throw "Invalid index";
        if (pos == 0)
            return removeFront();
        Element<T>* x = getElementAt(pos-1);
        T data = x->next->data;
        Element<T>* toBeRemoved = x->next;
        x->next = toBeRemoved->next;
        toBeRemoved->next = NULL;
        delete toBeRemoved;
        --size;
        return data;
    }

};
