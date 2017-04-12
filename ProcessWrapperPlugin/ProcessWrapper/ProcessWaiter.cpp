#include "ProcessWaiter.h"
#include "Logger.h"
 
ProcessWaiter::ProcessWaiter(HANDLE process, auto_ptr<SqueakSemaphore> semaphore) :
    process(process),
    thread(INVALID_HANDLE_VALUE),
    semaphore(semaphore),
    exit_code(STILL_ACTIVE),
    running(true) {
    if (!create_thread()) {
        Logger::error("ProcessWaiter::ProcessWaiter couldn't create thread!");
    } else {
        Logger::debug("PipeReader: thread created");
    }
        
}
    
ProcessWaiter::~ProcessWaiter() {
    if (thread != INVALID_HANDLE_VALUE) {
        semaphore->invalidate();
        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
    }
}
 
DWORD ProcessWaiter::get_exit_code() const {
    return exit_code;
}

void ProcessWaiter::set_exit_code() {
    if (!GetExitCodeProcess(process, &exit_code)) {
        Logger::error("ProcessWaiter::set_exit_code: GetExitCodeProcess failed");
    }
}

bool ProcessWaiter::is_running() const {
    return running;
}

BOOL ProcessWaiter::create_thread() {
    if (thread != INVALID_HANDLE_VALUE) {
        return true;
    }
    DWORD thread_id;
    thread = CreateThread(NULL, 0, &(ProcessWaiter::thread_function), this, 0, &thread_id);
    if (thread == NULL ) {
        thread = INVALID_HANDLE_VALUE;
        return false;
    }
    return true;
}

DWORD WINAPI ProcessWaiter::thread_function(LPVOID instance_pointer) {
    ProcessWaiter* instance = (ProcessWaiter*)instance_pointer;
    switch (WaitForSingleObject(instance->process, INFINITE)) {
        default:
            break;
        case WAIT_OBJECT_0: // successful process termination
            instance->set_exit_code();
            break;
        case WAIT_FAILED:
            Logger::error("ProcessWaiter::thread_function wait failed");
            break;
    }
	instance->running = false;
    instance->semaphore->signal();
    return 0;
}

