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
    bool removeElement(int element);
    Node* findElement(int element);
    void printAll(); // just for tests
    LinkedList(void);
    ~LinkedList(void);
private:
    HANDLE changeMutex;
    HANDLE counterMutex;
    HANDLE noFindEvent;

    Node* firstNode;
    Node* lastNode;

    int findCount;
    void incrementFindCount();
    void decrementFindCount();

    bool delElement(int element);
};

