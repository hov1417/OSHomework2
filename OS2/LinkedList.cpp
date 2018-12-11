#include "StdAfx.h"
#include "LinkedList.h"


template<typename T>
LinkedList<T>::LinkedList(void)
{
	this->addMutex = CreateMutex(NULL, FALSE, NULL);
	
	this->firstNode = nullptr;
	this->lastNode = nullptr;
    if (this->addMutex == NULL) 
    {
        printf("CreateMutex error: %d\n", GetLastError());
        return;
    }
}

template<typename T>
void LinkedList<T>::addElement(T element) {
	DWORD waitResult = WaitForSingleObject(this->addMutex, INFINITE);

	switch (waitResult) 
    {
        case WAIT_OBJECT_0: 
			if (this->firstNode == nullptr)
			{
				this->firstNode = this->lastNode = new Node<T>(nullptr, element);
			}
			else 
			{
				Node<T>* newNode = new Node<T>(nullptr, element);
				this->lastNode->next = newNode;
				this->lastNode = newNode;
			}

			if (! ReleaseMutex(this->addMutex)) 
            {
				printf("ReleaseMutex error: %d\n", GetLastError());
				return;
            } 

            break; 
        case WAIT_ABANDONED: 
        case WAIT_TIMEOUT:
			printf("WAIT_ABANDONED | WAIT_TIMEOUT error: %d\n", GetLastError());
            return; 
    }

}

template<typename T>
void LinkedList<T>::removeElement(T element) {

}

template<typename T>
Node<T>* LinkedList<T>::findElement(T element) {
	return nullptr;
}

template<typename T>
void LinkedList<T>::printAll() {
	Node<T>* current = this->firstNode;
	while(current) {
		_tprintf(_T("%d "), current->value);
		current = current->next;
	}
	_tprintf(_T("\n"));
}

template<typename T>
LinkedList<T>::~LinkedList(void)
{
	delete this->firstNode;
}
