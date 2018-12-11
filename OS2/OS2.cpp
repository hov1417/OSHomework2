
#include "stdafx.h"

LinkedList<int>* list;

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
		_tprintf(_T("adding %d\n"), addElems->arrayToAdd[i]);
		list->addElement(addElems->arrayToAdd[i]);
		Sleep(rand()%10);
	}

	return 0;
}

void test()
{
	list = new LinkedList<int>();
	srand(time(0));

	const int threadCount = 2;
	HANDLE handles[threadCount];
	DWORD dwThreadIdArray[threadCount];
	
	int arrayToAdd[] = {1, 2, 3, 4, 5, 6, 7, 3};
	handles[0] = CreateThread(NULL, 0, addThread, &AddStruct(arrayToAdd, 8), 0, &dwThreadIdArray[0]);  
	
	int arrayToAdd2[] = {-1, -2, -3, -4, -5, -6, -7, -3};
	handles[1] = CreateThread(NULL, 0, addThread, &AddStruct(arrayToAdd2, 8), 0, &dwThreadIdArray[1]);  


	WaitForMultipleObjects(threadCount, handles, true, INFINITE);
	for(int i = 0; i < threadCount; i++)
	{
		CloseHandle(handles[i]);
	}
	list->printAll();

	delete list;
}

int _tmain(int argc, _TCHAR* argv[])
{
	test();
	return 0;
}

