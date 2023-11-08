/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       login.h
 * @brief      登录界面 Function
 *
 * @author     yyf
 * @date       2022/08/18
 * @history
 *****************************************************************************/

#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QDebug>

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

    Ui::login *ui;

signals:

    void sendData();

    void sendLogin();

private slots:

    //登录界面关闭
    void closeEvent(QCloseEvent * event);
    //登录界面确认
    void on_code_lineEdit_returnPressed();

private:



};

#endif // LOGIN_H
