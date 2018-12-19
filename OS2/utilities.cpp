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
        MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );
    
	_tprintf(_T("%s\n"), lpMsgBuf);
    LocalFree(lpMsgBuf);
    ExitProcess(1); // for collecting statistics, BatchRun.cmd
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
    if(!CloseHandle(handle))
    {
        _tprintf(_T("CloseHandle error:\n"));
        ErrorExit();
    }
}


void ReleaseMutex_s(HANDLE handle) 
{
    if (!ReleaseMutex(handle))
    {
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


void WaitForObjects_s(int size, HANDLE handles[])
{
    DWORD waitRes = WaitForMultipleObjects(size, handles, true, INFINITE);

    if (waitRes != WAIT_OBJECT_0)
    {
        printf("WAIT_ABANDONED | WAIT_TIMEOUT | WAIT_FAILED error:\n");
        ErrorExit();
    }
}

HANDLE CreateSimpleEvent_s() 
{
    HANDLE _event = CreateEvent(NULL, TRUE, FALSE, NULL); 

    if (_event == NULL) 
    { 
        _tprintf(_T("CreateEvent failed:\n"));
        ErrorExit();
    }
    return _event;
}

void ResetEvent_s(HANDLE handle)
{
    if(!ResetEvent(handle))
    {
        printf("ResetEvent error:\n");
        ErrorExit();
    }
}

void SetEvent_s(HANDLE handle)
{
    if (!SetEvent(handle)) 
    {
        printf("SetEvent failed:\n");
        ErrorExit();
    }
}
