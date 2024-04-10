#include "log.h"

LogManager::LogManager(std::string path, bool withDate, std::string extension, bool print, bool save, bool enable)
{
    this->path = path + "_" + (withDate ? std::to_string(std::time(0)) : "") + "." + extension;
    logs = "";
    printLog = print;
    saveLog = save;
    isLogging = enable;
    log("LogManager initialized");
}

LogManager::~LogManager()
{
    log("LogManager destroyed");
    if (saveLog && logs != "")
        save();
}

void LogManager::print()
{
    std::cout << logs << "\n";
}

void LogManager::log(std::string message)
{
    // ["time"] : "message"
    if (isLogging)
    {
        std::string log = "[" + std::to_string(glfwGetTime()) + "]";
        log += " : ";
        log += message;
        log += "\n";
        logs += log;
        if (printLog)
            std::cout << log;
    }
}

void LogManager::log(std::string message, int frame)
{
    // ["time"]["frame"] : "message"
    if (isLogging)
    {
        std::string log = "[" + std::to_string(glfwGetTime()) + "]";
        log += "[" + std::to_string(frame) + "]";
        log += " : ";
        log += message;
        log += "\n";
        logs += log;
        if (printLog)
            std::cout << log;
    }
}

void LogManager::logQueue()
{
    if (isLogging)
    {
        for (int i = 0; i < logsQueue.size(); i++)
        {
            log(logsQueue[i]);
        }
        logsQueue.clear();
    }
}

void LogManager::logQueue(int frame)
{
    if (isLogging)
    {
        for (int i = 0; i < logsQueue.size(); i++)
        {
            log(logsQueue[i], frame);
        }
        logsQueue.clear();
    }
}

void LogManager::save()
{
    log("Saving logs to " + path);
    std::ofstream file;
    file.open(path);
    file << logs;
    file.close();
}

void LogManager::save(std::string path)
{
    std::ofstream file;
    file.open(path);
    file << logs;
    file.close();
}

void Log::log(std::string message)
{
    logsQueue.push_back(message);
}