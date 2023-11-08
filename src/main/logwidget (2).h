/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       logwidget.h
 * @brief      日志显示、保存 Function
 *
 * @author     yyf
 * @date       2022/08/18
 * @history
 *****************************************************************************/

#ifndef LOGWIDGET_H
#define LOGWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QActionGroup>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QTextStream>
#include <QDir>

#pragma execution_character_set("utf-8")

namespace Ui {
class LogWidgetYYF;
}

class LogWidgetYYF : public QWidget
{
    Q_OBJECT

public:
    explicit LogWidgetYYF(QWidget *parent = nullptr);
    ~LogWidgetYYF();

    //延时函数(ms)
    void log_bar_init(); //日志栏初始化
    //定时清理日志文件
    void cleanUpLog();

public slots:
    //日志显示、保存
    void logDisplay(QString, QString, bool, bool);

private slots:
    //右键菜单弹出在鼠标点击位置
    void on_tableWidget_customContextMenuRequested(const QPoint &pos);
    //删除日志
    void deleteOperation();
    //对应类型日志是否显示
    void isDisplay();

private:

    Ui::LogWidgetYYF *ui;

    int Rowcount;
    QString res_msg;
    QString type;
    QString date;

    QMenu *tableMenu;
    QAction *deleteAction;
    QMenu *displayMenu;
    QAction *infoDisplay;
    QAction *warningDisplay;
    QAction *errorDisplay;
    QAction *allDisplay;
    QActionGroup *displayGroup;

    QFile *logFile;
    QTextStream * stream;
};



#endif // LOGWIDGET_H
