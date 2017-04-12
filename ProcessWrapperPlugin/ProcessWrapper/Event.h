#ifndef EVENT_H
#define EVENT_H

#include <windows.h>

class Event {
    
    private: HANDLE handle;
    
    public: Event(const BOOL& manual_reset = true, const BOOL& signaled = false);
    
    public: ~Event();

    private: Event(const Event&);

    private: Event& operator=(const Event&);    
    
    public: BOOL wait();
    
    public: BOOL wait(const DWORD& timeout_milliseconds);
    
    public: BOOL signal();
    
    public: BOOL reset();
    
};

#endif // EVENT_H
