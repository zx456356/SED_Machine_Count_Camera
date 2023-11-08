#ifndef XVLOGLEVEL_H
#define XVLOGLEVEL_H


/**
 * @brief       LogLevel
 * @note        日志等级
 * @author      chenshiyu
 * @date        create:2018-04-27
 */

namespace XVLogging
{

enum LogLevel
{
    TraceLevel = 0,
//    DebugLevel,
    InfoLevel,
    WarnLevel,
    ErrorLevel,
//    FatalLevel,
    OffLevel
};


}
#endif // XVLOGLEVEL_H
