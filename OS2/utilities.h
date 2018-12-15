#pragma once

#include "stdafx.h"

template<class T, size_t N>
const size_t size(T (&)[N]) { return N; }

void ErrorExit();

HANDLE CreateSimpleMutex_s();

// mutex or event
void WaitForObject_s(HANDLE obj);

void CloseHandle_s(HANDLE handle);

void ReleaseMutex_s(HANDLE handle);

HANDLE CreateSimpleThread_s(LPTHREAD_START_ROUTINE function, LPVOID args);
