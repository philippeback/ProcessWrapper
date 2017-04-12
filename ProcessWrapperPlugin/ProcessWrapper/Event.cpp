#include "Event.h"
#include <windows.h>

Event::Event(const BOOL& manual_reset, const BOOL& signaled) {
    handle = CreateEvent(NULL, manual_reset, signaled, NULL);
}
    
Event::~Event() {
    if (handle != NULL) {
        CloseHandle(handle);
    }
}
    
BOOL Event::wait() {
    return wait(INFINITE);    
}
    
BOOL Event::wait(const DWORD& timeout_milliseconds) {
    return WaitForSingleObject(handle, timeout_milliseconds) == WAIT_OBJECT_0;
}
    
BOOL Event::signal() {
    return SetEvent(handle);
}
    
BOOL Event::reset() {
    return ResetEvent(handle);   
}

