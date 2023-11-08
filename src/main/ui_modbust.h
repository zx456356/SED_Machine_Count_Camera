/********************************************************************************
** Form generated from reading UI file 'modbust.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODBUST_H
#define UI_MODBUST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_modbust
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *port;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *serveID;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *lineEdit_4;

    void setupUi(QMainWindow *modbust)
    {
        if (modbust->objectName().isEmpty())
            modbust->setObjectName(QString::fromUtf8("modbust"));
        modbust->resize(342, 302);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        modbust->setFont(font);
        modbust->setStyleSheet(QString::fromUtf8("background-color: rgb(220, 220, 220);"));
        centralwidget = new QWidget(modbust);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(120, 23));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        label_3->setFont(font1);

        horizontalLayout_2->addWidget(label_3);

        port = new QLineEdit(centralwidget);
        port->setObjectName(QString::fromUtf8("port"));
        port->setFont(font1);
        port->setStyleSheet(QString::fromUtf8("border: 1px solid #1c7ed6;\n"
"border-radius: 4px;\n"
"background: white;"));
        port->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(port);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(120, 23));
        label_4->setFont(font1);

        horizontalLayout_3->addWidget(label_4);

        serveID = new QLineEdit(centralwidget);
        serveID->setObjectName(QString::fromUtf8("serveID"));
        serveID->setFont(font1);
        serveID->setStyleSheet(QString::fromUtf8("border: 1px solid #1c7ed6;\n"
"border-radius: 4px;\n"
"background: white;"));
        serveID->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(serveID);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        horizontalLayout_4->addWidget(label_2);

        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setFont(font1);
        lineEdit_4->setStyleSheet(QString::fromUtf8("border: 1px solid #1c7ed6;\n"
"border-radius: 4px;\n"
"background: white;"));
        lineEdit_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(lineEdit_4);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        modbust->setCentralWidget(centralwidget);

        retranslateUi(modbust);

        QMetaObject::connectSlotsByName(modbust);
    } // setupUi

    void retranslateUi(QMainWindow *modbust)
    {
        modbust->setWindowTitle(QCoreApplication::translate("modbust", "\351\200\232\350\256\257\347\256\241\347\220\206", nullptr));
        label_3->setText(QCoreApplication::translate("modbust", "\347\253\257\345\217\243\345\217\267:", nullptr));
        port->setText(QCoreApplication::translate("modbust", "502", nullptr));
        label_4->setText(QCoreApplication::translate("modbust", "\347\253\231\345\217\267:", nullptr));
        serveID->setText(QCoreApplication::translate("modbust", "1", nullptr));
        label_2->setText(QCoreApplication::translate("modbust", "\345\257\204\345\255\230\345\231\250\345\234\260\345\235\200\357\274\232", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("modbust", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class modbust: public Ui_modbust {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODBUST_H
