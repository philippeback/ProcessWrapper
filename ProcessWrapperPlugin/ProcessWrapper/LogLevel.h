#ifndef LOGLEVEL_H
#define LOGLEVEL_H

class LogLevel {
    
    private: const int id;
    
    private: const char* name;
    
    public: LogLevel(const int& id, const char* name);
    
    public: const char* get_name() const;
    
    public: const int get_id() const;
    
    public: bool accepts(const LogLevel& other_level);
    
    public: static LogLevel none;
    public: static LogLevel error;
    public: static LogLevel info;
    public: static LogLevel debug;

};

#endif // LOGLEVEL_H
