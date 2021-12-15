

#ifndef IP_LOG_H
#define IP_LOG_H

#include <string>
#include <iostream>

enum Level {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
};


void log(Level level, std::string &message);
void logInfo(std::string &message);
void logInfo(std::string &&message);
void logWarning(std::string &message);
void logWarning(std::string &&message);
void logError(std::string &message);
void logError(std::string &&message);
void logDebug(std::string &message);
void logDebug(std::string &&message);
void logFatal(std::string &message, int status);

#endif //IP_LOG_H
