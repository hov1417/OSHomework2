#include "StdAfx.h"
#include "LinkedList.h"
#include "utilities.h"


LinkedList::LinkedList(void)
{
    this->findCount = 0;

    this->firstNode = nullptr;
    this->lastNode = nullptr;

    this->changeMutex = CreateSimpleMutex_s();
    this->counterMutex = CreateSimpleMutex_s();
    this->noFindEvent = CreateSimpleEvent_s();
}


void LinkedList::addElement(int element)
{
    WaitForObject_s(this->changeMutex);

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

    ReleaseMutex_s(this->changeMutex);
}


bool LinkedList::removeElement(int element)
{
    WaitForObject_s(this->changeMutex);

    WaitForObject_s(this->counterMutex);

    if (this->findCount == 0)
    {
        bool res = this->delElement(element);

        ReleaseMutex_s(this->counterMutex);
        ReleaseMutex_s(this->changeMutex);    

        return res;
    }

    ReleaseMutex_s(this->counterMutex);

    HANDLE handles[] = {this->noFindEvent, this->counterMutex};
    WaitForObjects_s(size(handles), handles);
    if(this->findCount)
        ExitProcess(1); // for collecting statistics, BatchRun.cmd

    bool res = this->delElement(element);

    ResetEvent_s(this->noFindEvent);

    ReleaseMutex_s(this->counterMutex);

    ReleaseMutex_s(this->changeMutex);

    return res;
}


bool LinkedList::delElement(int element) 
{
    Node* current = this->firstNode;

    if (!current)
        return false;

    if (current->value == element)
    {
        this->firstNode = current->next;

        if(current == this->lastNode)
            this->lastNode = nullptr; 

        current->next = nullptr;
        delete current;
        return true;
    }

    while(current->next)
    {
        if (current->next->value == element)
        {
            Node * toDelete = current->next;
            current->next = toDelete->next;
            toDelete->next = nullptr;

            if(toDelete == this->lastNode)
                this->lastNode = current;

            delete toDelete;
            return true;
        }
        else
        {
            current = current->next;
        }
    }
    return false;
}


Node* LinkedList::findElement(int element)
{
    this->incrementFindCount();
    Node* current = this->firstNode;
    while(current)
    {
        if (current->value == element)
        {
            this->decrementFindCount();
            return current;
        }
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
    ResetEvent_s(this->noFindEvent);
    this->findCount ++;
    ReleaseMutex_s(this->counterMutex);
}


void LinkedList::decrementFindCount()
{
    WaitForObject_s(this->counterMutex);

    if(this->findCount <= 0)
    {
        _tprintf(_T("FindCount is 0\n"));
        ExitProcess(1);
    }
    this->findCount --;

    if (this->findCount == 0)
        SetEvent_s(this->noFindEvent);
    ReleaseMutex_s(this->counterMutex);
}


LinkedList::~LinkedList(void)
{
    delete this->firstNode;

    CloseHandle_s(this->changeMutex);
    CloseHandle_s(this->counterMutex);
    CloseHandle_s(this->noFindEvent);
}
