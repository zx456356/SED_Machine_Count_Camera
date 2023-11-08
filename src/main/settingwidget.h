/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       settingwidget.h
 * @brief      �������� Function
 *
 * @author     yyf
 * @date       2022/08/18
 * @history
 *****************************************************************************/

#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QSettings>
#include <QDir>
#include <QTreeWidgetItem>
#include <QThread>

#include "countprocess.h"
#include "ui_mainwindow.h"

extern CountProcess *cp;

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = nullptr);
    ~SettingWidget();

    Ui::SettingWidget *ui;
    QThread *countThread;
    QThread *saveImgThread;

    QString saveImgPath;
    int  saveImgDays;

    //MainWindow *mainwin;
    //Ui_MainWindow *mainwin;

    QString currentMode;
    bool isFirst;

signals :

    void Shaker1VBoxChanged();

    void Shaker2VBoxChanged();

    void Shaker3VBoxChanged();

    void tabWidgetEqul_2();

    void SingleNumBoxChanged_Sig();

    void exitSig();
    //static Widget *MainWin;

public:

    void configInit();

    void readConfig(QString filename);

    void writeConfig(QString filename);


public slots:

    void on_loadBtn_clicked();

    void on_newBtn_clicked();

    void on_delBtn_clicked();

    void on_saveBtn_clicked();


    void on_beltBtn_toggled(bool checked);

    void on_bufferBtn_toggled(bool checked);

    void on_shackerBtn_toggled(bool checked);

    void on_blockBtn_toggled(bool checked);

    void on_removeBtn_toggled(bool checked);

    void on_funnelBtn_toggled(bool checked);


    void on_bufferBtn_1_toggled(bool checked);
    void on_bufferBtn_2_toggled(bool checked);
    void on_bufferBtn_3_toggled(bool checked);
    void on_bufferBtn_4_toggled(bool checked);

    void on_bufferBtn_5_toggled(bool checked);
    void on_bufferBtn_6_toggled(bool checked);
    void on_bufferBtn_7_toggled(bool checked);
    void on_bufferBtn_8_toggled(bool checked);


    void cleanUpImage();

    void on_expousetime_editingFinished();

    void on_gainRaw_editingFinished();

    void on_lineRate_editingFinished();

    void on_ipAddress_editingFinished();

    void on_singleButtleQuantity_editingFinished();

    void on_minThreshold_editingFinished();

    void on_maxThreshold_editingFinished();

    void on_minArea_editingFinished();

    void on_maxArea_editingFinished();

    void on_minRadius_editingFinished();

    void on_maxRadius_editingFinished();

    void on_minFill_editingFinished();

    void on_maxFill_editingFinished();

    void on_currentNumAddr_editingFinished();

    ////////////ModbusͨѶ///////////////

    void on_cutTimeBox_editingFinished();

    void on_fallTimeBox_editingFinished();

    //void on_blockTimeBox_editingFinished();

    void on_bufferTimeBox_editingFinished();

    //void on_switchTimeBox_editingFinished();

    void on_removeOutBox_editingFinished();

    void on_removeBackBox_editingFinished();

    void on_shaker1VBox_editingFinished();

    void on_shaker2VBox_editingFinished();

    void on_shaker3VBox_editingFinished();

    void on_shaker1HzBox_editingFinished();

    void on_shaker2HzBox_editingFinished();

    void on_shaker3HzBox_editingFinished();


    void on_singleNumAddr_editingFinished();

    void on_insertCoordXAddr_editingFinished();

    void on_insertCoordYAddr_editingFinished();

    void on_fullSignalAddr_editingFinished();

    void on_flawSignalAddr_editingFinished();

    void on_setRuntime_editingFinished();

    //void on_saveImgPath_textChanged();

    void on_saveImgDays_editingFinished();

    //void on_saveImgPathBtn_clicked();

    void on_IsSaveImg_stateChanged(int arg1);

    void on_preProcessCombox_currentIndexChanged(int index);

    void on_operatorSize_editingFinished();

    void on_flawAreaMin_editingFinished();

    void on_flawAreaMax_editingFinished();

    void on_flawRadiusMin_editingFinished();

    void on_flawRadiusMax_editingFinished();

    void on_loadTimeBox_editingFinished();

    void on_stopRateBox_editingFinished();

    void on_shakeTimeBox_editingFinished();

    void on_blockTwoBox_editingFinished();

    void on_tabWidget_currentChanged(int);

    void on_MotorUpbtn_pressed();

    void on_MotorUpbtn_released();

    void on_MotorDownbtn_pressed();

    void on_MotorDownbtn_released();

    void on_sheddingBtn_toggled(bool cheked);

    void on_ExitBtn_clicked();

private slots:
    void on_restWarnBox_editingFinished();

private:


};

#endif // SETTINGWIDGET_H
