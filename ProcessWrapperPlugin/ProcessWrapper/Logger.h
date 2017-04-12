#ifndef LOGGER_H
#define LOGGER_H

#include "Mutex.h"
#include "LogLevel.h"

class Logger {
  
    private: static Logger* get_instance();
  
    private: static Logger* instance;
    
    private: LogLevel* log_level;
    
    private: Mutex mutex;
    
    private: Logger(LogLevel* log_level);
  
    private: Logger(const Logger&);
    
    private: Logger& operator=(const Logger&);
    
    private: void log(LogLevel* level , const char* message);
    
    public: static LogLevel* get_log_level();
    
    public: static void set_log_level(LogLevel* log_level);

    public: static void debug(const char* message);
    
    public: static void info(const char* message);
    
    public: static void error(const char* message);
    
};

#endif // LOGGER_H
