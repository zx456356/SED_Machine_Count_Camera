#include "myutils.h"
#include <QTextCodec>
#include <QDateTime>
#include <QtGlobal>
#include <iostream>
#include <QDir>

//delete the dir and files in it
bool MyUtils::delDir(const QString &path)
{
    if (path.isEmpty()){
        return false;
    }
    QDir dir(path);
    if (!dir.exists()) {
        return true;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    foreach (QFileInfo file, fileList){
        if (file.isFile()){
            file.dir().remove(file.fileName());
        }else{
            delDir(file.absoluteFilePath());
        }
    }
    return dir.rmpath(dir.absolutePath());
}

//save saveNumber files in this path
bool MyUtils::keepDirNumber(const QString &path, const int saveNumber)
{
    if (path.isEmpty()) {
        return false;
    }
    if (saveNumber < 0) {
        return false;
    }
    QDir dir(path);
    if (!dir.exists()) {
        return true;
    }
    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList( dir.filter(),QDir::Time);
    while(fileList.size()>saveNumber)
    {
        QFileInfo file = fileList.back();
//        fileList.
        if (file.isFile()){
            file.dir().remove(file.fileName());
        }else{
            delDir(file.absoluteFilePath());
        }
        fileList.pop_back();
    }

    return true;
}

XVLogging::RotationStrategy::~RotationStrategy()
{
}

XVLogging::NoRotationStrategy::NoRotationStrategy(const QString &filePath)
{
    QDir dir;
    dir.mkpath(filePath);
    mBasePath = filePath;
    mFileName = filePath + "/log.txt";
    mFile.setFileName(mFileName);

    if (!mFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))
     std::cerr << "QsLog: could not open log file " << qPrintable(mFileName);
    mOutputStream.setDevice(&mFile);
    mOutputStream.setCodec(QTextCodec::codecForName("UTF-8"));
}

XVLogging::NoRotationStrategy::~NoRotationStrategy()
{
    if (mFile.isOpen())
    {
        mOutputStream.setDevice(NULL);
        mFile.close();
    }
}

void XVLogging::NoRotationStrategy::write(const QString &message, LogLevel)
{
    mOutputStream << message << endl;
    mOutputStream.flush();
}

XVLogging::SingleFileRotationStrategy::SingleFileRotationStrategy(const QString& filePath,
    const qint64 &sizeInBytesToRotateAfter,
    const int &logsCountForOneDay,
    const int &daysToKeepLog)
{
    mBasePath = filePath;
    mCurrentSizeInBytes = 0;
    mMaxSizeInBytes = sizeInBytesToRotateAfter;
    mDayFilesNumber = logsCountForOneDay;
    mSaveDays = daysToKeepLog;

    refreshFilesName();
    checkFiles();
    openFiles();
}

XVLogging::SingleFileRotationStrategy::~SingleFileRotationStrategy()
{
    closeFiles();
}

void XVLogging::SingleFileRotationStrategy::write(const QString &message, LogLevel)
{
    mCurrentSizeInBytes += message.toUtf8().size();

    if (shouldRotate()) {
        rotate();
    }

    mOutputStream << message << endl;
    mOutputStream.flush();
}

bool XVLogging::SingleFileRotationStrategy::shouldRotate()
{
    return mCurrentSizeInBytes > mMaxSizeInBytes;
}

// Algorithm assumes backups will be named filename.X, where 1 <= X <= mBackupsCount.
// All X's will be shifted up.
void XVLogging::SingleFileRotationStrategy::rotate()
{
    closeFiles();
    checkFiles();

    refreshFilesName();
    openFiles();
}

void XVLogging::SingleFileRotationStrategy::setMaximumSizeInBytes(qint64 size)
{
    Q_ASSERT(size >= 0);
    mMaxSizeInBytes = size;
}

void XVLogging::SingleFileRotationStrategy::setMaxDayFilesNumber(int num)
{
    Q_ASSERT(num >= 0);
    mDayFilesNumber = num;
}

void XVLogging::SingleFileRotationStrategy::setMaxSaveDays(int days)
{
    Q_ASSERT(days >= 0);
    mSaveDays = days;
}

void XVLogging::SingleFileRotationStrategy::refreshFilesName()
{
    QDir dir;
    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    QString time = QTime::currentTime().toString("hh-mm-ss");
    mCurrentDayBasePath = mBasePath + "/" +date;
    dir.mkpath(mCurrentDayBasePath);

    mFileName = mCurrentDayBasePath + "/log_" + time + ".txt";
}

void XVLogging::SingleFileRotationStrategy::checkFiles()
{
    MyUtils::keepDirNumber(mBasePath,mSaveDays - 1);
    MyUtils::keepDirNumber(mCurrentDayBasePath,mDayFilesNumber - 1);
}

void XVLogging::SingleFileRotationStrategy::openFiles()
{
    mFile.setFileName(mFileName);
    if (!mFile.open(QFile::WriteOnly | QFile::Text | QFile::Append))
        std::cerr << "QsLog: could not open log file " << qPrintable(mFileName);
    mOutputStream.setDevice(&mFile);
    mOutputStream.setCodec(QTextCodec::codecForName("UTF-8"));
    mCurrentSizeInBytes = 0;
}

void XVLogging::SingleFileRotationStrategy::closeFiles()
{
    mOutputStream.setDevice(NULL);
    mFile.close();
}

XVLogging::MultiFileRotationStrategy::MultiFileRotationStrategy(const QString& filePath,
    const qint64 &sizeInBytesToRotateAfter,
    const int &logsCountForOneDay,
    const int &daysToKeepLog)
{
    mBasePath = filePath;
    mCurrentSizeInBytes = 0;
    mMaxSizeInBytes = sizeInBytesToRotateAfter;
    mDayFilesNumber = logsCountForOneDay;
    mSaveDays = daysToKeepLog;

    refreshFilesName();
    checkFiles();
    openFiles();
}

XVLogging::MultiFileRotationStrategy::~MultiFileRotationStrategy()
{
    closeFiles();
}

void XVLogging::MultiFileRotationStrategy::write(const QString &message, LogLevel level)
{
    mCurrentSizeInBytes += message.toUtf8().size();

    if (shouldRotate()) {
        rotate();
    }

    switch (level) {
        case TraceLevel : {
            traceStream << message << endl;
            traceStream.flush();
        } break;
//        case DebugLevel : {
//            debugStream << message << endl;
//            debugStream.flush();
//        } break;
        case InfoLevel : {
            infoStream << message << endl;
            infoStream.flush();
        } break;
        case WarnLevel : {
            warnStream << message << endl;
            warnStream.flush();
        } break;
        case ErrorLevel : {
            errorStream << message << endl;
            errorStream.flush();
        } break;
//        case FatalLevel : {
//            fatalStream << message << endl;
//            fatalStream.flush();
//        } break;
        default : break;
    }
}

bool XVLogging::MultiFileRotationStrategy::shouldRotate()
{
    return mCurrentSizeInBytes > mMaxSizeInBytes;
}

void XVLogging::MultiFileRotationStrategy::rotate()
{
    closeFiles();
    checkFiles();

    refreshFilesName();
    openFiles();
}

void XVLogging::MultiFileRotationStrategy::setMaximumSizeInBytes(qint64 size)
{
    Q_ASSERT(size >= 0);
    mMaxSizeInBytes = size;
}

void XVLogging::MultiFileRotationStrategy::setMaxDayFilesNumber(int num)
{
    Q_ASSERT(num >= 0);
    mDayFilesNumber = num;
}

void XVLogging::MultiFileRotationStrategy::setMaxSaveDays(int days)
{
    Q_ASSERT(days >= 0);
    mSaveDays = days;
}

void XVLogging::MultiFileRotationStrategy::refreshFilesName()
{
    QDir dir;
    QString date = QDate::currentDate().toString("yyyy-MM-dd");
    QString time = QTime::currentTime().toString("hh-mm-ss");
    QString path = mBasePath +  "/" + date + "/" + time;
    mCurrentDayBasePath = mBasePath + "/" +date;
    dir.mkpath(path);

    traceFileName = path + "/trace.txt";
//    debugFileName = path + "/debug.txt";
    infoFileName = path + "/info.txt";
    warnFileName = path + "/warning.txt";
    errorFileName = path + "/error.txt";
//    fatalFileName = path + "/fatal.txt";
}

void XVLogging::MultiFileRotationStrategy::checkFiles()
{
    MyUtils::keepDirNumber(mBasePath,mSaveDays - 1);
    MyUtils::keepDirNumber(mCurrentDayBasePath,mDayFilesNumber - 1);
}

void XVLogging::MultiFileRotationStrategy::openFiles()
{
    mCurrentSizeInBytes = 0;
    //trace file
    traceFile.setFileName(traceFileName);
    if (!traceFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))
        std::cerr << "QsLog: could not open log file " << qPrintable(traceFileName);
    traceStream.setDevice(&traceFile);
    traceStream.setCodec(QTextCodec::codecForName("UTF-8"));

    //debug file
//    debugFile.setFileName(debugFileName);
//    if (!debugFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))
//        std::cerr << "QsLog: could not open log file " << qPrintable(debugFileName);
//    debugStream.setDevice(&debugFile);
//    debugStream.setCodec(QTextCodec::codecForName("UTF-8"));

    //info file
    infoFile.setFileName(infoFileName);
    if (!infoFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))
        std::cerr << "QsLog: could not open log file " << qPrintable(infoFileName);
    infoStream.setDevice(&infoFile);
    infoStream.setCodec(QTextCodec::codecForName("UTF-8"));

    //warning file
    warnFile.setFileName(warnFileName);
    if (!warnFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))
        std::cerr << "QsLog: could not open log file " << qPrintable(warnFileName);
    warnStream.setDevice(&warnFile);
    warnStream.setCodec(QTextCodec::codecForName("UTF-8"));

    //error file
    errorFile.setFileName(errorFileName);
    if (!errorFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))
        std::cerr << "QsLog: could not open log file " << qPrintable(errorFileName);
    errorStream.setDevice(&errorFile);
    errorStream.setCodec(QTextCodec::codecForName("UTF-8"));

    //fatal file
//    fatalFile.setFileName(fatalFileName);
//    if (!fatalFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))
//        std::cerr << "QsLog: could not open log file " << qPrintable(fatalFileName);
//    fatalStream.setDevice(&fatalFile);
//    fatalStream.setCodec(QTextCodec::codecForName("UTF-8"));
}

void XVLogging::MultiFileRotationStrategy::closeFiles()
{
    traceStream.setDevice(NULL);
    traceFile.close();
//    debugStream.setDevice(NULL);
//    debugFile.close();
    infoStream.setDevice(NULL);
    infoFile.close();
    warnStream.setDevice(NULL);
    warnFile.close();
    errorStream.setDevice(NULL);
    errorFile.close();
//    fatalStream.setDevice(NULL);
//    fatalFile.close();
}
