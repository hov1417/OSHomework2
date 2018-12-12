#include "StdAfx.h"
#include "utilities.h"

void ErrorExit() 
{
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    LocalFree(lpMsgBuf);
    ExitProcess(dw); 
}

HANDLE CreateSimpleMutex_s() {
	HANDLE mutex = CreateMutex(NULL, FALSE, NULL);
    if (mutex == NULL) 
    {
        printf("CreateMutex error:\n");
		ErrorExit();
    }
	return mutex;
}

void WaitForMutex_s(HANDLE mutex) {
	DWORD waitResult = WaitForSingleObject(mutex, INFINITE);
	if (waitResult != WAIT_OBJECT_0) 
    {
		printf("WAIT_ABANDONED | WAIT_TIMEOUT | WAIT_FAILED error:\n");
        ErrorExit();
	}
}