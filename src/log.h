#ifndef LOG_H
#define LOG_H

#include "include.h"

static std::vector<std::string> logsQueue;

class LogManager
{
private:
    std::string path;
    std::string logs;
    bool printLog;
    bool saveLog;
    bool isLogging;

public:
    LogManager(const std::string &path, bool withDate, const std::string &extension, bool print, bool save, bool enable);
    ~LogManager();

    void print();

    void log(const std::string &message);
    void log(const std::string &message, int frame);

    void error(const std::string &message);
    void error(const std::string &message, int frame);

    // update the log queue on separate thread for more accurate timing
    void logQueue();
    void logQueue(int frame);

    void save();
    void save(const std::string &path);

    void setFlags(bool print, bool save, bool enable);
};

namespace Log
{
    void log(const std::string &message);
    void error(const std::string &message);
}

#endif