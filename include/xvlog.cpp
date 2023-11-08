#include "xvlog.h"
#include <QDateTime>
#include <QDebug>
#include <QScopedPointer>

namespace XVLogging
{
XVLog* XVLog::_instance = 0;

XVLog::XVLog()
{
    mLogLevel = InfoLevel;
    includeLogLevel = true;
    includeTimestamp = true;
    includeLogLine = true;
    setting.enableWriteToDebug = true;
    setting.enableWriteToFile = false;

    qRegisterMetaType<LogData>("LogData");
    qRegisterMetaType<LogData>("LogData&");
}

XVLog* XVLog::Instance()
{
    if (!_instance)
        _instance = new XVLog();

    return _instance;
}

void XVLog::destroyInstance()
{
    if (_instance)
    {
        delete _instance;
        _instance = 0;
    }
}

void XVLog::messageFromMacro(LogLevel level, QString msg, char *file, int line)
{
    LogData logData;
    logData.level = level;
    logData.info = msg;
    logData.timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    logData.atFile = file;
    logData.atLine = line;
    logData.location = true;

    enqueueLogData(logData);
}


int XVLog::addOutputDestination(LogDestination destination, FileStrategy strategy)
{
    switch (destination)
    {
        case OnlyDebug :
            setting.enableWriteToDebug = true; setting.enableWriteToFile = false; break;
        case OnlyFile :
            setting.enableWriteToDebug = false; setting.enableWriteToFile = true; break;
        case DebugAndFile :
            setting.enableWriteToDebug = true; setting.enableWriteToFile = true; break;
        default :
            setting.enableWriteToDebug = false; setting.enableWriteToFile = false; break;
    }
    setting.strategy = strategy;

    if (setting.enableWriteToFile && !mRotationStrategy)
    {
        setFileDestination(QCoreApplication::applicationDirPath(), setting.strategy);
    }
    return 0;
}

void XVLog::addCallBackFunction(LogFunction f)
{
    mLogFunction = f;
}

void XVLog::setLogLevel(LogLevel level)
{
    mLogLevel = level;
}

LogLevel XVLog::getLogLevel()
{
    return mLogLevel;
}

void XVLog::setIncludeTimestamp(bool value)
{
    includeTimestamp = value;
}

bool XVLog::isIncludeTimestamp()
{
    return includeTimestamp;
}

void XVLog::setIncludeLogLevel(bool value)
{
    includeLogLevel = value;
}

bool XVLog::isIncludeLogLevel()
{
    return includeLogLevel;
}

void XVLog::setIncludeLogLine(bool value)
{
    includeLogLine = value;
}

bool XVLog::isIncludeLogLine()
{
    return includeLogLine;
}

void XVLog::writeTrace(const QString &info, bool emitSingle)
{
    if (mLogLevel > TraceLevel)
        return;

    initLog(info,TraceLevel);
    if (emitSingle)
        emit signal_traceMessage(info);
}

//void XVLog::writeDebug(const QString &info)
//{
//    if (mLogLevel > DebugLevel)
//        return;

//    initLog(info,DebugLevel);
//}

void XVLog::writeInfo(const QString &info, bool emitSingle)
{
    if (mLogLevel > InfoLevel)
        return;

    initLog(info,InfoLevel);
    if (emitSingle)
        emit signal_InfoMessage(info);
}

void XVLog::writeWarn(const QString &info, bool emitSingle)
{
    if (mLogLevel > WarnLevel)
        return;

    initLog(info,WarnLevel);
    if (emitSingle)
        emit signal_warnMessage(info);
}

void XVLog::writeError(const QString &info, bool emitSingle)
{
    if (mLogLevel > ErrorLevel)
        return;

    initLog(info,ErrorLevel);
    if (emitSingle)
        emit signal_errorMessage(info);
}

//void XVLog::writeFatal(const QString &info)
//{
//    if (mLogLevel > FatalLevel)
//        return;

//    initLog(info,FatalLevel);
//}

void XVLog::initLog(const QString &info, LogLevel level)
{
    LogData logData;
    logData.level = level;
    logData.info = info;
    logData.timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");//"yyyy-MM-dd hh:mm:ss.zzz"
    logData.atFile = "";
    logData.atLine = 0;
    logData.location = false;
    enqueueLogData(logData);
}

void XVLog::enqueueLogData(const LogData &logData)
{
    QString message;
    if (includeLogLevel) {
        QString levelToString;
        switch (logData.level) {
            case TraceLevel : levelToString = "TRACE"; break;
//            case DebugLevel : levelToString = "DEBUG"; break;
            case InfoLevel : levelToString = "INFO"; break;
            case WarnLevel : levelToString = "WARN"; break;
            case ErrorLevel : levelToString = "ERROR"; break;
//            case FatalLevel : levelToString = "FATAL"; break;
            default : break;
        }
        message.append(levelToString).append(' ');
    }
    if (includeTimestamp) {
        message.append(logData.timestamp).append(' ');
    }
    message.append(logData.info);
    if (includeLogLine) {
        if (logData.location) {
            message.append(' ').append("FILE:").append(logData.atFile);
            message.append('@').append(QString::number(logData.atLine));
        }
    }

    outputToDestination(logData, message);
}

void XVLog::outputToDestination(const LogData &logData, const QString &message)
{
    mutex.lock();
    if (setting.enableWriteToDebug)
        qDebug() << message;
    if (setting.enableWriteToFile)
        writeToFile(message, logData.level);
    if (mLogFunction)
        mLogFunction(logData);

    emit signal_curLogData(logData);
    mutex.unlock();
}

void XVLog::writeToFile(const QString &message, LogLevel level)
{
    if (mRotationStrategy)
        mRotationStrategy->write(message, level);
}

bool XVLog::setFileDestination(
    const QString& filePath,
    const FileStrategy &rotation,
    const MaxSizeBytes &sizeInBytesToRotateAfter,
    const MaxOneDayLogs &logsCountForOneDay,
    const MaxLogDays &daysToKeepLog)
{
    if (!mRotationStrategy) {
        QString path = filePath + "/logfile";
        if (rotation == SingleFileRotation) {
            QScopedPointer<SingleFileRotationStrategy> logRotation(new SingleFileRotationStrategy(path
                                                                                                  , sizeInBytesToRotateAfter.size
                                                                                                  , logsCountForOneDay.num
                                                                                                  , daysToKeepLog.days));

            mRotationStrategy = RotationStrategyPtr(logRotation.take());
            return true;
        } else if (rotation == MultiFileRotation) {
            QScopedPointer<MultiFileRotationStrategy> logRotation(new MultiFileRotationStrategy(path
                                                                                                  , sizeInBytesToRotateAfter.size
                                                                                                  , logsCountForOneDay.num
                                                                                                  , daysToKeepLog.days));

            mRotationStrategy = RotationStrategyPtr(logRotation.take());
            return true;
        }
        return RotationStrategyPtr(new NoRotationStrategy(path));        
    }
    return false;
}

}//end namespace


