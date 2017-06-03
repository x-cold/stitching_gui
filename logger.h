#ifndef LOGGER_H
#define LOGGER_H

#include <string>
using namespace std;

class Logger
{
private:
    int level = 1;
public:
    Logger();
    void log(string msg);
    void info(string msg);
    void warn(string msg);
    void error(string msg);
    char* getNow();
};

#endif // LOGGER_H
