#include "Logger.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

Logger* Logger::get_instance() {
    if (instance == NULL) {
        instance = new Logger(&LogLevel::none);
    }
    return instance;
}
  
Logger* Logger::instance = NULL;

Logger::Logger(LogLevel* log_level) :
    log_level(log_level) {
}

  
void Logger::log(LogLevel* level , const char* message) {
    if (!log_level->accepts(*level)) {
        return;
    }
    mutex.get();
    FILE* file = fopen("ProcessWrapper.log", "a");
    if (file != NULL) {
        time_t now;
        time(&now);
        tm* tmp = gmtime(&now);
        fprintf(file, "[%04d.%02d.%02d %02d:%02d:%02d] %s: %s\n", 
            tmp->tm_year + 1900, 
            tmp->tm_mon + 1,
            tmp->tm_mday,
            tmp->tm_hour,
            tmp->tm_min,
            tmp->tm_sec,
            level->get_name(),
            message); 
        fclose(file);
    }
    mutex.release();
}

LogLevel* Logger::get_log_level() {
    return get_instance()->log_level;
}
 
void Logger::set_log_level(LogLevel* log_level) {
    get_instance()->log_level = log_level;
}

#ifdef LOGGING_ENABLED    
void Logger::debug(const char* message) {
    get_instance()->log(&LogLevel::debug, message);
}
    
void Logger::info(const char* message) {
    get_instance()->log(&LogLevel::info, message);
}
    
void Logger::error(const char* message) {
    get_instance()->log(&LogLevel::error, message);
}
#else
void Logger::debug(const char* message) {
}
    
void Logger::info(const char* message) {
}
    
void Logger::error(const char* message) {
}
#endif
