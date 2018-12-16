#include "stdafx.h"
#include <vector>

void test()
{
    LinkedList list;
    srand(static_cast<unsigned int>(time(0)));

    std::vector<HANDLE> handles;

    int arrayToAdd[] = {1, 2, 3, 4, 5, 6, 7};
    handles.push_back(CreateSimpleThread_s(addThread, &ThreadConfig(arrayToAdd, size(arrayToAdd), &list)));  
    int arrayToAdd2[] = {-1, -2, -3, -4, -5, -6, -7};
    handles.push_back(CreateSimpleThread_s(addThread, &ThreadConfig(arrayToAdd2, size(arrayToAdd2), &list)));  

    int findElements[] = {4, 4, 4, 3, 2, 10, 100};
    handles.push_back(CreateSimpleThread_s(findThread, &ThreadConfig(findElements, size(findElements), &list)));  
    int findElements2[] = {-5, -5, -6, -7, -8, 3, -10};
    handles.push_back(CreateSimpleThread_s(findThread, &ThreadConfig(findElements2, size(findElements2), &list)));  

    int deleteElements[] = {-4, 3, 2, 3};
    handles.push_back(CreateSimpleThread_s(deleteThread, &ThreadConfig(deleteElements, size(deleteElements), &list)));  
    int deleteElements2[] = {1, 5, 4, 7, 10};
    handles.push_back(CreateSimpleThread_s(deleteThread, &ThreadConfig(deleteElements2, size(deleteElements2), &list)));  


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

