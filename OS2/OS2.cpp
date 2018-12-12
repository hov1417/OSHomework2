
#include "stdafx.h"

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
		_tprintf(_T("f: %s %d\n"), list->findElement(findElems->elementsToFind[i]) ? _T("finded") : _T("can't find"),
			findElems->elementsToFind[i]);
		//list->findElement(findElems->elementsToFind[i]);
		Sleep(rand()%10);
	}

	return 0;
}

void test()
{
	list = new LinkedList();
	srand(time((time_t)0));

	const int threadCount = 4;
	HANDLE handles[threadCount];
	
	int arrayToAdd[] = {1, 2, 3, 1, 4, 5, 6, 7, 3};
	handles[0] = CreateThread(NULL, 0, addThread, &AddStruct(arrayToAdd, 9), 0, NULL);  
	
	int arrayToAdd2[] = {-1, -2, -3, -4, -5, -6, -7, -3};
	handles[1] = CreateThread(NULL, 0, addThread, &AddStruct(arrayToAdd2, 8), 0, NULL);  

	int findElements[] = {4, 4, 4, 3, 2, 10, 100};
	handles[2] = CreateThread(NULL, 0, findThread, &FindStruct(findElements, 7), 0, NULL);  
	
	int findElements2[] = {-5, -5, -6, -7, -8, 3, -10};
	handles[3] = CreateThread(NULL, 0, findThread, &FindStruct(findElements2, 7), 0, NULL);  

	WaitForMultipleObjects(threadCount, handles, true, INFINITE);
	
	for(int i = 0; i < threadCount; i++)
		CloseHandle_s(handles[i]);

	list->printAll();

	delete list;
}

int _tmain(int argc, _TCHAR* argv[])
{
	test();
	return 0;
}

