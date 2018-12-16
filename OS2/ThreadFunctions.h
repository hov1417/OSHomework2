#pragma once

class ThreadConfig
{
public:
    int* elements;
    int length;
    LinkedList* list;
    ThreadConfig(int elements[], int length, LinkedList* list) {
        this->elements = elements;
        this->length = length;
        this->list = list;
    }
};

DWORD WINAPI addThread(LPVOID lpParam);

DWORD WINAPI findThread(LPVOID lpParam);

DWORD WINAPI deleteThread(LPVOID lpParam);

