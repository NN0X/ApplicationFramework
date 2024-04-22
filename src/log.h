#ifndef LOG_H
#define LOG_H

#include "include.h"
#include "utility.h"

namespace Logger
{
    static std::string path;
    static std::string logs;
    static int frame;
    static bool printLog;
    static bool saveLog;
    static bool isLogging;

    void init(const std::string &directory, bool withTime, const std::string &extension, bool print, bool save, bool enable);
    void quit();

    void update(int frame);

    bool checkInit();

    void print();

    void log(const std::string &message);
    void error(const std::string &message);

    void save();
    void save(const std::string &path);

    void setFlags(bool print, bool save, bool enable);

}

#endif