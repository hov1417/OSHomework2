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

HANDLE CreateSimpleMutex_s()
{
    HANDLE mutex = CreateMutex(NULL, FALSE, NULL);
    if (mutex == NULL) 
    {
        printf("CreateMutex error:\n");
        ErrorExit();
    }
    return mutex;
}

void WaitForObject_s(HANDLE obj) 
{
    DWORD waitResult = WaitForSingleObject(obj, INFINITE);
    if (waitResult != WAIT_OBJECT_0) 
    {
        printf("WAIT_ABANDONED | WAIT_TIMEOUT | WAIT_FAILED error:\n");
        ErrorExit();
    }
}

void CloseHandle_s(HANDLE handle) 
{
    if(!CloseHandle(handle)) {
        _tprintf(_T("CloseHandle error:\n"));
        ErrorExit();
    }
}


void ReleaseMutex_s(HANDLE handle) 
{
    if (!ReleaseMutex(handle)) {
        printf("ReleaseMutex error:\n");
        ErrorExit();
    }
}
    
 
HANDLE CreateSimpleThread_s(LPTHREAD_START_ROUTINE function, LPVOID args)
{
    HANDLE handle = CreateThread(NULL, 0, function, args, 0, NULL);
    if(handle == NULL) 
    {
        printf("CreateThread error:\n");
        ErrorExit();
    }
    return handle;
}
