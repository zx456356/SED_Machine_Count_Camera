#ifndef XVLOGWIDGET_H
#define XVLOGWIDGET_H

#include "xvlog_global.h"
#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QList>
#include <QMenu>
#include <QAction>
#include <QEvent>
#include <QPaintEvent>
#include <QPainter>
#include "log.h"

/**
 * @brief       XVLogWidget
 * @note        基于tablewidget的日志控件
 * @author      chenshiyu
 * @date        create:2018-04-27
 */

struct MyLogData
{
    quint64 number;
    LogData logData;
};

typedef QList<MyLogData> LogDataList;

class XVLOGSHARED_EXPORT XVLogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit XVLogWidget(QString iconPath, QWidget *parent = 0);
    ~XVLogWidget();

    void setRowCount(int num);
    void initLogShow(bool num,bool type,bool time,bool msg,bool source);
    int getRowCount();
    void clearLogDataList();

    //"background-color:#3B3B3B;color:#FFFFFF;selection-background-color:#00A0E8;selection-color:#FFFFFF;"
    //"QHeaderView::section{background:#646464;color:#FFFFFF;}"
//    void setStyle(QString tableWidgetStyle,QString tableHeaderStyle);

protected slots:
    void slot_curLogData(const LogData &logData);
    void slot_copyData();

    void slot_actTrace_clicked();
    void slot_actInfo_clicked();
    void slot_actWarn_clicked();
    void slot_actError_clicked();
    void slot_actAll_clicked();

    void slot_actNum_clicked();
    void slot_actType_clicked();
    void slot_actTime_clicked();
    void slot_actMsg_clicked();
    void slot_actSource_clicked();

    void slot_actClear_clicked();

private:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void tableFlush();
    void tableScroll();
    void levelChanged(LogLevel level);
    MyLogData logDataToMyLogData(quint64 num, const LogData &logData);

private:
    QTableWidget *mTableWidget;
    QVBoxLayout *mainLayout;

    LogDataList mTraceLogList;
    LogDataList mInfoLogList;
    LogDataList mWarnLogList;
    LogDataList mErrorLogList;
    LogDataList mAllLogList;
    LogLevel mLogLevel;
    int mRowCount = 1000;//列表的长度
    quint64 mNumber = 0;

private:
    void paintEvent(QPaintEvent *event);
    void initMenu();
    QMenu *mMenu;
    QAction *actNum;
    QAction *actType;
    QAction *actTime;
    QAction *actMsg;
    QAction *actSource;

    QAction *actTrace;
    QAction *actInfo;
    QAction *actWarn;
    QAction *actError;
    QAction *actAll;

    QAction *actClear;

    QString mIconPath;

};
#endif // XVLOGWIDGET_H
