#ifndef PIPE_FEEDER_H
#define PIPE_FEEDER_H

#include "Event.h"
#include "SharedBuffer.h"
#include <windows.h>

#ifndef DEFAULT_TIMEOUT
#define DEFAULT_TIMEOUT 1000
#endif

class PipeFeeder {
    
    private: HANDLE pipe_input;
    
    private: HANDLE thread;
    
    private: SharedBuffer queue;
    
    private: Event feed_event;
    
    private: BOOL closed;
    
    public: PipeFeeder(HANDLE pipe_input);
    
    private: BOOL create_thread();
    
    public: BOOL feed(const BYTE* buffer, DWORD length);
    
    public: ~PipeFeeder();
    
    public: void close();
    
    private: static DWORD WINAPI thread_function(LPVOID instance_pointer);
    
};

#endif // PIPE_FEEDER_H
