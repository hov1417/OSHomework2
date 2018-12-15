#pragma once

#include "utilities.h"

class Node 
{
public:
    Node* next;
    int value;
    Node(Node* next, int value) {
        this->next = next;
        this->value = value;
    }
    ~Node() {
        delete this->next;
    }
};

class LinkedList
{
public:
    void addElement(int element);
    void removeElement(int element);
    Node* findElement(int element);
    void printAll();
    LinkedList(void);
    ~LinkedList(void);
private:
    HANDLE addMutex;
    HANDLE findMutex;
    HANDLE deleteMutex;
    HANDLE counterMutex;
    HANDLE noFindEvent;

    Node* firstNode;
    Node* lastNode;
    
    int findCount;
    void incrementFindCount();
    void decrementFindCount();

    void delElement(int element);
};

