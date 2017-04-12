#ifndef PROCESS_WAITER_H
#define PROCESS_WAITER_H

#include <windows.h>
#include "SqueakSemaphore.h"
#include <memory>

using std::auto_ptr;

class ProcessWaiter {
    
    private: HANDLE process;
    private: HANDLE thread;
    private: auto_ptr<SqueakSemaphore> semaphore;
    private: DWORD exit_code;
    private: bool running;
	     
    public: ProcessWaiter(HANDLE process, auto_ptr<SqueakSemaphore> semaphore);
    
    public: ~ProcessWaiter();

    public: bool is_running() const;

    public: DWORD get_exit_code() const;
	    
    private: void set_exit_code();
	    
    private: BOOL create_thread();

    private: static DWORD WINAPI thread_function(LPVOID instance_pointer);
    
};

#endif // PROCESS_WAITER_H
