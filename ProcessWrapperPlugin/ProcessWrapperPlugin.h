#ifndef PROCESS_WRAPPER_PLUGIN_H
#define PROCESS_WRAPPER_PLUGIN_H

#include <windows.h>

/* Process creation */

DWORD new_process();

BOOL remove_process(DWORD process);

/* ExternalProcess functions */

/* Process execution/termination */
BOOL start_process(DWORD process, char* command_line);

BOOL show_window_at_startup(DWORD process);

BOOL terminate(DWORD process);

BOOL is_running(DWORD process);

DWORD exit_code(DWORD process);

void set_waiter_semaphore(DWORD process, DWORD semaphore);

// stdin access
BOOL write_to_stdin(DWORD process, BYTE* message, DWORD length);

BOOL close_stdin(DWORD process);

// stdout access
void set_stdout_semaphore(DWORD process, DWORD semaphore);

DWORD read_from_stdout(DWORD process, BYTE* buffer, DWORD buffer_size);

BOOL close_stdout();

// stderr access
void set_stderr_semaphore(DWORD process, DWORD semaphore);

DWORD read_from_stderr(DWORD process, BYTE* buffer, DWORD buffer_size);

BOOL close_stderr();

//Logging
void log_level_none();

void log_level_error();

void log_level_info();

void log_level_debug();

void log_test();

#endif /* PROCESS_WRAPPER_PLUGIN_H */
