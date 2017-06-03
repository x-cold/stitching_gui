#include "logger.h"
#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

Logger::Logger()
{
}

char* Logger::getNow()
{
    // 获取时间戳
    time_t tt = time(NULL);
    // 转换为本地时间
    tm* t= localtime(&tt);
    char* formatTime;
    sprintf(formatTime,"%d-%02d-%02d %02d:%02d:%02d",
            t->tm_year + 1900,
            t->tm_mon + 1,
            t->tm_mday,
            t->tm_hour,
            t->tm_min,
            t->tm_sec);
    return formatTime;
}

void Logger::log(string msg)
{
    char* now = this->getNow();
    cout << "[LOG]" << now << "::" << msg << endl;
}

void Logger::info(string msg)
{
    char* now = this->getNow();
    cout << "[INFO]" << now << "::" << msg << endl;
}

void Logger::warn(string msg)
{
    char* now = this->getNow();
    cout << "[WARN]" << now << "::" << msg << endl;
}

void Logger::error(string msg)
{
    char* now = this->getNow();
    cout << "[ERROR]" << now << "::" << msg << endl;
}
