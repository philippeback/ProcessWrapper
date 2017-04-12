#ifndef SHARED_BUFFER_H
#define SHARED_BUFFER_H

#include "Mutex.h"
#include <queue>
#include <windows.h>

class SharedBuffer {
  
    private: BOOL closed;
    private: Mutex mutex;
    private: std::queue<BYTE> queue;

    public: SharedBuffer();
  
    public: BOOL close();

    public: BOOL close(DWORD timeout_milliseconds);
	    
    public: BOOL put(const BYTE* buffer, DWORD length);
    
    public: BOOL put(const BYTE* buffer, DWORD length, DWORD timeout_milliseconds);
    
    public: DWORD get(BYTE* buffer, DWORD length);

    public: DWORD get(BYTE* buffer, DWORD length, DWORD timeout_milliseconds);
    
};

#endif // SHARED_BUFFER_H
