#include "LogLevel.h"

LogLevel::LogLevel(const int& id, const char* name) :
    id(id),
    name(name) {
}
    
const char* LogLevel::get_name() const {
    return name;
}
    
const int LogLevel::get_id() const {
    return id;
}
    
bool LogLevel::accepts(const LogLevel& other_level) {
    return id >= other_level.id;        
}
    
LogLevel LogLevel::none(0, "none");
LogLevel LogLevel::error(1, "error");
LogLevel LogLevel::info(2, "info");
LogLevel LogLevel::debug(3, "debug");
