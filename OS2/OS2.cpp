#include "stdafx.h"
#include <vector>

void test()
{
    LinkedList list;
    srand(static_cast<unsigned int>(time(0)));

    std::vector<HANDLE> handles;

    int arrayToAdd[] = {1, 2, 3, 4, 5, 6, 7, 20, 1000};
    handles.push_back(CreateSimpleThread_s(addThread, &ThreadConfig(arrayToAdd, size(arrayToAdd), &list)));  
    int arrayToAdd2[] = {-1, -2, -3, -4, -5, -6, -7};
    handles.push_back(CreateSimpleThread_s(addThread, &ThreadConfig(arrayToAdd2, size(arrayToAdd2), &list)));  
    int arrayToAdd3[] = {-1, 2, -3, -4, -5, 6, -77, 20};
    handles.push_back(CreateSimpleThread_s(addThread, &ThreadConfig(arrayToAdd3, size(arrayToAdd3), &list)));  
    int arrayToAdd4[] = {-1, 22, -3, -4, 55, 6};
    handles.push_back(CreateSimpleThread_s(addThread, &ThreadConfig(arrayToAdd4, size(arrayToAdd4), &list)));  

    int findElements[] = {4, 4, 4, 3, 2, 10, -3};
    handles.push_back(CreateSimpleThread_s(findThread, &ThreadConfig(findElements, size(findElements), &list)));  
    int findElements2[] = {-5, -5, -6, -7, 8, 3, -3};
    handles.push_back(CreateSimpleThread_s(findThread, &ThreadConfig(findElements2, size(findElements2), &list)));  
    int findElements3[] = {5, -5, 36, -7, -8, 3, 20};
    handles.push_back(CreateSimpleThread_s(findThread, &ThreadConfig(findElements3, size(findElements3), &list)));  
    int findElements4[] = {5, 5, 43, -7, 8, 3, -1};
    handles.push_back(CreateSimpleThread_s(findThread, &ThreadConfig(findElements4, size(findElements4), &list)));  

    int deleteElements[] = {-4, 3, 2, 3};
    handles.push_back(CreateSimpleThread_s(deleteThread, &ThreadConfig(deleteElements, size(deleteElements), &list)));
    int deleteElements2[] = {1, 5, 2, 22, -3};
    handles.push_back(CreateSimpleThread_s(deleteThread, &ThreadConfig(deleteElements2, size(deleteElements2), &list)));
    int deleteElements3[] = {-1, 4, -1, -5, 55};
    handles.push_back(CreateSimpleThread_s(deleteThread, &ThreadConfig(deleteElements3, size(deleteElements3), &list)));
    int deleteElements4[] = {-1, 55, 20, -77, -77};
    handles.push_back(CreateSimpleThread_s(deleteThread, &ThreadConfig(deleteElements4, size(deleteElements4), &list)));

    WaitForObjects_s(handles.size(), handles.data());

    for(size_t i = 0; i < handles.size(); i++)
        CloseHandle_s(handles[i]);

    list.printAll();
}

int _tmain(int argc, _TCHAR* argv[])
{
    test();
    return 0;
}

