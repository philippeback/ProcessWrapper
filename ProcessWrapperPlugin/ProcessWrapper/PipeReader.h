#ifndef PIPE_READER_H
#define PIPE_READER_H

#include "Event.h"
#include "SharedBuffer.h"
#include "SqueakSemaphore.h"
#include <windows.h>
#include <memory>

using std::auto_ptr;

class PipeReader {
  
    private: HANDLE pipe_output;  
  
    private: HANDLE thread;
    
    private: SharedBuffer queue;
    
    private: BOOL closed;

    private: auto_ptr<SqueakSemaphore> semaphore;
    
    public: PipeReader(HANDLE pipe_output, auto_ptr<SqueakSemaphore> semaphore);
    
    public: ~PipeReader();
    
    public: void close();
    
    public: DWORD read(BYTE* buffer, DWORD length);

    private: BOOL create_thread();

    
    private: static DWORD WINAPI thread_function(LPVOID instance_pointer);    
    
};

#endif // PIPE_READER_H
