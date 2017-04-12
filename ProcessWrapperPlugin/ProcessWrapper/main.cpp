#include "Logger.h"
#include "ExternalProcess.h"
#include "SqueakSemaphore.h"
#include <memory>

using std::auto_ptr;

#ifdef DLL
#define Export __declspec(Export)
#else
#define Export 
#endif

extern "C" {

// Process creation
Export ExternalProcess* new_process() {
    return new ExternalProcess();
}

Export void remove_process(ExternalProcess* process) {
    delete process;
}

// ExternalProcess functions

// Process execution/termination
Export BOOL start_process(ExternalProcess* process, char* command_line) {
    return process->create_process(command_line);
}

Export BOOL show_window_at_startup(ExternalProcess* process) {     
    return process->show_window_at_startup();
}

Export BOOL terminate(ExternalProcess* process) {
    return process->terminate();
}

Export BOOL is_running(ExternalProcess* process) {
    return process->is_running();
}

Export DWORD exit_code(ExternalProcess* process) {
    return process->exit_code();
}

Export void set_waiter_semaphore(ExternalProcess* process, int semaphore) {
    process->set_waiter_semaphore(auto_ptr<SqueakSemaphore>(new SqueakSemaphore(semaphore)));
}

// stdin access
Export BOOL write_to_stdin(ExternalProcess* process, BYTE* message, DWORD length) {
    return process->write_to_stdin(message, length);
}

Export BOOL close_stdin(ExternalProcess* process) {
    return process->close_stdin();
}

// stdout access
Export DWORD read_from_stdout(ExternalProcess* process, BYTE* buffer, DWORD buffer_size) {
    return process->read_from_stdout(buffer, buffer_size);
}

Export void set_stdout_semaphore(ExternalProcess* process, int semaphore) {
    process->set_stdout_semaphore(auto_ptr<SqueakSemaphore>(new SqueakSemaphore(semaphore)));
}

Export BOOL close_stdout(ExternalProcess* process) {
	return process->close_stdout();
}

// stderr access
Export DWORD read_from_stderr(ExternalProcess* process, BYTE* buffer, DWORD buffer_size) {
    return process->read_from_stderr(buffer, buffer_size);
}

Export void set_stderr_semaphore(ExternalProcess* process, int semaphore) {
    process->set_stderr_semaphore(auto_ptr<SqueakSemaphore>(new SqueakSemaphore(semaphore)));
}

Export BOOL close_stderr(ExternalProcess* process) {
	return process->close_stderr();
}

//Logging
Export void log_level_none() {
    Logger::set_log_level(&LogLevel::none);
}

Export void log_level_error() {
    Logger::set_log_level(&LogLevel::error);
}

Export void log_level_info() {
    Logger::set_log_level(&LogLevel::info);
}

Export void log_level_debug() {
    Logger::set_log_level(&LogLevel::debug);
}

Export void log_test() {
    Logger::debug("test debug");
    Logger::info("test info");
    Logger::error("test error");        
}

}
