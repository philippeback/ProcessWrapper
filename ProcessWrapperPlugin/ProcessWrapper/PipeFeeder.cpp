#include "PipeFeeder.h"
#include <windows.h>
#include "Logger.h"

PipeFeeder::PipeFeeder(HANDLE pipe_input) :
    pipe_input(pipe_input),
    thread(INVALID_HANDLE_VALUE),
    closed(false) {
}

PipeFeeder::~PipeFeeder() {
    if (!closed) {
        close();    
    }
    if (thread != INVALID_HANDLE_VALUE) {
        feed_event.signal();
        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
    }
}

    
BOOL PipeFeeder::create_thread() {
    if (thread != INVALID_HANDLE_VALUE) {
        return true;
    }
    DWORD thread_id;
    thread = CreateThread(NULL, 0, &(PipeFeeder::thread_function), this, 0, &thread_id);
    if (thread == NULL ) {
        thread = INVALID_HANDLE_VALUE;
    }
    return thread != INVALID_HANDLE_VALUE;
}
    
BOOL PipeFeeder::feed(const BYTE* buffer, DWORD length) {
    if (closed) {
        return false;
    }
    if (!create_thread()) {
        return false;
    }
    BOOL result = queue.put(buffer, length, DEFAULT_TIMEOUT);
    if (result) {
        feed_event.signal();
    }
    return result;
}
    
void PipeFeeder::close() {
    closed = true;
    if (thread == INVALID_HANDLE_VALUE) {
        if (pipe_input != INVALID_HANDLE_VALUE) {
            CloseHandle(pipe_input);
            pipe_input = INVALID_HANDLE_VALUE;
        }
    } else {
        feed_event.signal();
    }
}    

DWORD WINAPI PipeFeeder::thread_function(LPVOID instance_pointer) {
    PipeFeeder* instance = (PipeFeeder*)instance_pointer;
    HANDLE& pipe_input = instance->pipe_input;
    SharedBuffer& queue = instance->queue;
    Event& feed_event = instance->feed_event;
    DWORD length;
    BYTE buffer[4096];
    Logger::debug("Thread initialized.");
    while (!instance->closed) {
        Logger::debug("Thread: pipe open");        
        if (feed_event.wait(1000)) {
            Logger::debug("Thread: lock achieved");
            feed_event.reset();
            while ((length = queue.get(buffer, sizeof(buffer), 1000)) > 0) {
		if (length > sizeof(buffer)) {
                    Logger::debug("Thread: shared buffer is closed");
		    break;
		}		    
                Logger::debug("Thread: writing data to pipe");                  
                DWORD written;
                WriteFile(pipe_input, buffer, length, &written, NULL);
                Logger::debug("Thread: data written to pipe");                
            }
        } else {
            Logger::debug("Thread: lock timeout");
        }
    }
    while ((length = queue.get(buffer, sizeof(buffer), 1000)) > 0) {
	if (length > sizeof(buffer)) {
            Logger::debug("Thread finalization: shared buffer is closed");
            break;
	}		    
        DWORD written;
        Logger::debug("Thread finalization: writing data to pipe");                                
        WriteFile(pipe_input, buffer, length, &written, NULL);
        Logger::debug("Thread finalization: data written to pipe");                
    }
    Logger::debug("Thread closes handle.");    
    if (pipe_input != INVALID_HANDLE_VALUE) {
        CloseHandle(pipe_input);
        pipe_input = INVALID_HANDLE_VALUE;
    }
    return 0;
}

