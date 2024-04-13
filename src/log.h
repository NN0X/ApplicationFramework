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
    LogManager(std::string pathm, bool withDate, std::string extension, bool print, bool save, bool enable);
    ~LogManager();

    void print();

    void log(std::string message);
    void log(std::string message, int frame);

    void error(std::string message);
    void error(std::string message, int frame);

    void logQueue();
    void logQueue(int frame);

    void save();
    void save(std::string path);

    void setFlags(bool print, bool save, bool enable);
};

namespace Log
{
    void log(std::string message);
    void error(std::string message);
}

#endif