#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

}

login::~login()
{
    delete ui;
}

void login::closeEvent(QCloseEvent * event)
{
    emit sendData();
}

void login::on_code_lineEdit_returnPressed()
{
    emit sendLogin();
}
