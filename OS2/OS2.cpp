
#include "stdafx.h"
#include <vector>

LinkedList* list;

class AddStruct
{
public:
    int* arrayToAdd;
    int length;
    AddStruct(int a[], int length) {
        this->arrayToAdd = a;
        this->length = length;
    }
};

DWORD WINAPI addThread(LPVOID lpParam)
{
    AddStruct* addElems = (AddStruct*) lpParam;
    for(int i = 0; i < addElems->length; i++)
    {
        list->addElement(addElems->arrayToAdd[i]);
        _tprintf(_T("a: added %d\n"), addElems->arrayToAdd[i]);
        Sleep(rand()%10);
    }

    return 0;
}

class FindStruct
{
public:
    int* elementsToFind;
    int length;
    FindStruct(int a[], int length) {
        this->elementsToFind = a;
        this->length = length;
    }
};

DWORD WINAPI findThread(LPVOID lpParam)
{
    FindStruct* findElems = (FindStruct*) lpParam;
    for(int i = 0; i < findElems->length; i++)
    {
        _tprintf(_T("f: %s %d\n"), list->findElement(findElems->elementsToFind[i]) ? _T("found") : _T("can't find"),
            findElems->elementsToFind[i]);
        Sleep(rand()%10);
    }

    return 0;
}

class DeleteStruct
{
public:
    int* elementsToDelete;
    int length;
    DeleteStruct(int a[], int length) {
        this->elementsToDelete = a;
        this->length = length;
    }
};

DWORD WINAPI deleteThread(LPVOID lpParam)
{
    DeleteStruct* deleteElems = (DeleteStruct*) lpParam;
    for(int i = 0; i < deleteElems ->length; i++)
    {
        list->removeElement(0);
        list->removeElement(deleteElems->elementsToDelete[i]);
        _tprintf(_T("d: deleted %d \n"), deleteElems->elementsToDelete[i]);
        Sleep(rand()%10);
    }

    return 0;
}

void test()
{
    list = new LinkedList();
    srand(time(0));

    std::vector<HANDLE> handles;
    
    int arrayToAdd[] = {1, 2, 3, 4, 5, 6, 7};
    handles.push_back(CreateSimpleThread_s(addThread, &AddStruct(arrayToAdd, size(arrayToAdd))));  
    int arrayToAdd2[] = {-1, -2, -3, -4, -5, -6, -7};
    handles.push_back(CreateSimpleThread_s(addThread, &AddStruct(arrayToAdd2, size(arrayToAdd2))));  

    int findElements[] = {4, 4, 4, 3, 2, 10, 100};
    handles.push_back(CreateSimpleThread_s(findThread, &FindStruct(findElements, size(findElements))));  
    int findElements2[] = {-5, -5, -6, -7, -8, 3, -10};
    //handles.push_back(CreateSimpleThread_s(findThread, &FindStruct(findElements2, size(findElements2))));  
    
    int deleteElements[] = {-4, 3, 2, 10};
    handles.push_back(CreateSimpleThread_s(deleteThread, &DeleteStruct(deleteElements, size(deleteElements))));  
    int deleteElements2[] = {1, 5, 4, 7, 10};
    handles.push_back(CreateSimpleThread_s(deleteThread, &DeleteStruct(deleteElements2, size(deleteElements2))));  
    

    WaitForMultipleObjects(handles.size(), handles.data(), true, INFINITE);
    
    for(int i = 0; i < handles.size(); i++)
        CloseHandle_s(handles[i]);

    list->printAll();

    delete list;
}

int _tmain(int argc, _TCHAR* argv[])
{
    test();
    return 0;
}

