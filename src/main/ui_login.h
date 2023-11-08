/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *code_lineEdit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *loginBtn;
    QPushButton *loginCancelBtn;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QMainWindow *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QString::fromUtf8("login"));
        login->setWindowModality(Qt::WindowModal);
        login->resize(296, 221);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(login->sizePolicy().hasHeightForWidth());
        login->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        login->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ico/ivision.ico"), QSize(), QIcon::Normal, QIcon::Off);
        login->setWindowIcon(icon);
        login->setStyleSheet(QString::fromUtf8("background-color: rgb(220, 220, 220);"));
        centralwidget = new QWidget(login);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer_2 = new QSpacerItem(275, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        label->setFont(font1);

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setFont(font1);
        lineEdit->setStyleSheet(QString::fromUtf8("border: 1px solid black;\n"
"border-radius: 4px;\n"
"background: white;"));

        horizontalLayout_2->addWidget(lineEdit);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setFont(font1);

        horizontalLayout_3->addWidget(label_2);

        code_lineEdit = new QLineEdit(centralwidget);
        code_lineEdit->setObjectName(QString::fromUtf8("code_lineEdit"));
        code_lineEdit->setFont(font1);
        code_lineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	border: 1px solid #1c7ed6;\n"
"	border-radius: 4px;\n"
"	background: white;\n"
"}\n"
"\n"
"QLineEdit:hover{\n"
"	border-color: #74b816;\n"
"}"));
        code_lineEdit->setEchoMode(QLineEdit::Password);

        horizontalLayout_3->addWidget(code_lineEdit);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        loginBtn = new QPushButton(centralwidget);
        loginBtn->setObjectName(QString::fromUtf8("loginBtn"));
        loginBtn->setFont(font1);
        loginBtn->setStyleSheet(QString::fromUtf8("QPushButton#loginBtn{\n"
"	min-width: 80px;\n"
"	min-height: 30px;\n"
"	background: #adb5bd;\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton#loginBtn:hover{	\n"
"	background-color: gray;\n"
"}"));

        horizontalLayout->addWidget(loginBtn);

        loginCancelBtn = new QPushButton(centralwidget);
        loginCancelBtn->setObjectName(QString::fromUtf8("loginCancelBtn"));
        loginCancelBtn->setFont(font1);
        loginCancelBtn->setStyleSheet(QString::fromUtf8("QPushButton#loginCancelBtn{\n"
"	min-width: 80px;\n"
"	min-height: 30px;\n"
"	background: #adb5bd;\n"
"	border-radius: 4px;\n"
"}\n"
"\n"
"QPushButton#loginCancelBtn:hover{	\n"
"	background-color: gray;\n"
"}"));

        horizontalLayout->addWidget(loginCancelBtn);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(275, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 4, 0, 1, 1);

        login->setCentralWidget(centralwidget);

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QMainWindow *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "\347\263\273\347\273\237\347\231\273\345\275\225", nullptr));
        label->setText(QCoreApplication::translate("login", "\347\224\250\346\210\267\357\274\232", nullptr));
        lineEdit->setText(QCoreApplication::translate("login", "\347\256\241\347\220\206\345\221\230", nullptr));
        label_2->setText(QCoreApplication::translate("login", "\345\257\206\347\240\201\357\274\232", nullptr));
        code_lineEdit->setText(QString());
        loginBtn->setText(QCoreApplication::translate("login", "\347\241\256\345\256\232", nullptr));
        loginCancelBtn->setText(QCoreApplication::translate("login", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
