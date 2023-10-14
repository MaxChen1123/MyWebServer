#include"./Logger.h"

Logger::Logger(const char *f) : _log(f, std::ios::out | std::ios::app),
                                _level(INFO),
                                _line_level(VERBOSE),
                                _default_line_level(VERBOSE)
{
    assert(_log.is_open());
}

Logger::Logger(const std::string &f) : _log(f, std::ios::out | std::ios::app),
                                _level(INFO),
                                _line_level(VERBOSE),
                                _default_line_level(VERBOSE)
{
    assert(_log.is_open());
}

void Logger::log(const logger_level& _logger_level, const char* fmt, ...){
    std::lock_guard<std::mutex> lock(mtx);

    char buf[1024];
    va_list args;
    va_start(args, fmt);
    _log<<level_str(_logger_level)<<' '<<get_time()<<' ';
    vsnprintf(buf, sizeof(buf), fmt, args);
    _log<<buf<<std::endl;

    _log.flush();
    va_end(args);
}

Logger::~Logger()
{
    if (_log.is_open())
    {
        _log.flush();
        _log.close();
    }
}

void Logger::set_level(const logger_level &level)
{
    _level = level;
}

void Logger::set_default_line_level(const logger_level &level)
{
    _default_line_level = level;
}

std::string Logger::get_time() const
{
    struct tm *timeinfo;
    time_t rawtime;
    char *time_buf;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    time_buf = asctime(timeinfo);

    std::string ret(time_buf);
    if (!ret.empty() && ret[ret.length() - 1] == '\n')
    {
        ret.erase(ret.length() - 1);
    }

    return (ret);
}

inline const char *Logger::level_str(const logger_level &level)
{
    switch (level)
    {
    case VERBOSE:
        return ("VRB");
    case DEBUG:
        return ("DBG");
    case INFO:
        return ("INF");
    case WARNING:
        return ("WRN");
    case ERROR:
        return ("ERR");
    case CRITICAL:
        return ("CRT");
    default:
        assert(false);
    }
}