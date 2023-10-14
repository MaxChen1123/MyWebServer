#pragma once
#include <fstream>
#include <cassert>
#include <ctime>
#include <sstream>
#include <mutex>
#include <cstdarg>

typedef enum {
  VERBOSE = 0,
  DEBUG,
  INFO,
  WARNING,
  ERROR,
  CRITICAL
} logger_level;



class Logger{
public:
    Logger(const char *f);
    Logger(const std::string& f);
    ~Logger();
    
    
    void set_level(const logger_level& level);
    void set_default_line_level(const logger_level& level);
    void log(const logger_level& level, const char* fmt, ...);
    
private:
    std::string get_time() const;
    inline const char* level_str(const logger_level& level);
    
    std::ofstream  _log;
    logger_level   _level;
    logger_level   _line_level;
    logger_level   _default_line_level;
    std::mutex mtx;
};


