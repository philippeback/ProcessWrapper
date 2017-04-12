#include "PipeReader.h"
#include "Logger.h"

#include <windows.h>

PipeReader::PipeReader(HANDLE pipe_output, auto_ptr<SqueakSemaphore> semaphore) :
    pipe_output(pipe_output),
    thread(INVALID_HANDLE_VALUE),
    closed(false),
    semaphore(semaphore) {
    if (!create_thread()) {
        Logger::error("PipeReader: couldn't create thread!");
        closed = true;
    } else {
        Logger::debug("PipeReader: thread created");
    }
}

PipeReader::~PipeReader() {
    if (!closed) {
        close();    
    }
    if (thread != INVALID_HANDLE_VALUE) {
        Logger::debug("PipeReader: thread is still running");
        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
    }
}

void PipeReader::close() {
    Logger::debug("PipeReader: close");
    closed = true;
    if (pipe_output != INVALID_HANDLE_VALUE) {
        CloseHandle(pipe_output);
        pipe_output = INVALID_HANDLE_VALUE;
        Logger::debug("PipeReader: pipe_output closed");
    } 
}

DWORD PipeReader::read(BYTE* buffer, DWORD length) {
    return queue.get(buffer, length);
}    
 
BOOL PipeReader::create_thread() {
    if (thread != INVALID_HANDLE_VALUE) {
        return true;
    }
    DWORD thread_id;
    thread = CreateThread(NULL, 0, &(PipeReader::thread_function), this, 0, &thread_id);
    if (thread == NULL ) {
        thread = INVALID_HANDLE_VALUE;
	return false;
    }
    return true;
}

DWORD WINAPI PipeReader::thread_function(LPVOID instance_pointer) {
    Logger::debug("PipeReader: Thread: Thread started.");
    PipeReader* instance = (PipeReader*)instance_pointer;
    DWORD length;
    HANDLE pipe_output = instance->pipe_output;
    SharedBuffer& queue = instance->queue;
    BYTE buffer[4096];
    Logger::debug("PipeReader: Thread: Thread initialized.");
    while (!instance->closed) {
        Logger::debug("PipeReader: Thread: reading pipe");
        if (ReadFile(pipe_output, buffer, sizeof(buffer), &length, NULL) == 0) {
            // Pipe closed or error occured, leave
            if (GetLastError() == ERROR_BROKEN_PIPE) {
                Logger::debug("PipeReader: Thread: Pipe closed.");
            } else {
                Logger::error("PipeReader: Thread: Error occured while reading pipe.");
            }
            break;
        }
        Logger::debug("PipeReader: Thread: writing data to queue");
        queue.put(buffer, length);      
        Logger::debug("PipeReader: Thread: data written to queue");
        instance->semaphore->signal();
        Logger::debug("PipeReader: Thread: semaphore signaled");
    }
    Logger::debug("PipeReader: Thread: closing shared buffer");
    queue.close();
    Logger::debug("PipeReader: Thread: sending last signal to semaphore");
    instance->semaphore->signal();
    Logger::debug("PipeReader: Thread: Thread terminating.");    
    return 0;
}

