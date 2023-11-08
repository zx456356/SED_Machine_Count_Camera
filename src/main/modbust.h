/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       modbust.h
 * @brief      Modbus通讯 Function
 *
 * @author     yyf
 * @date       2022/08/18
 * @history
 *****************************************************************************/

#ifndef MODBUST_H
#define MODBUST_H

//#include <QChart>

#include <QLineSeries>
QT_CHARTS_USE_NAMESPACE

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QTimer>
#include "modbus.h"
#include "logwidget.h"
#include "ui_settingwidget.h"

#include "../include/xvlog.h"
#include "../include/xvlogwidget.h"
//#include "mainwindow.h"
#include "ui_mainwindow.h"


namespace Ui {
class modbust;
}

extern LogWidget *logBar;
extern XVLogWidget *Loge;
//extern QChart *chart;
extern QLineSeries *seriesBS;
extern QLineSeries *seriesCS;

class modbust : public QMainWindow
{
    Q_OBJECT

public:
    explicit modbust(Ui::SettingWidget *setWidget);
    ~modbust();
    Ui::modbust *ui;

    Ui_MainWindow *mainwin;
    modbus_t* modbus;
    bool modbus_state;
    QString ipAddress;
    bool isModbusMdu, isModbusCount, isModbusMain;
    int     bottleCount;


private slots:
    //通讯掉线重连
    void modbusTcpReconnect();

private:

};

#endif // MODBUST_H
