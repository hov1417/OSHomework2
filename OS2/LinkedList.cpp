#include "StdAfx.h"
#include "LinkedList.h"

LinkedList::LinkedList(void)
{
	this->firstNode = nullptr;
	this->lastNode = nullptr;
	
	this->addMutex = CreateSimpleMutex_s();
	this->findMutex = CreateSimpleMutex_s();
	this->deleteMutex = CreateSimpleMutex_s();
}

void LinkedList::addElement(int element) {
	WaitForMutex_s(this->addMutex);

	if (this->firstNode == nullptr)
	{
		this->firstNode = this->lastNode = new Node(nullptr, element);
	}
	else 
	{
		Node* newNode = new Node(nullptr, element);
		this->lastNode->next = newNode;
		this->lastNode = newNode;
	}
	
	ReleaseMutex_s(this->addMutex);
}

void LinkedList::removeElement(int element) {

}

Node* LinkedList::findElement(int element) {
	Node* current = this->firstNode;
	while(current) {
		if (current->value == element)
			return current;
		current = current->next;
	}
	return nullptr;
}

void LinkedList::printAll() {
	Node* current = this->firstNode;
	while(current) {
		_tprintf(_T("%d "), current->value);
		current = current->next;
	}
	_tprintf(_T("\n"));
}

LinkedList::~LinkedList(void)
{
	delete this->firstNode;
	CloseHandle_s(this->addMutex);
	CloseHandle_s(this->findMutex);
	CloseHandle_s(this->deleteMutex);
}
