#include "log.h"

void Logger::init(const std::string &directory, bool withTime, const std::string &extension, bool print, bool save, bool enable)
{
    path = directory + "/log_" + (withTime ? std::to_string(std::time(0)) : "/log_" + std::to_string(Utils::genID())) + "." + extension;
    logs = "";
    frame = 0;
    printLog = print;
    saveLog = save;
    isLogging = enable;
    log("Logger initialized");
}

void Logger::quit()
{
    if (!checkInit())
        return;
    log("Logger quitting");
    if (saveLog && logs != "")
        save();
    print();
}

void Logger::update(int frame)
{
    if (!checkInit())
        return;
    Logger::frame = frame;
    if (logs.size() > 1000000)
    {
        log("Saving logs to '" + path + "'");
        save();
        print();
        logs = "";
    }
}

bool Logger::checkInit()
{
    if (path == "")
    {
        std::cerr << "Logger not initialized\n";
        return false;
    }
    return true;
}

void Logger::print()
{
    if (!checkInit())
        return;
    if (printLog)
        std::cout << logs << "\n";
}

void Logger::log(const std::string &message)
{
    if (!checkInit())
        return;
    // ["time"]["frame"] : "message"
    if (isLogging)
    {
        std::string log = "[" + std::to_string(glfwGetTime()) + "]";
        log += "[" + std::to_string(frame) + "]";
        log += " : ";
        log += message;
        log += "\n";
        logs += log;
        print();
    }
}

void Logger::error(const std::string &message)
{
    if (!checkInit())
        return;
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
        print();
    }
}

void Logger::save()
{
    if (!checkInit())
        return;
    log("Saving logs to '" + path + "'");
    std::ofstream file;
    file.open(path);
    file << logs;
    file.close();
}

void Logger::save(const std::string &path)
{
    if (!checkInit())
        return;
    log("Saving logs to '" + path + "'");
    std::ofstream file;
    file.open(path);
    file << logs;
    file.close();
}

void Logger::setFlags(bool print, bool save, bool enable)
{
    if (!checkInit())
        return;
    printLog = print;
    saveLog = save;
    isLogging = enable;
}