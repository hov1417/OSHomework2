#include "StdAfx.h"
#include "LinkedList.h"
#include "utilities.h"

LinkedList::LinkedList(void)
{
    this->findCount = 0;

    this->firstNode = nullptr;
    this->lastNode = nullptr;
    
    this->addMutex = CreateSimpleMutex_s();
    this->findMutex = CreateSimpleMutex_s();
    this->deleteMutex = CreateSimpleMutex_s();
    this->counterMutex = CreateSimpleMutex_s();
    this->noFindEvent = CreateEvent(NULL, TRUE, FALSE, NULL); 
        
    if (this->noFindEvent == NULL) 
    { 
        _tprintf(_T("CreateEvent failed:\n"));
        ErrorExit();
    }
}

void LinkedList::addElement(int element)
{
    WaitForObject_s(this->addMutex);

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

void LinkedList::removeElement(int element)
{
    WaitForObject_s(this->counterMutex);
    if (this->findCount == 0)
    {
        this->delElement(element);
        ReleaseMutex_s(this->counterMutex);
        return;
    }
    ReleaseMutex_s(this->counterMutex);
    HANDLE handles[2] = { this->noFindEvent, this->counterMutex };

    DWORD res = WaitForMultipleObjects(2, handles, true, INFINITE);
    if (res != WAIT_OBJECT_0)
    {
        printf("WAIT_ABANDONED | WAIT_TIMEOUT | WAIT_FAILED error:\n");
        ErrorExit();
    }
    this->delElement(element);
    ReleaseMutex_s(this->counterMutex);
    if(!ResetEvent(this->noFindEvent))
    {
        printf("ResetEvent error:\n");
        ErrorExit();
    }
}


void LinkedList::delElement(int element) 
{
    Node* current = this->firstNode;
    if (!current)
        return;
    while(current->next)
    {
        if (current->next->value == element)
        {
            Node * toDelete = current->next;
            current->next = toDelete->next;
            toDelete->next = nullptr;
            delete toDelete;
        }
        current = current->next;
    }
}


Node* LinkedList::findElement(int element)
{
    this->incrementFindCount();
    Node* current = this->firstNode;
    while(current)
    {
        if (current->value == element)
            return current;
        current = current->next;
    }
    this->decrementFindCount();
    return nullptr;
}

void LinkedList::printAll()
{
    Node* current = this->firstNode;
    while(current)
    {
        _tprintf(_T("%d "), current->value);
        current = current->next;
    }
    _tprintf(_T("\n"));
}


void LinkedList::incrementFindCount()
{
    WaitForObject_s(this->counterMutex);
    this->findCount ++;
    ReleaseMutex_s(this->counterMutex);
}

void LinkedList::decrementFindCount()
{
    WaitForObject_s(this->counterMutex);

    if(this->findCount <= 0)
    {
        _tprintf(_T("FindCount is 0"));
        ExitProcess(-1);
    }
    this->findCount --;

    if (this->findCount == 0)
    {
        if (! SetEvent(this->noFindEvent)) 
        {
            printf("SetEvent failed:\n");
            ErrorExit();
        }
    }
    ReleaseMutex_s(this->counterMutex);
}


LinkedList::~LinkedList(void)
{
    delete this->firstNode;

    CloseHandle_s(this->addMutex);
    CloseHandle_s(this->findMutex);
    CloseHandle_s(this->deleteMutex);
    CloseHandle_s(this->counterMutex);
    CloseHandle_s(this->noFindEvent);
}
