/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <unitspainbox.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *login;
    QAction *mainInterfaceAction;
    QAction *setInterfaceAction;
    QAction *start;
    QAction *imageInterfaceAction;
    QAction *FullScreen;
    QAction *Exit;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *mainInterface;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *curRecipe;
    QFrame *frame;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    UnitSpainBox *currentNumBox;
    UnitSpainBox *singleNumBox;
    UnitSpainBox *countSpeedBox;
    QLabel *label_8;
    UnitSpainBox *bottleSpeedBox;
    QLabel *label_7;
    QPushButton *clearBottleBtn;
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_12;
    QGridLayout *gridLayout_8;
    QLabel *M354Sig;
    QLabel *label_13;
    QLabel *label_15;
    QFrame *verticalFrame1;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_9;
    QGridLayout *gridLayout_7;
    QLabel *label_10;
    QLabel *X1Sig;
    QLabel *label_11;
    QPushButton *clearBtn;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_6;
    UnitSpainBox *BottleCountBox;
    QProgressBar *progressBar;
    QGridLayout *gridLayout_6;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer_12;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *shaker3Dec;
    QSpacerItem *verticalSpacer_13;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_14;
    QSpacerItem *verticalSpacer_3;
    QPushButton *studyBtn;
    QSpacerItem *horizontalSpacer_3;
    UnitSpainBox *Shaker2VBox;
    QPushButton *startBtn;
    QSpacerItem *verticalSpacer_2;
    QPushButton *shaker1Add;
    QPushButton *shaker2Dec;
    QPushButton *stopBtn;
    QPushButton *saveImgBtn;
    QVBoxLayout *verticalLayout_2;
    QPushButton *beltPowerBtn;
    UnitSpainBox *Shaker1VBox;
    QPushButton *shaker1Dec;
    QSpacerItem *horizontalSpacer_6;
    UnitSpainBox *Shaker3VBox;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *shaker3Add;
    QPushButton *shaker2Add;
    QPushButton *clearBufferBtn;
    QVBoxLayout *verticalLayout;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *DisplayLayout;
    QVBoxLayout *chartLayout;
    QVBoxLayout *LogLayout;
    QSpacerItem *verticalSpacer_4;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1366, 789);
        QPalette palette;
        MainWindow->setPalette(palette);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ico/ivision3.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setLayoutDirection(Qt::LeftToRight);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow#MainWindow{\n"
"border-image:url(./backgrandpic.png);\n"
"}"));
        login = new QAction(MainWindow);
        login->setObjectName(QString::fromUtf8("login"));
        login->setCheckable(true);
        login->setChecked(false);
        QIcon icon1;
        QString iconThemeName = QString::fromUtf8("dengru");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(":/ico/project/login.png"), QSize(), QIcon::Normal, QIcon::Off);
            icon1.addFile(QString::fromUtf8(":/ico/project/logout.png"), QSize(), QIcon::Normal, QIcon::On);
        }
        login->setIcon(icon1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        login->setFont(font1);
        mainInterfaceAction = new QAction(MainWindow);
        mainInterfaceAction->setObjectName(QString::fromUtf8("mainInterfaceAction"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ico/project/camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        mainInterfaceAction->setIcon(icon2);
        mainInterfaceAction->setFont(font1);
        setInterfaceAction = new QAction(MainWindow);
        setInterfaceAction->setObjectName(QString::fromUtf8("setInterfaceAction"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ico/project/set.png"), QSize(), QIcon::Normal, QIcon::Off);
        setInterfaceAction->setIcon(icon3);
        setInterfaceAction->setFont(font1);
        start = new QAction(MainWindow);
        start->setObjectName(QString::fromUtf8("start"));
        start->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ico/project/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QString::fromUtf8(":/ico/project/stop.png"), QSize(), QIcon::Normal, QIcon::On);
        start->setIcon(icon4);
        start->setFont(font1);
        imageInterfaceAction = new QAction(MainWindow);
        imageInterfaceAction->setObjectName(QString::fromUtf8("imageInterfaceAction"));
        imageInterfaceAction->setCheckable(false);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ico/learn1.png"), QSize(), QIcon::Normal, QIcon::Off);
        imageInterfaceAction->setIcon(icon5);
        imageInterfaceAction->setFont(font1);
        FullScreen = new QAction(MainWindow);
        FullScreen->setObjectName(QString::fromUtf8("FullScreen"));
        FullScreen->setCheckable(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/ico/windows/max_press.png"), QSize(), QIcon::Normal, QIcon::Off);
        FullScreen->setIcon(icon6);
        FullScreen->setFont(font1);
        FullScreen->setShortcutContext(Qt::WindowShortcut);
        FullScreen->setMenuRole(QAction::TextHeuristicRole);
        FullScreen->setPriority(QAction::NormalPriority);
        Exit = new QAction(MainWindow);
        Exit->setObjectName(QString::fromUtf8("Exit"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/ico/windows/close_press.png"), QSize(), QIcon::Normal, QIcon::Off);
        Exit->setIcon(icon7);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setFont(font1);
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(105, 105, 105);"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setFocusPolicy(Qt::WheelFocus);
        stackedWidget->setStyleSheet(QString::fromUtf8("color: rgb(30, 30, 30)"));
        stackedWidget->setFrameShape(QFrame::NoFrame);
        mainInterface = new QWidget();
        mainInterface->setObjectName(QString::fromUtf8("mainInterface"));
        gridLayout = new QGridLayout(mainInterface);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        curRecipe = new QLabel(mainInterface);
        curRecipe->setObjectName(QString::fromUtf8("curRecipe"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(16);
        curRecipe->setFont(font2);
        curRecipe->setStyleSheet(QString::fromUtf8("color: rgb(50,50,50)"));

        horizontalLayout_3->addWidget(curRecipe);


        verticalLayout_4->addLayout(horizontalLayout_3);

        frame = new QFrame(mainInterface);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_3->setHorizontalSpacing(10);
        gridLayout_3->setVerticalSpacing(5);
        gridLayout_3->setContentsMargins(10, 10, 10, 10);
        currentNumBox = new UnitSpainBox(frame);
        currentNumBox->setObjectName(QString::fromUtf8("currentNumBox"));
        currentNumBox->setStyleSheet(QString::fromUtf8("QSpinBox{	\n"
"		border: 1px solid rgb(0,0,0);\n"
"		rgb:(50,50,50);\n"
"		background-color:transparent;\n"
"		font: 30pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
"\n"
"QSpinBox::up-button{\n"
"	subcontrol-origin: border;\n"
"	subcontrol-position: right;\n"
"	width: 0px;\n"
"	height: 20px;\n"
"	\n"
"	background-image: url(:/ico/hmi/add_right.png);\n"
"}\n"
"\n"
"QSpinBox::up-button:hover{\n"
"	\n"
"	background-image: url(:/ico/hmi/add_right(1).png);\n"
"}\n"
"\n"
"QSpinBox::down-button{\n"
"	subcontrol-origin: border;\n"
"	subcontrol-position: left;\n"
"	width: 0px;\n"
"	height: 20px;\n"
"\n"
"	background-image: url(:/ico/hmi/add_left.png);\n"
"}\n"
"\n"
"QSpinBox::down-button:hover{\n"
"	\n"
"	background-image: url(:/ico/hmi/add_left(1).png);\n"
"}"));
        currentNumBox->setAlignment(Qt::AlignCenter);
        currentNumBox->setMaximum(999999999);

        gridLayout_3->addWidget(currentNumBox, 0, 1, 1, 2);

        singleNumBox = new UnitSpainBox(frame);
        singleNumBox->setObjectName(QString::fromUtf8("singleNumBox"));
        singleNumBox->setStyleSheet(QString::fromUtf8("QSpinBox{	\n"
"		border: 1px solid rgb(0,0,0);\n"
"		rgb:(50,50,50);\n"
"		background-color:transparent;\n"
"		font: 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
"\n"
"QSpinBox::up-button{\n"
"	subcontrol-origin: border;\n"
"	subcontrol-position: right;\n"
"	width: 0px;\n"
"	height: 20px;\n"
"	\n"
"	background-image: url(:/ico/hmi/add_right.png);\n"
"}\n"
"\n"
"QSpinBox::up-button:hover{\n"
"	\n"
"	background-image: url(:/ico/hmi/add_right(1).png);\n"
"}\n"
"\n"
"QSpinBox::down-button{\n"
"	subcontrol-origin: border;\n"
"	subcontrol-position: left;\n"
"	width: 0px;\n"
"	height: 20px;\n"
"\n"
"	background-image: url(:/ico/hmi/add_left.png);\n"
"}\n"
"\n"
"QSpinBox::down-button:hover{\n"
"	\n"
"	background-image: url(:/ico/hmi/add_left(1).png);\n"
"}"));
        singleNumBox->setAlignment(Qt::AlignCenter);
        singleNumBox->setMaximum(99999999);

        gridLayout_3->addWidget(singleNumBox, 4, 1, 1, 2);

        countSpeedBox = new UnitSpainBox(frame);
        countSpeedBox->setObjectName(QString::fromUtf8("countSpeedBox"));
        countSpeedBox->setStyleSheet(QString::fromUtf8("QSpinBox{	\n"
"		border: 1px solid rgb(0,0,0);\n"
"		rgb:(50,50,50);\n"
"		background-color:transparent;\n"
"		font: 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
"\n"
"QSpinBox::up-button{\n"
"	subcontrol-origin: border;\n"
"	subcontrol-position: right;\n"
"	width: 0px;\n"
"	height: 20px;\n"
"	\n"
"	background-image: url(:/ico/hmi/add_right.png);\n"
"}\n"
"\n"
"QSpinBox::up-button:hover{\n"
"	\n"
"	background-image: url(:/ico/hmi/add_right(1).png);\n"
"}\n"
"\n"
"QSpinBox::down-button{\n"
"	subcontrol-origin: border;\n"
"	subcontrol-position: left;\n"
"	width: 0px;\n"
"	height: 20px;\n"
"\n"
"	background-image: url(:/ico/hmi/add_left.png);\n"
"}\n"
"\n"
"QSpinBox::down-button:hover{\n"
"	\n"
"	background-image: url(:/ico/hmi/add_left(1).png);\n"
"}"));
        countSpeedBox->setAlignment(Qt::AlignCenter);
        countSpeedBox->setMaximum(999999);

        gridLayout_3->addWidget(countSpeedBox, 8, 1, 1, 2);

        label_8 = new QLabel(frame);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(0, 0));
        label_8->setMaximumSize(QSize(16777215, 40));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(14);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        label_8->setFont(font3);
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(50,50,50);\n"
"\n"
"font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_3->addWidget(label_8, 10, 0, 1, 1);

        bottleSpeedBox = new UnitSpainBox(frame);
        bottleSpeedBox->setObjectName(QString::fromUtf8("bottleSpeedBox"));
        bottleSpeedBox->setStyleSheet(QString::fromUtf8("QSpinBox{	\n"
"		border: 1px solid rgb(0,0,0);\n"
"		rgb:(50,50,50);\n"
"		background-color:transparent;\n"
"		font: 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
"\n"
"QSpinBox::up-button{\n"
"	subcontrol-origin: border;\n"
"	subcontrol-position: right;\n"
"	width: 0px;\n"
"	height: 20px;\n"
"	\n"
"	background-image: url(:/ico/hmi/add_right.png);\n"
"}\n"
"\n"
"QSpinBox::up-button:hover{\n"
"	\n"
"	background-image: url(:/ico/hmi/add_right(1).png);\n"
"}\n"
"\n"
"QSpinBox::down-button{\n"
"	subcontrol-origin: border;\n"
"	subcontrol-position: left;\n"
"	width: 0px;\n"
"	height: 20px;\n"
"\n"
"	background-image: url(:/ico/hmi/add_left.png);\n"
"}\n"
"\n"
"QSpinBox::down-button:hover{\n"
"	\n"
"	background-image: url(:/ico/hmi/add_left(1).png);\n"
"}"));
        bottleSpeedBox->setAlignment(Qt::AlignCenter);
        bottleSpeedBox->setMaximum(9999999);

        gridLayout_3->addWidget(bottleSpeedBox, 10, 1, 1, 2);

        label_7 = new QLabel(frame);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMaximumSize(QSize(16777215, 40));
        QPalette palette1;
        QBrush brush(QColor(50, 50, 50, 255));
        brush.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(105, 105, 105, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush2(QColor(50, 50, 50, 128));
        brush2.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush3(QColor(50, 50, 50, 128));
        brush3.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush3);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QBrush brush4(QColor(50, 50, 50, 128));
        brush4.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush4);
#endif
        label_7->setPalette(palette1);
        label_7->setFont(font3);
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(50,50,50)"));

        gridLayout_3->addWidget(label_7, 12, 0, 2, 1);

        clearBottleBtn = new QPushButton(frame);
        clearBottleBtn->setObjectName(QString::fromUtf8("clearBottleBtn"));
        clearBottleBtn->setFont(font3);
        clearBottleBtn->setStyleSheet(QString::fromUtf8("QPushButton#clearBottleBtn{\n"
"	min-width: 100px;\n"
"	min-height: 50px;\n"
"	background: rgb(85, 0, 255);\n"
"	border-radius: 4px;\n"
"	font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color:rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton#clearBottleBtn:hover{	\n"
"	background-color: rgb(85, 85, 255);\n"
"}\n"
""));

        gridLayout_3->addWidget(clearBottleBtn, 12, 3, 2, 1);

        verticalFrame = new QFrame(frame);
        verticalFrame->setObjectName(QString::fromUtf8("verticalFrame"));
        verticalFrame->setFrameShape(QFrame::Box);
        verticalLayout_3 = new QVBoxLayout(verticalFrame);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_12 = new QLabel(verticalFrame);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setStyleSheet(QString::fromUtf8("color: rgb(50,50,50);\n"
"\n"
"font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_12->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_12);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        M354Sig = new QLabel(verticalFrame);
        M354Sig->setObjectName(QString::fromUtf8("M354Sig"));
        M354Sig->setAlignment(Qt::AlignCenter);

        gridLayout_8->addWidget(M354Sig, 0, 1, 1, 1);

        label_13 = new QLabel(verticalFrame);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_8->addWidget(label_13, 0, 0, 1, 1);

        label_15 = new QLabel(verticalFrame);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_8->addWidget(label_15, 0, 2, 1, 1);

        gridLayout_8->setColumnStretch(0, 1);
        gridLayout_8->setColumnStretch(1, 3);
        gridLayout_8->setColumnStretch(2, 1);

        verticalLayout_3->addLayout(gridLayout_8);


        gridLayout_3->addWidget(verticalFrame, 8, 3, 3, 1);

        verticalFrame1 = new QFrame(frame);
        verticalFrame1->setObjectName(QString::fromUtf8("verticalFrame1"));
        verticalFrame1->setFrameShape(QFrame::Box);
        verticalFrame1->setLineWidth(1);
        verticalLayout_5 = new QVBoxLayout(verticalFrame1);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, -1, 0, -1);
        label_9 = new QLabel(verticalFrame1);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(50,50,50);\n"
"\n"
"font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_9);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_10 = new QLabel(verticalFrame1);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_7->addWidget(label_10, 0, 0, 1, 1);

        X1Sig = new QLabel(verticalFrame1);
        X1Sig->setObjectName(QString::fromUtf8("X1Sig"));
        X1Sig->setStyleSheet(QString::fromUtf8("color: rgb(50,50,50);\n"
"\n"
"font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"\n"
"alignment:AlignHCenter,AlignVCenter;"));
        X1Sig->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(X1Sig, 0, 1, 1, 1);

        label_11 = new QLabel(verticalFrame1);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_7->addWidget(label_11, 0, 2, 1, 1);

        gridLayout_7->setColumnStretch(0, 1);
        gridLayout_7->setColumnStretch(1, 3);
        gridLayout_7->setColumnStretch(2, 1);

        verticalLayout_5->addLayout(gridLayout_7);


        gridLayout_3->addWidget(verticalFrame1, 4, 3, 4, 1);

        clearBtn = new QPushButton(frame);
        clearBtn->setObjectName(QString::fromUtf8("clearBtn"));
        clearBtn->setMinimumSize(QSize(100, 50));
        clearBtn->setFont(font3);
        clearBtn->setStyleSheet(QString::fromUtf8("QPushButton#clearBtn{\n"
"	min-width: 100px;\n"
"	min-height: 50px;\n"
"	background: rgb(85, 0, 255);\n"
"	border-radius: 4px;\n"
"	font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color:rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton#clearBtn:hover{	\n"
"	background-color: rgb(85, 85, 255);\n"
"}\n"
""));

        gridLayout_3->addWidget(clearBtn, 0, 3, 1, 1);

        label_29 = new QLabel(frame);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_29->sizePolicy().hasHeightForWidth());
        label_29->setSizePolicy(sizePolicy);
        label_29->setMinimumSize(QSize(0, 0));
        label_29->setMaximumSize(QSize(16777215, 40));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush5(QColor(50, 50, 50, 128));
        brush5.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Active, QPalette::PlaceholderText, brush5);
#endif
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush6(QColor(50, 50, 50, 128));
        brush6.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush6);
#endif
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QBrush brush7(QColor(50, 50, 50, 128));
        brush7.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush7);
#endif
        label_29->setPalette(palette2);
        label_29->setFont(font);
        label_29->setStyleSheet(QString::fromUtf8("color: rgb(50,50,50)"));
        label_29->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_29, 0, 0, 1, 1);

        label_30 = new QLabel(frame);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        sizePolicy.setHeightForWidth(label_30->sizePolicy().hasHeightForWidth());
        label_30->setSizePolicy(sizePolicy);
        label_30->setMinimumSize(QSize(0, 0));
        label_30->setMaximumSize(QSize(16777215, 40));
        label_30->setFont(font);
        label_30->setStyleSheet(QString::fromUtf8("color: rgb(50,50,50)"));
        label_30->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_30, 4, 0, 1, 1);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(0, 0));
        label_6->setMaximumSize(QSize(16777215, 40));
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(50,50,50)"));

        gridLayout_3->addWidget(label_6, 8, 0, 1, 1);

        BottleCountBox = new UnitSpainBox(frame);
        BottleCountBox->setObjectName(QString::fromUtf8("BottleCountBox"));
        BottleCountBox->setStyleSheet(QString::fromUtf8("QSpinBox{	\n"
"		border: 1px solid rgb(0,0,0);\n"
"		rgb:(50,50,50);\n"
"		background-color:transparent;\n"
"		font: 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
"\n"
"QSpinBox::up-button{\n"
"	subcontrol-origin: border;\n"
"	subcontrol-position: right;\n"
"	width: 0px;\n"
"	height: 20px;\n"
"	\n"
"	background-image: url(:/ico/hmi/add_right.png);\n"
"}\n"
"\n"
"QSpinBox::up-button:hover{\n"
"	\n"
"	background-image: url(:/ico/hmi/add_right(1).png);\n"
"}\n"
"\n"
"QSpinBox::down-button{\n"
"	subcontrol-origin: border;\n"
"	subcontrol-position: left;\n"
"	width: 0px;\n"
"	height: 20px;\n"
"\n"
"	background-image: url(:/ico/hmi/add_left.png);\n"
"}\n"
"\n"
"QSpinBox::down-button:hover{\n"
"	\n"
"	background-image: url(:/ico/hmi/add_left(1).png);\n"
"}"));
        BottleCountBox->setAlignment(Qt::AlignCenter);
        BottleCountBox->setMaximum(9999999);

        gridLayout_3->addWidget(BottleCountBox, 12, 1, 2, 2);

        progressBar = new QProgressBar(frame);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font4.setPointSize(25);
        font4.setBold(true);
        font4.setItalic(false);
        font4.setUnderline(false);
        font4.setWeight(75);
        font4.setStrikeOut(false);
        progressBar->setFont(font4);
        progressBar->setContextMenuPolicy(Qt::DefaultContextMenu);
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"   background-color: #FFFFFF;\n"
"   height:2;\n"
"}\n"
" \n"
"QProgressBar::chunk {\n"
"   background-color: rgb(255, 134, 152);\n"
"}\n"
" "));
        progressBar->setValue(0);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setInvertedAppearance(false);
        progressBar->setTextDirection(QProgressBar::TopToBottom);

        gridLayout_3->addWidget(progressBar, 6, 0, 2, 3);

        gridLayout_3->setRowStretch(0, 1);
        gridLayout_3->setColumnStretch(0, 3);

        gridLayout_4->addLayout(gridLayout_3, 1, 0, 1, 1);


        verticalLayout_4->addWidget(frame);


        gridLayout->addLayout(verticalLayout_4, 0, 2, 2, 2);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(0);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_8, 6, 3, 1, 1);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_12, 4, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_5, 9, 1, 5, 1);

        shaker3Dec = new QPushButton(mainInterface);
        shaker3Dec->setObjectName(QString::fromUtf8("shaker3Dec"));
        shaker3Dec->setMaximumSize(QSize(150, 40));
        shaker3Dec->setStyleSheet(QString::fromUtf8("QPushButton#shaker3Dec{\n"
"	min-width: 150px;\n"
"	min-height: 40px;\n"
"	background: rgb(85, 0, 255);\n"
"	border-radius: 4px;\n"
"	font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"		color:rgb(255, 255, 255);;\n"
"}\n"
"\n"
"QPushButton#shaker3Dec:hover{	\n"
"	background-color: rgb(85, 85, 255);\n"
"}\n"
"\n"
"QPushButton#shaker3Dec::checked{	\n"
"	background-color: #4dabf7;\n"
"}"));

        gridLayout_6->addWidget(shaker3Dec, 2, 4, 1, 1);

        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_13, 4, 2, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_7, 6, 1, 1, 1);

        verticalSpacer_14 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_14, 4, 4, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_3, 6, 4, 1, 1);

        studyBtn = new QPushButton(mainInterface);
        studyBtn->setObjectName(QString::fromUtf8("studyBtn"));
        studyBtn->setMinimumSize(QSize(150, 80));
        studyBtn->setMaximumSize(QSize(150, 80));
        studyBtn->setFont(font);
        studyBtn->setStyleSheet(QString::fromUtf8("QPushButton#studyBtn{\n"
"	min-width: 150px;\n"
"	min-height: 80px;\n"
"	background: rgb(85, 0, 255);\n"
"	border-radius: 4px;\n"
"	color:rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton#studyBtn:hover{	\n"
"	background-color: rgb(85, 85, 255);\n"
"}\n"
"\n"
"QPushButton#studyBtn::checked{	\n"
"	background-color: #a0eee1;\n"
"}"));
        studyBtn->setCheckable(true);

        gridLayout_6->addWidget(studyBtn, 9, 0, 5, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_3, 5, 3, 1, 1);

        Shaker2VBox = new UnitSpainBox(mainInterface);
        Shaker2VBox->setObjectName(QString::fromUtf8("Shaker2VBox"));
        Shaker2VBox->setMaximumSize(QSize(150, 40));
        Shaker2VBox->setStyleSheet(QString::fromUtf8("QSpinBox{	\n"
"		border: 1px solid rgb(0,0,0);\n"
"		rgb:(50,50,50);\n"
"		background-color:transparent;\n"
"		font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	min-width: 100px;\n"
"	min-height: 40px;\n"
"}\n"
"\n"
"QSpinBox::up-button{\n"
"	subcontrol-origin: border;\n"
"	subcontrol-position: right;\n"
"	width: 0px;\n"
"	height: 20px;\n"
"	\n"
"	background-image: url(:/ico/hmi/add_right.png);\n"
"}\n"
"\n"
"QSpinBox::up-button:hover{\n"
"	\n"
"	background-image: url(:/ico/hmi/add_right(1).png);\n"
"}\n"
"\n"
"QSpinBox::down-button{\n"
"	subcontrol-origin: border;\n"
"	subcontrol-position: left;\n"
"	width: 0px;\n"
"	height: 20px;\n"
"\n"
"	background-image: url(:/ico/hmi/add_left.png);\n"
"}\n"
"\n"
"QSpinBox::down-button:hover{\n"
"	\n"
"	background-image: url(:/ico/hmi/add_left(1).png);\n"
"}"));
        Shaker2VBox->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(Shaker2VBox, 1, 2, 1, 1);

        startBtn = new QPushButton(mainInterface);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));
        startBtn->setMinimumSize(QSize(150, 80));
        startBtn->setMaximumSize(QSize(150, 80));
        startBtn->setStyleSheet(QString::fromUtf8("QPushButton#startBtn{\n"
"	min-width: 150px;\n"
"	min-height: 80px;\n"
"	background: rgb(85, 255, 0);\n"
"	border-radius: 4px;\n"
"	font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
""));

        gridLayout_6->addWidget(startBtn, 5, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_2, 6, 2, 1, 1);

        shaker1Add = new QPushButton(mainInterface);
        shaker1Add->setObjectName(QString::fromUtf8("shaker1Add"));
        shaker1Add->setMaximumSize(QSize(150, 40));
        QPalette palette3;
        QBrush brush8(QColor(255, 255, 255, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush8);
        QBrush brush9(QColor(85, 0, 255, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush9);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush8);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush8);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush9);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush9);
        QBrush brush10(QColor(255, 255, 255, 128));
        brush10.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Active, QPalette::PlaceholderText, brush10);
#endif
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush8);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush9);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush8);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush8);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush9);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush9);
        QBrush brush11(QColor(255, 255, 255, 128));
        brush11.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush11);
#endif
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush8);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush9);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush8);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush8);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush9);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush9);
        QBrush brush12(QColor(255, 255, 255, 128));
        brush12.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush12);
#endif
        shaker1Add->setPalette(palette3);
        shaker1Add->setStyleSheet(QString::fromUtf8("QPushButton#shaker1Add{\n"
"	min-width: 150px;\n"
"	min-height: 40px;\n"
"	background: rgb(85, 0, 255);\n"
"	border-radius: 4px;\n"
"	font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color:rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton#shaker1Add:hover{	\n"
"	background-color: rgb(85, 85, 255);\n"
"}\n"
"\n"
"QPushButton#shaker1Add::checked{	\n"
"	background-color: #4dabf7;\n"
"}"));

        gridLayout_6->addWidget(shaker1Add, 0, 0, 1, 1);

        shaker2Dec = new QPushButton(mainInterface);
        shaker2Dec->setObjectName(QString::fromUtf8("shaker2Dec"));
        shaker2Dec->setMaximumSize(QSize(150, 40));
        shaker2Dec->setStyleSheet(QString::fromUtf8("QPushButton#shaker2Dec{\n"
"	min-width: 150px;\n"
"	min-height: 40px;\n"
"	background: rgb(85, 0, 255);\n"
"	border-radius: 4px;\n"
"	font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"		color:rgb(255, 255, 255);;\n"
"}\n"
"\n"
"QPushButton#shaker2Dec:hover{	\n"
"	background-color: rgb(85, 85, 255);\n"
"}\n"
"\n"
"QPushButton#shaker2Dec::checked{	\n"
"	background-color: #4dabf7;\n"
"}"));

        gridLayout_6->addWidget(shaker2Dec, 2, 2, 1, 1);

        stopBtn = new QPushButton(mainInterface);
        stopBtn->setObjectName(QString::fromUtf8("stopBtn"));
        stopBtn->setMaximumSize(QSize(150, 80));
        stopBtn->setStyleSheet(QString::fromUtf8("QPushButton#stopBtn{\n"
"	min-width: 150px;\n"
"	min-height: 80px;\n"
"	background:rgb(255, 0, 0);\n"
"	border-radius: 4px;\n"
"	font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
""));

        gridLayout_6->addWidget(stopBtn, 5, 2, 1, 1);

        saveImgBtn = new QPushButton(mainInterface);
        saveImgBtn->setObjectName(QString::fromUtf8("saveImgBtn"));
        saveImgBtn->setMinimumSize(QSize(150, 80));
        saveImgBtn->setMaximumSize(QSize(150, 80));
        saveImgBtn->setFont(font);
        saveImgBtn->setStyleSheet(QString::fromUtf8("QPushButton#saveImgBtn{\n"
"	min-width: 150px;\n"
"	min-height: 80px;\n"
"	background: rgb(85, 0, 255);\n"
"	border-radius: 4px;\n"
"	color:rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton#saveImgBtn:hover{	\n"
"	background-color: rgb(85, 85, 255);\n"
"}\n"
"\n"
"QPushButton#saveImgBtn::checked{	\n"
"	background-color: #a0eee1;\n"
"}"));
        saveImgBtn->setCheckable(true);

        gridLayout_6->addWidget(saveImgBtn, 9, 2, 5, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        beltPowerBtn = new QPushButton(mainInterface);
        beltPowerBtn->setObjectName(QString::fromUtf8("beltPowerBtn"));
        beltPowerBtn->setMaximumSize(QSize(150, 80));
        beltPowerBtn->setStyleSheet(QString::fromUtf8("QPushButton#beltPowerBtn{\n"
"	min-width: 150px;\n"
"	min-height: 80px;\n"
"	background: rgb(85, 0, 255);\n"
"	border-radius: 4px;\n"
"	color:rgb(255, 255, 255);\n"
"	font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
"\n"
"QPushButton#beltPowerBtn::checked{	\n"
"	background-color: rgb(255, 165, 0);\n"
"}"));
        beltPowerBtn->setCheckable(true);

        verticalLayout_2->addWidget(beltPowerBtn);

        verticalLayout_2->setStretch(0, 1);

        gridLayout_6->addLayout(verticalLayout_2, 12, 4, 1, 1);

        Shaker1VBox = new UnitSpainBox(mainInterface);
        Shaker1VBox->setObjectName(QString::fromUtf8("Shaker1VBox"));
        Shaker1VBox->setMinimumSize(QSize(102, 42));
        Shaker1VBox->setMaximumSize(QSize(150, 40));
        Shaker1VBox->setStyleSheet(QString::fromUtf8("QSpinBox{	\n"
"		border: 1px solid rgb(0,0,0);\n"
"		rgb:(50,50,50);\n"
"		background-color:transparent;\n"
"		font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	min-width: 100px;\n"
"	min-height: 40px;\n"
"}\n"
"\n"
"QSpinBox::up-button{\n"
"	subcontrol-origin: border;\n"
"	subcontrol-position: right;\n"
"	width: 0px;\n"
"	height: 20px;\n"
"	\n"
"	background-image: url(:/ico/hmi/add_right.png);\n"
"}\n"
"\n"
"QSpinBox::up-button:hover{\n"
"	\n"
"	background-image: url(:/ico/hmi/add_right(1).png);\n"
"}\n"
"\n"
"QSpinBox::down-button{\n"
"	subcontrol-origin: border;\n"
"	subcontrol-position: left;\n"
"	width: 0px;\n"
"	height: 20px;\n"
"\n"
"	background-image: url(:/ico/hmi/add_left.png);\n"
"}\n"
"\n"
"QSpinBox::down-button:hover{\n"
"	\n"
"	background-image: url(:/ico/hmi/add_left(1).png);\n"
"}"));
        Shaker1VBox->setAlignment(Qt::AlignCenter);
        Shaker1VBox->setMaximum(999999);

        gridLayout_6->addWidget(Shaker1VBox, 1, 0, 1, 1);

        shaker1Dec = new QPushButton(mainInterface);
        shaker1Dec->setObjectName(QString::fromUtf8("shaker1Dec"));
        shaker1Dec->setMaximumSize(QSize(150, 40));
        shaker1Dec->setStyleSheet(QString::fromUtf8("QPushButton#shaker1Dec{\n"
"	min-width: 150px;\n"
"	min-height: 40px;\n"
"	background: rgb(85, 0, 255);\n"
"	border-radius: 4px;\n"
"	font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"		color:rgb(255, 255, 255);;\n"
"}\n"
"\n"
"QPushButton#shaker1Dec:hover{	\n"
"	background-color: rgb(85, 85, 255);\n"
"}\n"
"\n"
"QPushButton#shaker1Dec::checked{	\n"
"	background-color: #4dabf7;\n"
"}"));

        gridLayout_6->addWidget(shaker1Dec, 2, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_6, 11, 3, 3, 1);

        Shaker3VBox = new UnitSpainBox(mainInterface);
        Shaker3VBox->setObjectName(QString::fromUtf8("Shaker3VBox"));
        Shaker3VBox->setMaximumSize(QSize(150, 40));
        Shaker3VBox->setStyleSheet(QString::fromUtf8("QSpinBox{	\n"
"		border: 1px solid rgb(0,0,0);\n"
"		rgb:(50,50,50);\n"
"		background-color:transparent;\n"
"		font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	min-width: 100px;\n"
"	min-height: 40px;\n"
"}\n"
"\n"
"QSpinBox::up-button{\n"
"	subcontrol-origin: border;\n"
"	subcontrol-position: right;\n"
"	width: 0px;\n"
"	height: 20px;\n"
"	\n"
"	background-image: url(:/ico/hmi/add_right.png);\n"
"}\n"
"\n"
"QSpinBox::up-button:hover{\n"
"	\n"
"	background-image: url(:/ico/hmi/add_right(1).png);\n"
"}\n"
"\n"
"QSpinBox::down-button{\n"
"	subcontrol-origin: border;\n"
"	subcontrol-position: left;\n"
"	width: 0px;\n"
"	height: 20px;\n"
"\n"
"	background-image: url(:/ico/hmi/add_left.png);\n"
"}\n"
"\n"
"QSpinBox::down-button:hover{\n"
"	\n"
"	background-image: url(:/ico/hmi/add_left(1).png);\n"
"}"));
        Shaker3VBox->setAlignment(Qt::AlignCenter);
        Shaker3VBox->setMaximum(999999);

        gridLayout_6->addWidget(Shaker3VBox, 1, 4, 1, 1);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 6, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_2, 5, 1, 1, 1);

        shaker3Add = new QPushButton(mainInterface);
        shaker3Add->setObjectName(QString::fromUtf8("shaker3Add"));
        shaker3Add->setMaximumSize(QSize(150, 40));
        shaker3Add->setStyleSheet(QString::fromUtf8("QPushButton#shaker3Add{\n"
"	min-width: 150px;\n"
"	min-height: 40px;\n"
"	background: rgb(85, 0, 255);\n"
"	border-radius: 4px;\n"
"	font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"		color:rgb(255, 255, 255);;\n"
"}\n"
"\n"
"QPushButton#shaker3Add:hover{	\n"
"	background-color: rgb(85, 85, 255);;\n"
"}\n"
"\n"
"QPushButton#shaker3Add::checked{	\n"
"	background-color: #4dabf7;\n"
"}"));

        gridLayout_6->addWidget(shaker3Add, 0, 4, 1, 1);

        shaker2Add = new QPushButton(mainInterface);
        shaker2Add->setObjectName(QString::fromUtf8("shaker2Add"));
        shaker2Add->setMaximumSize(QSize(150, 40));
        shaker2Add->setStyleSheet(QString::fromUtf8("QPushButton#shaker2Add{\n"
"	min-width: 150px;\n"
"	min-height: 40px;\n"
"	background: rgb(85, 0, 255);\n"
"	border-radius: 4px;\n"
"	font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"		color:rgb(255, 255, 255);;\n"
"}\n"
"\n"
"QPushButton#shaker2Add:hover{	\n"
"	background-color: rgb(85, 85, 255);\n"
"}\n"
"\n"
"QPushButton#shaker2Add::checked{	\n"
"	background-color: #4dabf7;\n"
"}"));

        gridLayout_6->addWidget(shaker2Add, 0, 2, 1, 1);

        clearBufferBtn = new QPushButton(mainInterface);
        clearBufferBtn->setObjectName(QString::fromUtf8("clearBufferBtn"));
        clearBufferBtn->setMaximumSize(QSize(150, 80));
        clearBufferBtn->setStyleSheet(QString::fromUtf8("QPushButton#clearBufferBtn{\n"
"	min-width: 150px;\n"
"	min-height: 80px;\n"
"	background: rgb(255, 255, 0);\n"
"	border-radius: 4px;\n"
"	font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color:rgb(50, 50, 50);\n"
"}\n"
"\n"
"QPushButton#clearBufferBtn::checked{	\n"
"	background-color: #4dabf7;\n"
"}"));
        clearBufferBtn->setCheckable(false);

        gridLayout_6->addWidget(clearBufferBtn, 5, 4, 1, 1);

        gridLayout_6->setRowStretch(0, 2);
        gridLayout_6->setColumnStretch(0, 3);

        gridLayout->addLayout(gridLayout_6, 3, 2, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(3, 2, 2, 3);
        horizontalSpacer_9 = new QSpacerItem(600, 5, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_9);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_5);

        DisplayLayout = new QVBoxLayout();
        DisplayLayout->setObjectName(QString::fromUtf8("DisplayLayout"));

        verticalLayout->addLayout(DisplayLayout);

        chartLayout = new QVBoxLayout();
        chartLayout->setSpacing(0);
        chartLayout->setObjectName(QString::fromUtf8("chartLayout"));
        chartLayout->setSizeConstraint(QLayout::SetMaximumSize);

        verticalLayout->addLayout(chartLayout);

        LogLayout = new QVBoxLayout();
        LogLayout->setObjectName(QString::fromUtf8("LogLayout"));

        verticalLayout->addLayout(LogLayout);

        verticalLayout->setStretch(2, 4);
        verticalLayout->setStretch(3, 3);
        verticalLayout->setStretch(4, 3);

        gridLayout->addLayout(verticalLayout, 0, 0, 4, 2);

        verticalSpacer_4 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout->addItem(verticalSpacer_4, 2, 2, 1, 2);

        stackedWidget->addWidget(mainInterface);

        gridLayout_2->addWidget(stackedWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(toolBar->sizePolicy().hasHeightForWidth());
        toolBar->setSizePolicy(sizePolicy1);
        QFont font5;
        font5.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        toolBar->setFont(font5);
        toolBar->setStyleSheet(QString::fromUtf8("color: rgb(50,50,50)"));
        toolBar->setMovable(true);
        toolBar->setAllowedAreas(Qt::AllToolBarAreas);
        toolBar->setOrientation(Qt::Horizontal);
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(login);
        toolBar->addAction(mainInterfaceAction);
        toolBar->addAction(setInterfaceAction);
        toolBar->addAction(imageInterfaceAction);
        toolBar->addAction(start);
        toolBar->addSeparator();

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\211\221\347\203\275\346\234\272\346\242\260", nullptr));
        login->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\347\231\273\345\205\245", nullptr));
#if QT_CONFIG(tooltip)
        login->setToolTip(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\347\231\273\345\205\245", nullptr));
#endif // QT_CONFIG(tooltip)
        mainInterfaceAction->setText(QCoreApplication::translate("MainWindow", "\344\270\273\347\225\214\351\235\242", nullptr));
        setInterfaceAction->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\347\225\214\351\235\242", nullptr));
        start->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\350\277\220\350\241\214", nullptr));
        imageInterfaceAction->setText(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\345\233\276\347\211\207", nullptr));
        FullScreen->setText(QString());
        Exit->setText(QString());
        curRecipe->setText(QCoreApplication::translate("MainWindow", "CurrentMode", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\350\243\205\347\223\266\351\200\237\345\272\246", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\345\267\262\350\243\205\347\223\266\346\225\260\351\207\217", nullptr));
        clearBottleBtn->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\233\266", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\350\277\207\351\207\217\350\255\246\345\221\212", nullptr));
        M354Sig->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        label_13->setText(QString());
        label_15->setText(QString());
        label_9->setText(QCoreApplication::translate("MainWindow", "\346\234\211\347\223\266\344\277\241\345\217\267", nullptr));
        label_10->setText(QString());
        X1Sig->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        label_11->setText(QString());
        clearBtn->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\233\266", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "\345\275\223\345\211\215\346\225\260\351\207\217", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "\345\215\225\347\223\266\346\225\260\351\207\217", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\350\256\241\346\225\260\351\200\237\345\272\246", nullptr));
        shaker3Dec->setText(QCoreApplication::translate("MainWindow", "3\347\272\247\346\214\257\345\212\250\347\233\230- -", nullptr));
        studyBtn->setText(QCoreApplication::translate("MainWindow", "\345\255\246\344\271\240\346\225\260\346\215\256", nullptr));
        startBtn->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250", nullptr));
        shaker1Add->setText(QCoreApplication::translate("MainWindow", "1\347\272\247\346\214\257\345\212\250\347\233\230++", nullptr));
        shaker2Dec->setText(QCoreApplication::translate("MainWindow", "2\347\272\247\346\214\257\345\212\250\347\233\230- -", nullptr));
        stopBtn->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        saveImgBtn->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\345\233\276\347\211\207", nullptr));
        beltPowerBtn->setText(QCoreApplication::translate("MainWindow", "\344\274\240\351\200\201\345\270\246", nullptr));
        shaker1Dec->setText(QCoreApplication::translate("MainWindow", "1\347\272\247\346\214\257\345\212\250\347\233\230- -", nullptr));
        shaker3Add->setText(QCoreApplication::translate("MainWindow", "3\347\272\247\346\214\257\345\212\250\347\233\230++", nullptr));
        shaker2Add->setText(QCoreApplication::translate("MainWindow", "2\347\272\247\346\214\257\345\212\250\347\233\230++", nullptr));
        clearBufferBtn->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\223\266", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
