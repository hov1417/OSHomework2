#include "StdAfx.h"
#include "ThreadFunctions.h"

DWORD WINAPI addThread(LPVOID lpParam)
{
    ThreadConfig* params = (ThreadConfig*) lpParam;

    for(int i = 0; i < params->length; i++)
    {
        params->list->addElement(params->elements[i]);
        _tprintf(_T("a: added %d\n"), params->elements[i]);
        Sleep(rand()%10);
    }

    return 0;
}

DWORD WINAPI findThread(LPVOID lpParam)
{
    ThreadConfig* params = (ThreadConfig*) lpParam;

    for(int i = 0; i < params->length; i++)
    {
        _tprintf(_T("f: %s %d\n"), 
            params->list->findElement(params->elements[i]) ? _T("found") : _T("can't find"),
            params->elements[i]);
        Sleep(rand()%10);
    }

    return 0;
}

DWORD WINAPI deleteThread(LPVOID lpParam)
{
    ThreadConfig* params = (ThreadConfig*) lpParam;

    for(int i = 0; i < params->length; i++)
    {
        bool res = params->list->removeElement(params->elements[i]);
        _tprintf(_T("d: %s %d\n"), 
            res ? _T("deleted") : _T("can't delete"),
            params->elements[i]);
        Sleep(rand()%10);
    }

    return 0;
}
