#pragma once

void ErrorExit();

HANDLE CreateSimpleMutex_s();

void WaitForMutex_s(HANDLE mutex);

#define CloseHandle_s(handle) \
	if(!CloseHandle(handle)) {\
		_tprintf(_T("CloseHandle error:\n"));\
		ErrorExit();\
	}


#define ReleaseMutex_s(handle) \
	if (!ReleaseMutex(this->addMutex)) {\
		printf("ReleaseMutex error:\n");\
        ErrorExit();\
    }

