#ifndef XVLOG_H
#define XVLOG_H

#include "xvloglevel.h"
#include "xvlog_global.h"
#include <QObject>
#include <QMutex>
#include "myutils.h"
#include <QCoreApplication>
#include <QMetaType>

/**
 * @brief       XVLog类
 * @note        日志类，日志数据结构体，日志输出方向
 * @author      chenshiyu
 * @date        create:2018-04-27
 */

namespace XVLogging
{
struct LogData
{
    LogLevel level;
    QString info;
    QString timestamp;
    QString atFile;
    int atLine;
    bool location;//Log位置是否有效
};
Q_DECLARE_METATYPE(LogData)


enum LogDestination
{
    OnlyDebug = 0x0001,
    OnlyFile = 0x0002,
    DebugAndFile = 0x0004,

    NoDestination = 0x0000,
};

typedef void (*LogFunction)(const LogData &logData);

class XVLOGSHARED_EXPORT XVLog : public QObject
{
    Q_OBJECT
public:
    struct OutputSetting
    {
        bool enableWriteToDebug;
        bool enableWriteToFile;
        FileStrategy strategy;
    };

public:
    static XVLog* Instance();
    static void destroyInstance();
    void messageFromMacro(LogLevel level, QString msg, char *file, int line);

    //about loglevel
    void setLogLevel(LogLevel level);
    LogLevel getLogLevel();
    void setIncludeLogLevel(bool value);
    bool isIncludeLogLevel();
    //about timestamp
    void setIncludeTimestamp(bool value);
    bool isIncludeTimestamp();
    //about logline
    void setIncludeLogLine(bool value);
    bool isIncludeLogLine();

public:
    void writeTrace(const QString &info, bool emitSingle = false);
//    void writeDebug(const QString &info);
    void writeInfo(const QString &info, bool emitSingle = false);
    void writeWarn(const QString &info, bool emitSingle = false);
    void writeError(const QString &info, bool emitSingle = false);
//    void writeFatal(const QString &info);

public:
    //若改变默认设置，请再调用此函数前先调用setFileDestination
    int addOutputDestination(LogDestination destination = DebugAndFile, FileStrategy strategy = SingleFileRotation);
    void addCallBackFunction(LogFunction f);
    bool setFileDestination(const QString& filePath = QCoreApplication::applicationDirPath(),
        const FileStrategy &rotation = SingleFileRotation,
        const MaxSizeBytes &sizeInBytesToRotateAfter = MaxSizeBytes(1024*1024*100),
        const MaxOneDayLogs &logsCountForOneDay = MaxOneDayLogs(10),
        const MaxLogDays &daysToKeepLog = MaxLogDays(7));

signals:
    void signal_curLogData(const LogData &logData);
    void signal_traceMessage(const QString &msg);
    void signal_InfoMessage(const QString &msg);
    void signal_warnMessage(const QString &msg);
    void signal_errorMessage(const QString &msg);

private:
    XVLog();
    LogFunction mLogFunction = 0;

    void initLog(const QString &info, LogLevel level);
    void enqueueLogData(const LogData &logData);
    void outputToDestination(const LogData &logData, const QString &message);
    void writeToFile(const QString &message, LogLevel level);
    static XVLog *_instance;

private:
    RotationStrategyPtr mRotationStrategy = 0;
    QMutex mutex;
    LogLevel mLogLevel;
    OutputSetting setting;
    bool includeTimestamp;
    bool includeLogLevel;
    bool includeLogLine;
};

}//end namespace

#define xvTrace(msg) \
    if (XVLogging::XVLog::Instance()->getLogLevel() > XVLogging::TraceLevel) {} \
    else XVLogging::XVLog::Instance()->messageFromMacro(XVLogging::TraceLevel,msg,(char*)__FILE__,__LINE__)
//#define xvDebug(msg) \
//    if (XVLogging::XVLog::Instance()->getLogLevel() > XVLogging::DebugLevel) {} \
//    else XVLogging::XVLog::Instance()->messageFromMacro(XVLogging::DebugLevel,msg,__FILE__,__LINE__)
#define xvInfo(msg) \
    if (XVLogging::XVLog::Instance()->getLogLevel() > XVLogging::InfoLevel) {} \
    else XVLogging::XVLog::Instance()->messageFromMacro(XVLogging::InfoLevel,msg,(char*)__FILE__,__LINE__)
#define xvWarn(msg) \
    if (XVLogging::XVLog::Instance()->getLogLevel() > XVLogging::WarnLevel) {} \
    else XVLogging::XVLog::Instance()->messageFromMacro(XVLogging::WarnLevel,msg,(char*)__FILE__,__LINE__)
#define xvError(msg) \
    if (XVLogging::XVLog::Instance()->getLogLevel() > XVLogging::ErrorLevel) {} \
    else XVLogging::XVLog::Instance()->messageFromMacro(XVLogging::ErrorLevel,msg,(char*)__FILE__,__LINE__)
//#define xvFatal(msg) \
//    if (XVLogging::XVLog::Instance()->getLogLevel() > XVLogging::FatalLevel) {} \
//    else XVLogging::XVLog::Instance()->messageFromMacro(XVLogging::FatalLevel,msg,__FILE__,__LINE__)

#endif // XVLOG_H
