#ifndef MUTEX_H
#define MUTEX_H

#include <windows.h>

class Mutex {
    
    private: HANDLE handle;
    
    public: Mutex();
    
    public: ~Mutex();

    private: Mutex(const Mutex&);

    private: Mutex& operator=(const Mutex&);    
    
    public: BOOL get();
    
    public: BOOL get(const DWORD& timeout_milliseconds);
    
    public: BOOL release();
        
};

#endif // MUTEX_H
