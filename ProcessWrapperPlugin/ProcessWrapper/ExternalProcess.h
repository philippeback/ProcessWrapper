#ifndef EXTERNAL_PROCESS_H
#define EXTERNAL_PROCESS_H

#include "PipeFeeder.h"
#include "PipeReader.h"
#include "ProcessWaiter.h"
#include "SqueakSemaphore.h"
#include <windows.h>
#include <memory>

using std::auto_ptr;

class ExternalProcess {
    
    private: auto_ptr<PipeFeeder> stdin_feeder;
    private: auto_ptr<PipeReader> stdout_reader;
    private: auto_ptr<PipeReader> stderr_reader;
    private: auto_ptr<SqueakSemaphore> stdout_semaphore;
    private: auto_ptr<SqueakSemaphore> stderr_semaphore;

    private: HANDLE child_process;
    private: BOOL show_child_window;

	private: auto_ptr<ProcessWaiter> process_waiter;
	private: auto_ptr<SqueakSemaphore> waiter_semaphore;
			 
    public: ExternalProcess();
    
    public: ~ExternalProcess();

// pipes

    private: BOOL create_pipes(HANDLE* child_stdin, HANDLE* child_stdout, HANDLE* child_stderr);
    
    public: BOOL close_stdin();

    public: BOOL close_stdout();
    
    public: BOOL close_stderr();

    private: void close_pipes();
    
    private: BOOL close_handle(HANDLE* handle);

    public: BOOL create_process(char* command_line);

    public: BOOL show_window_at_startup();

    public: BOOL terminate();
    
    public: BOOL is_running() const;

	public: DWORD exit_code() const;
            
    private: void close_process_handles();

    public: BOOL write_to_stdin(const BYTE* buffer, DWORD length);
    
    public: DWORD read_from_stdout(BYTE* buffer, DWORD buffer_size);
    
    public: DWORD read_from_stderr(BYTE* buffer, DWORD buffer_size);
    
    public: void set_stdout_semaphore(auto_ptr<SqueakSemaphore> semaphore);
    
    public: void set_stderr_semaphore(auto_ptr<SqueakSemaphore> semaphore);    

    public: void set_waiter_semaphore(auto_ptr<SqueakSemaphore> semaphore);    			

};

#endif // EXTERNAL_PROCESS_H
