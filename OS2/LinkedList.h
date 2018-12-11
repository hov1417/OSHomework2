#pragma once

template<typename T>
class Node 
{
public:
	Node* next;
	T value;
	Node(Node* next, T value) {
		this->next = next;
		this->value = value;
	}
	~Node() {
		delete this->next;
	}
};

template<typename T>
class LinkedList
{
public:
	void addElement(T element);
	void removeElement(T element);
	Node<T>* findElement(T element);
	void printAll();
	LinkedList(void);
	~LinkedList(void);
private:
	HANDLE addMutex;
	Node<T>* firstNode;
	Node<T>* lastNode;
};

