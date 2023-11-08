/********************************************************************************
** Form generated from reading UI file 'viewwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWWIDGET_H
#define UI_VIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewWidget
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *imgPathEdit;
    QPushButton *chooseButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *firstImgButton;
    QPushButton *preImgButton;
    QPushButton *nextImgButton;
    QPushButton *finalImgButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *ViewWidget)
    {
        if (ViewWidget->objectName().isEmpty())
            ViewWidget->setObjectName(QString::fromUtf8("ViewWidget"));
        ViewWidget->resize(756, 534);
        gridLayout_2 = new QGridLayout(ViewWidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        imgPathEdit = new QLineEdit(ViewWidget);
        imgPathEdit->setObjectName(QString::fromUtf8("imgPathEdit"));
        QFont font;
        font.setPointSize(14);
        imgPathEdit->setFont(font);

        horizontalLayout->addWidget(imgPathEdit);

        chooseButton = new QPushButton(ViewWidget);
        chooseButton->setObjectName(QString::fromUtf8("chooseButton"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(14);
        chooseButton->setFont(font1);

        horizontalLayout->addWidget(chooseButton);

        horizontalSpacer = new QSpacerItem(255, 22, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        firstImgButton = new QPushButton(ViewWidget);
        firstImgButton->setObjectName(QString::fromUtf8("firstImgButton"));
        firstImgButton->setFont(font1);

        horizontalLayout->addWidget(firstImgButton);

        preImgButton = new QPushButton(ViewWidget);
        preImgButton->setObjectName(QString::fromUtf8("preImgButton"));
        preImgButton->setFont(font1);

        horizontalLayout->addWidget(preImgButton);

        nextImgButton = new QPushButton(ViewWidget);
        nextImgButton->setObjectName(QString::fromUtf8("nextImgButton"));
        nextImgButton->setFont(font1);

        horizontalLayout->addWidget(nextImgButton);

        finalImgButton = new QPushButton(ViewWidget);
        finalImgButton->setObjectName(QString::fromUtf8("finalImgButton"));
        finalImgButton->setFont(font1);

        horizontalLayout->addWidget(finalImgButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 4);
        gridLayout_2->setRowStretch(1, 1);

        retranslateUi(ViewWidget);

        QMetaObject::connectSlotsByName(ViewWidget);
    } // setupUi

    void retranslateUi(QWidget *ViewWidget)
    {
        ViewWidget->setWindowTitle(QCoreApplication::translate("ViewWidget", "Form", nullptr));
        chooseButton->setText(QCoreApplication::translate("ViewWidget", "\351\200\211\346\213\251", nullptr));
        firstImgButton->setText(QCoreApplication::translate("ViewWidget", "\347\254\254\344\270\200\345\274\240", nullptr));
        preImgButton->setText(QCoreApplication::translate("ViewWidget", "\344\270\212\344\270\200\345\274\240", nullptr));
        nextImgButton->setText(QCoreApplication::translate("ViewWidget", "\344\270\213\344\270\200\345\274\240", nullptr));
        finalImgButton->setText(QCoreApplication::translate("ViewWidget", "\346\234\200\345\220\216\344\270\200\345\274\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ViewWidget: public Ui_ViewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWWIDGET_H
