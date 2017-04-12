#include "ExternalProcess.h"
#include <windows.h>
#include "Logger.h"

ExternalProcess::ExternalProcess() :
    child_process(INVALID_HANDLE_VALUE),
    show_child_window(false) {
}
    
ExternalProcess::~ExternalProcess() {
    if (process_waiter.get() != NULL && process_waiter->is_running()) {
        terminate();
    }
    close_pipes();
    close_process_handles();
}

// pipes

BOOL ExternalProcess::create_pipes(HANDLE* child_stdin, HANDLE* child_stdout, HANDLE* child_stderr) {
    HANDLE current_process = GetCurrentProcess();

    SECURITY_ATTRIBUTES pipe_security_attributes;
    ZeroMemory(&pipe_security_attributes, sizeof(pipe_security_attributes));    
    pipe_security_attributes.nLength = sizeof(pipe_security_attributes);
    pipe_security_attributes.bInheritHandle = TRUE;
    pipe_security_attributes.lpSecurityDescriptor = NULL;

    HANDLE handles[6];
    
    // Initialize stdin
    HANDLE stdin_input;
    if (CreatePipe(&handles[0], &handles[1], &pipe_security_attributes, 0) == 0) {
        Logger::error("CreatePipe(stdin)");
        return false;
    }
    if (!DuplicateHandle(current_process, handles[1], current_process, &stdin_input, 0, FALSE, DUPLICATE_SAME_ACCESS | DUPLICATE_CLOSE_SOURCE)) {
        Logger::error("DuplicateHandle(stdin)");
        return false;
    }
    *child_stdin = handles[0];
    stdin_feeder.reset(new PipeFeeder(stdin_input));

    if (stdout_semaphore.get() != NULL) {    
        // Initialize stdout
        HANDLE stdout_output;
        if (CreatePipe(&handles[2], &handles[3], &pipe_security_attributes, 0) == 0) {
            Logger::error("CreatePipe(stdout)");
            return false;
        }
        if (!DuplicateHandle(current_process, handles[2], current_process, &stdout_output, 0, FALSE, DUPLICATE_SAME_ACCESS | DUPLICATE_CLOSE_SOURCE)) {
            Logger::error("DuplicateHandle(stdout)");
            return false;
        }
        *child_stdout = handles[3];
        stdout_reader.reset(new PipeReader(stdout_output, stdout_semaphore));
    }

    if (stderr_semaphore.get() != NULL) {
        HANDLE stderr_output;
        if (CreatePipe(&handles[4], &handles[5], &pipe_security_attributes, 0) == 0) {
            Logger::error("CreatePipe(stderr)");
            return false;
        }
        if (!DuplicateHandle(current_process, handles[4], current_process, &stderr_output, 0, FALSE, DUPLICATE_SAME_ACCESS | DUPLICATE_CLOSE_SOURCE)) {
            Logger::error("DuplicateHandle(stderr)");
            return false;
        }
        *child_stderr = handles[5];
        stderr_reader.reset(new PipeReader(stderr_output, stderr_semaphore));
    }
    return true;
}
    
BOOL ExternalProcess::close_stdin() {
    if (stdin_feeder.get() == NULL) {
        return false;
    }
    stdin_feeder->close();
    return true;
}    

BOOL ExternalProcess::close_stdout() {
    if (stdout_reader.get() == NULL) {
        return false;
    }
    stdout_reader->close();
    return true;
}

BOOL ExternalProcess::close_stderr() {
    if (stderr_reader.get() == NULL) {
        return false;
    }
    stderr_reader->close();
    return true;
}

void ExternalProcess::close_pipes() {
    close_stdin();
    close_stdout();
    close_stderr();    
}
    
BOOL ExternalProcess::close_handle(HANDLE* handle) {
    if (*handle != INVALID_HANDLE_VALUE && !CloseHandle(*handle)) {
        Logger::error("CloseHandle");
        return false;
    }
    *handle = INVALID_HANDLE_VALUE;
    return true;
}

BOOL ExternalProcess::create_process(char* command_line) {
    HANDLE child_stdin = INVALID_HANDLE_VALUE;
    HANDLE child_stdout = INVALID_HANDLE_VALUE;
    HANDLE child_stderr = INVALID_HANDLE_VALUE;
    if (!create_pipes(&child_stdin, &child_stdout, &child_stderr)) {
        close_handle(&child_stdin);
        close_handle(&child_stdout);
        close_handle(&child_stderr);
        return false;
    }
    STARTUPINFO startup_information;
    ZeroMemory(&startup_information, sizeof(startup_information));
    startup_information.cb = sizeof(startup_information);
    startup_information.hStdInput = child_stdin;
    startup_information.hStdOutput = child_stdout;
    startup_information.hStdError = child_stderr;
    startup_information.dwFlags |= STARTF_USESTDHANDLES;
    if (!show_child_window) {
        startup_information.dwFlags |= STARTF_USESHOWWINDOW;
    }
    startup_information.wShowWindow = SW_HIDE; // Hide the window of the application!
    PROCESS_INFORMATION process_information;
    ZeroMemory(&process_information, sizeof(process_information));    
    
    BOOL startup_success = CreateProcess(
        NULL,
        command_line,
        NULL,
        NULL,
        TRUE,
        0,
        NULL,
        NULL,
        &startup_information,
        &process_information);
    
    if (!startup_success) {
        Logger::error("CreateProcess");
    } else {
        close_handle(&process_information.hThread);
        child_process = process_information.hProcess;
		process_waiter.reset(new ProcessWaiter(child_process, waiter_semaphore));
    }
    
    close_handle(&child_stdin);
    close_handle(&child_stdout);
    close_handle(&child_stderr);
    return startup_success;
}

BOOL ExternalProcess::show_window_at_startup() {
    return (show_child_window = !show_child_window);
}

BOOL ExternalProcess::terminate() {
    close_pipes();
    if (!TerminateProcess(child_process, 0)) {
        Logger::error("ExternalProcess::terminate TerminateProcess failed");
        return false;
    }
    close_process_handles();
    return true;
}

BOOL ExternalProcess::is_running() const {
    if (process_waiter.get() == NULL) {
		return false;
	}
	return process_waiter->is_running();
}

DWORD ExternalProcess::exit_code() const {
	if (process_waiter.get() == NULL) {
        Logger::error("ExternalProcess::exit_code called with no process_waiter");
		return (DWORD)-1;
	}
	return process_waiter->get_exit_code();
}
        
void ExternalProcess::close_process_handles() {
    close_handle(&child_process);
}

BOOL ExternalProcess::write_to_stdin(const BYTE* buffer, DWORD length) {
    if (stdin_feeder.get() == NULL) {
        return false;
    }
    return stdin_feeder->feed(buffer, length);
}
    
DWORD ExternalProcess::read_from_stdout(BYTE* buffer, DWORD buffer_size) {
    if (stdout_reader.get() == NULL) {
        return 0;
    }
    return stdout_reader->read(buffer, buffer_size);
}
    
DWORD ExternalProcess::read_from_stderr(BYTE* buffer, DWORD buffer_size) {
    if (stderr_reader.get() == NULL) {
        return 0;
    }
    return stderr_reader->read(buffer, buffer_size);
}
    
void ExternalProcess::set_stdout_semaphore(auto_ptr<SqueakSemaphore> semaphore) {
    stdout_semaphore = semaphore;   
}

void ExternalProcess::set_stderr_semaphore(auto_ptr<SqueakSemaphore> semaphore) {
    stderr_semaphore = semaphore;   
}

void ExternalProcess::set_waiter_semaphore(auto_ptr<SqueakSemaphore> semaphore) {
    waiter_semaphore = semaphore;   
}
