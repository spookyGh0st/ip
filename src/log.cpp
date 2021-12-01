#include "ip/log.h"

void logInfo(std::string &message) {
    log(INFO, message);
}

void logInfo(std::string &&message) {
    log(INFO, message);
}

void logWarning(std::string &message) {
    log(WARNING, message);
}

void logError(std::string &message) {
    log(ERROR, message);
}

void logError(std::string &&message) {
    log(ERROR, message);
}

void logDebug(std::string &message) {
    log(DEBUG, message);
}

void logDebug(std::string &&message) {
    log(DEBUG, message);
}

void logFatal(std::string &message, int status) {
    log(DEBUG, message);
    exit(status);
}


void log(Level level, std::string &message) {
    std::string prefix;
    switch (level) {
        case DEBUG:
            prefix = "DEBUG: ";
            break;
        case INFO:
            prefix = "INFO: ";
            break;
        case WARNING:
            prefix = "WARNING: ";
            break;
        case ERROR:
            prefix = "ERROR: ";
            break;
    }

    std::cout << prefix << message << std::endl;
}

