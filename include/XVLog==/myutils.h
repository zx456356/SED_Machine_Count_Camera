#ifndef MYUTILS_H
#define MYUTILS_H

#include "xvloglevel.h"
#include "xvlog_global.h"
#include <QFile>
#include <QTextStream>
//#include <QtGlobal>
#include <QSharedPointer>

/**
 * @brief       文件处理
 * @note        文件处理工具及文件保存策略
 * @author      chenshiyu
 * @date        create:2018-04-27
 */

namespace MyUtils
{
bool delDir(const QString &path);

bool keepDirNumber(const QString &path, const int saveNumber);

}//end namespace



namespace XVLogging
{
struct XVLOGSHARED_EXPORT MaxSizeBytes
{
    MaxSizeBytes() : size(0) {}
    explicit MaxSizeBytes(qint64 size_) : size(size_) {}
    qint64 size;
};

struct XVLOGSHARED_EXPORT MaxLogDays
{
    MaxLogDays() : days(0) {}
    explicit MaxLogDays(int days_) : days(days_) {}
    int days;
};

struct XVLOGSHARED_EXPORT MaxOneDayLogs
{
    MaxOneDayLogs() : num(0) {}
    explicit MaxOneDayLogs(int num_) : num(num_) {}
    int num;
};

enum FileStrategy
{
    SingleFileRotation = 0,
    MultiFileRotation,

    NoRotation
};

class RotationStrategy
{
public:
    virtual ~RotationStrategy();

    virtual void write(const QString &message, LogLevel level) = 0;
    virtual bool shouldRotate() = 0;
    virtual void rotate() = 0;
    virtual FileStrategy type() = 0;
};

// Never rotates file, overwrites existing file.
class NoRotationStrategy : public RotationStrategy
{
public:
    NoRotationStrategy(const QString &filePath);
    ~NoRotationStrategy();

    virtual void write(const QString &message, LogLevel level);
    virtual bool shouldRotate() { return false; }
    virtual void rotate() {}
    virtual FileStrategy type() {return NoRotation;}

private:
    QFile mFile;
    QTextStream mOutputStream;
private:
    QString mFileName;
    QString mBasePath;
};

class SingleFileRotationStrategy : public RotationStrategy
{
public:
    SingleFileRotationStrategy(const QString& filePath,
        const qint64 &sizeInBytesToRotateAfter,
        const int &logsCountForOneDay,
        const int &daysToKeepLog);
    virtual ~SingleFileRotationStrategy();

    virtual void write(const QString &message, LogLevel level);
    virtual bool shouldRotate();
    virtual void rotate();
    virtual FileStrategy type() {return SingleFileRotation;}


    void setMaximumSizeInBytes(qint64 size);
    void setMaxDayFilesNumber(int num);
    void setMaxSaveDays(int days);

private:
    void refreshFilesName();
    void checkFiles();
    void openFiles();
    void closeFiles();

private:
    QFile mFile;
    QTextStream mOutputStream;
private:
    QString mFileName;
    QString mBasePath;
    QString mCurrentDayBasePath;
    qint64 mCurrentSizeInBytes;
    qint64 mMaxSizeInBytes;
    int mDayFilesNumber;
    int mSaveDays;
};

class MultiFileRotationStrategy : public RotationStrategy
{
public:
    MultiFileRotationStrategy(const QString& filePath,
        const qint64 &sizeInBytesToRotateAfter,
        const int &logsCountForOneDay,
        const int &daysToKeepLog);
    virtual ~MultiFileRotationStrategy();

    virtual void write(const QString &message, LogLevel level);
    virtual bool shouldRotate();
    virtual void rotate();
    virtual FileStrategy type() {return MultiFileRotation;}

    void setMaximumSizeInBytes(qint64 size);
    void setMaxDayFilesNumber(int num);
    void setMaxSaveDays(int days);

private:
    void refreshFilesName();
    void checkFiles();
    void openFiles();
    void closeFiles();
private:
    QString mBasePath;
    QString mCurrentDayBasePath;
    qint64 mCurrentSizeInBytes;
    qint64 mMaxSizeInBytes;
    int mDayFilesNumber;
    int mSaveDays;

private:
    QString traceFileName;
//    QString debugFileName;
    QString infoFileName;
    QString warnFileName;
    QString errorFileName;
//    QString fatalFileName;
    QFile traceFile;
//    QFile debugFile;
    QFile infoFile;
    QFile warnFile;
    QFile errorFile;
//    QFile fatalFile;
    QTextStream traceStream;
//    QTextStream debugStream;
    QTextStream infoStream;
    QTextStream warnStream;
    QTextStream errorStream;
//    QTextStream fatalStream;
};

typedef QSharedPointer<RotationStrategy> RotationStrategyPtr;

}//end namespace

#endif // MYUTILS_H
