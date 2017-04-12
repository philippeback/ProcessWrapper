#include "Mutex.h"
#include <windows.h>

Mutex::Mutex() {
    handle = CreateMutex(NULL, FALSE, NULL);
}
    
Mutex::~Mutex() {
    if (handle != NULL) {
        CloseHandle(handle);
    }
}
    
BOOL Mutex::get() {
    return get(INFINITE);
}
    
BOOL Mutex::get(const DWORD& timeout_milliseconds) {
    return WaitForSingleObject(handle, timeout_milliseconds) == WAIT_OBJECT_0;
}
    
BOOL Mutex::release() {
    return ReleaseMutex(handle);    
}
