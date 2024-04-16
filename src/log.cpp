#include "log.h"

LogManager::LogManager(const std::string &path, bool withDate, const std::string &extension, bool print, bool save, bool enable)
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
    if (printLog)
        std::cin.get();
}

void LogManager::print()
{
    std::cout << logs << "\n";
}

void LogManager::log(const std::string &message)
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

void LogManager::log(const std::string &message, int frame)
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

void LogManager::error(const std::string &message)
{
    // ["time"] : "ERROR: message"
    if (isLogging)
    {
        std::string log = "[" + std::to_string(glfwGetTime()) + "]";
        log += " : ";
        log += "ERROR: ";
        log += message;
        log += "\n";
        logs += log;
        if (printLog)
            std::cout << log;
    }
}

void LogManager::error(const std::string &message, int frame)
{
    // ["time"]["frame"] : "ERROR: message"
    if (isLogging)
    {
        std::string log = "[" + std::to_string(glfwGetTime()) + "]";
        log += "[" + std::to_string(frame) + "]";
        log += " : ";
        log += "ERROR: ";
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
    log("Saving logs to '" + path + "'");
    std::ofstream file;
    file.open(path);
    file << logs;
    file.close();
}

void LogManager::save(const std::string &path)
{
    log("Saving logs to '" + path + "'");
    std::ofstream file;
    file.open(path);
    file << logs;
    file.close();
}

void LogManager::setFlags(bool print, bool save, bool enable)
{
    printLog = print;
    saveLog = save;
    isLogging = enable;
}

void Log::log(const std::string &message)
{
    logsQueue.push_back(message);
}

void Log::error(const std::string &message)
{
    logsQueue.push_back("ERROR: " + message);
}