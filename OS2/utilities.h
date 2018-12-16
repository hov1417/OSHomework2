#pragma once

#include "stdafx.h"

template<class T, size_t n>
const size_t size(T (&)[n]) { return n; }

void ErrorExit();

HANDLE CreateSimpleMutex_s();

// mutex or event
void WaitForObject_s(HANDLE obj);

void CloseHandle_s(HANDLE handle);

void ReleaseMutex_s(HANDLE handle);

HANDLE CreateSimpleThread_s(LPTHREAD_START_ROUTINE function, LPVOID args);

void WaitForObjects_s(int size, HANDLE handles[]);

HANDLE CreateSimpleEvent_s();

void ResetEvent_s(HANDLE handle);

void SetEvent_s(HANDLE handle);

