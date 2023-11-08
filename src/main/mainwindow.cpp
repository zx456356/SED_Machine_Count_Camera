#include <QValueAxis>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingwidget.h"
#include "ui_settingwidget.h"

#define HD 41088

#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    set = new SettingWidget(this);
    view = new ViewWidget();
    this->showFullScreen();

    setCentralWidget(ui->stackedWidget);
    ui->stackedWidget->addWidget(set);
    ui->stackedWidget->addWidget(view);

    loginWindow = new login(this);

    vg = new VisionGraph(GraphType::graph_Info);
    vg->setGraphType(GraphType::graph_Info,item_NO);
    //ui->DisplayLayout->addWidget(vg);

    ui->DisplayLayout->addWidget(vg);

    QImage BkImg(QApplication::applicationDirPath() + "/ico/SED_ico.png");
    vg->setBkImg(BkImg);

    //set->ui->verticalLayout_4->addWidget(Loge);
    ui->LogLayout->addWidget(Loge);
    setLog(Loge);

    ui->currentNumBox->setReadOnly(true);
    ui->countSpeedBox->setReadOnly(true);
    ui->BottleCountBox->setReadOnly(true);
    ui->BottleCountBox->setReadOnly(true);
    ui->Shaker1VBox->SetUnitText("V",ui->currentNumBox->font().pixelSize());
    ui->Shaker2VBox->SetUnitText("V",ui->currentNumBox->font().pixelSize());
    ui->Shaker3VBox->SetUnitText("V",ui->currentNumBox->font().pixelSize());

    ui->singleNumBox->setValue(set->ui->singleButtleQuantity->value());

   seriesCS->setName("颗/秒");   //自动添加折线名字
   seriesBS->setName("瓶/分");

   //创建坐标
   QValueAxis *axisX = new QValueAxis();//X轴
   QValueAxis *axisY = new QValueAxis(); //Y 轴

   axisX->setRange(0, 50);//设置坐标轴范围

   axisX->setTitleText("装瓶数目");//标题
   axisX->setTitleFont(QFont("微软雅黑", 10));
   axisX->setLabelFormat("%i"); //标签格式：每个单位保留几位小数
   axisX->setTickCount(26); //主分隔个数：0到10分成20个单位
   axisX->setMinorTickCount(1); //每个单位之间绘制了多少虚网线
   //axisX->setGridLineVisible(false);


   axisY->setRange(0,100);
  // axisY->setTitleText("每秒钟装料/瓶");
   axisY->setTitleFont(QFont("微软雅黑", 10));
   axisY->setLabelFormat("%i"); //标签格式
   axisY->setTickCount(6);
   axisY->setMinorTickCount(1);
   //axisX->setGridLineVisible(false);

    dateLab = new QLabel(this);
    timeLab = new QLabel(this);
    QWidget *spacer1 = new QWidget();
    QWidget *spacer2 = new QWidget();
    QWidget *spacer3 = new QWidget();
    QWidget *spacer4 = new QWidget();
    spacer1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer2->setBaseSize(50, 100);
    spacer2->setMaximumSize(50, 100);
    spacer2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer3->setBaseSize(20, 100);
    spacer3->setMaximumSize(20, 100);
    spacer3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer4->setBaseSize(20, 100);
    spacer4->setMaximumSize(20, 100);
    spacer4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->toolBar->addWidget(spacer1);
    ui->toolBar->addWidget(dateLab);
    ui->toolBar->addWidget(spacer2);
    ui->toolBar->addWidget(timeLab);
    ui->toolBar->addWidget(spacer3);
    //ui->toolBar->addAction(ui->Exit);
    dateLab->setFont(QFont("微软雅黑", 16));
    timeLab->setFont(QFont("微软雅黑", 16));
    toolBarInit();

    isErrorImage = false;
    //图像显示
//    QTimer *showTimer = new QTimer(this);
//    connect(showTimer, SIGNAL(timeout()), this, SLOT(ShowImage()));
//    showTimer->start(100);

    ShowImage();
    //saveImageO();
    connect(this, SIGNAL(signal_showImage(QImage)), this, SLOT(slot_showImage(QImage)));
    //connect(mindcam, SIGNAL(sendImageShow(QImage)), this, SLOT(recImage(QImage)));
    //登录确认
    connect(loginWindow->ui->loginBtn, SIGNAL(clicked()), this, SLOT(loginBtn()));
    connect(loginWindow, SIGNAL(sendLogin()), this, SLOT(loginBtn()));

    //登录取消
    connect(loginWindow->ui->loginCancelBtn, SIGNAL(clicked()), this, SLOT(loginCancelBtn()));

    //登录界面关闭
    connect(loginWindow, SIGNAL(sendData()), this, SLOT(loginClose()));

    // 在构造函数中创建 QTimer 对象
    QTimer *timerbk = new QTimer(this);

    // 连接 QTimer 的 timeout 信号到需要执行的槽函数
    connect(timerbk, SIGNAL(timeout()), this, SLOT(BkIMgFit()));

    // 启动 QTimer，并设置延时时间
    timerbk->start(1000); // 延时 1000 毫秒，即 1 秒

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Showexec()));
    timer->start(200);

    saveImgPool = new QThreadPool();
    saveImgPool->setMaxThreadCount(10);

    ui->Shaker1VBox->setValue(set->ui->shaker1VBox->value());
    ui->Shaker2VBox->setValue(set->ui->shaker2VBox->value());
    ui->Shaker3VBox->setValue(set->ui->shaker3VBox->value());

    connect(set, &SettingWidget::Shaker1VBoxChanged,this, &MainWindow::ChangeShaker1VText);
    connect(set, &SettingWidget::Shaker2VBoxChanged,this, &MainWindow::ChangeShaker2VText);
    connect(set, &SettingWidget::Shaker3VBoxChanged,this, &MainWindow::ChangeShaker3VText);
    connect(set, &SettingWidget::tabWidgetEqul_2,this, &MainWindow::HandModeStop);
    connect(set, &SettingWidget::SingleNumBoxChanged_Sig,this,&MainWindow::SingleNumBoxChanged);
    connect(set ,&SettingWidget::exitSig,this,&MainWindow::ExitProgram);

    //setLED(ui->X1Sig,0,50);

    LEDFlashTimer = new QTimer(this);

    MainWindow* mw = nullptr;

    mw = this;

    cp->seY = 0;
    Log::Instance()->writeInfo("程序初始化完成");
    ui->currentNumBox->setValue(0);
    EStoped = false;

    //translation
    if(loadXML()){
        QStringList strList;
        xmlEle = xmlDoc.FirstChildElement()->FirstChildElement("language");
        while(xmlEle){
            strList << xmlEle->Attribute("name");
            xmlEle = xmlEle->NextSiblingElement("language");
        }
        set->ui->comboBox->addItems(strList);

        xmlEle = xmlDoc.FirstChildElement()->FirstChildElement("set");
        const char* curLang = xmlEle->Attribute("current");
        set->ui->comboBox->setCurrentText(curLang);
        loadTranslation(curLang);

        connect(set->ui->comboBox, &QComboBox::currentTextChanged, [this]{
            QString curText = set->ui->comboBox->currentText();
            QByteArray lang_name = curText.toUtf8();
            const char *name_byte = lang_name.constData();

            writeCurrToXML(name_byte);
            loadTranslation(name_byte);
        });
    }
}

void MainWindow::iniLeftBar()
{

}

MainWindow::~MainWindow()
{
    delete ui;
    delete set;
    delete loginWindow;
    delete vg;

}

bool MainWindow::loadXML()
{
    xmlErr = xmlDoc.LoadFile("translation_setup.xml");
    if(xmlErr != 0){
        Log::Instance()->writeError("Load translation config failure.");
        return false;
    }
    return true;
}

void MainWindow::loadTranslation(const char* language)
{
    QString lang = language;
    tinyxml2::XMLElement     *xml_ele;
    xml_ele = xmlDoc.FirstChildElement()->FirstChildElement("language");
    while(xml_ele){
        QString attr = xml_ele->Attribute("name");
        if(attr != lang){
            xml_ele = xml_ele->NextSiblingElement("language");
        }
        else{
            tinyxml2::XMLElement     *item;
            item = xml_ele->FirstChildElement("mainWin");
            attr = item->Attribute("desc");
            this->ui->mainInterfaceAction->setText(attr);

            item = xml_ele->FirstChildElement("login");
            attr = item->Attribute("desc");
            this->ui->login->setText(attr);

            item = xml_ele->FirstChildElement("setup");
            attr = item->Attribute("desc");
            this->ui->setInterfaceAction->setText(attr);

            item = xml_ele->FirstChildElement("viewImg");
            attr = item->Attribute("desc");
            this->ui->imageInterfaceAction->setText(attr);

            item = xml_ele->FirstChildElement("start");
            attr = item->Attribute("desc");
            this->ui->start->setText(attr);

            item = xml_ele->FirstChildElement("corporate");
            attr = item->Attribute("desc");
            //this->ui->label_3->setText(attr);

            item = xml_ele->FirstChildElement("recipe");
            attr = item->Attribute("desc");
            this->ui->curRecipe->setText(attr);

            item = xml_ele->FirstChildElement("curNum");
            attr = item->Attribute("desc");
            this->ui->label_29->setText(attr);

            item = xml_ele->FirstChildElement("clear1");
            attr = item->Attribute("desc");
            //this->ui->clearBtn->setText(attr);

            item = xml_ele->FirstChildElement("numPerBottle");
            attr = item->Attribute("desc");
            this->ui->label_30->setText(attr);

            item = xml_ele->FirstChildElement("haveBottle");
            attr = item->Attribute("desc");
            //this->ui->label_9->setText(attr);

            item = xml_ele->FirstChildElement("countSpd");
            attr = item->Attribute("desc");
            this->ui->label_6->setText(attr);

            item = xml_ele->FirstChildElement("fillSpd");
            attr = item->Attribute("desc");
            this->ui->label_8->setText(attr);

            item = xml_ele->FirstChildElement("excessSignal");
            attr = item->Attribute("desc");
            //this->ui->label_12->setText(attr);

            item = xml_ele->FirstChildElement("filledNum");
            attr = item->Attribute("desc");
            this->ui->label_7->setText(attr);

            item = xml_ele->FirstChildElement("clear2");
            attr = item->Attribute("desc");
            //this->ui->clearBottleBtn->setText(attr);

            item = xml_ele->FirstChildElement("shaker1Add");
            attr = item->Attribute("desc");
            this->ui->shaker1Add->setText(attr);

            item = xml_ele->FirstChildElement("shaker1Dec");
            attr = item->Attribute("desc");
            this->ui->shaker1Dec->setText(attr);

            item = xml_ele->FirstChildElement("shaker2Add");
            attr = item->Attribute("desc");
            this->ui->shaker2Add->setText(attr);

            item = xml_ele->FirstChildElement("shaker2Dec");
            attr = item->Attribute("desc");
            this->ui->shaker2Dec->setText(attr);

            item = xml_ele->FirstChildElement("shaker3Add");
            attr = item->Attribute("desc");
            this->ui->shaker3Add->setText(attr);

            item = xml_ele->FirstChildElement("shaker3Dec");
            attr = item->Attribute("desc");
            this->ui->shaker3Dec->setText(attr);

            item = xml_ele->FirstChildElement("startUp");
            attr = item->Attribute("desc");
            this->ui->startBtn->setText(attr);

            item = xml_ele->FirstChildElement("shutDown");
            attr = item->Attribute("desc");
            this->ui->stopBtn->setText(attr);

            item = xml_ele->FirstChildElement("clearBottle");
            attr = item->Attribute("desc");
            this->ui->clearBufferBtn->setText(attr);

            item = xml_ele->FirstChildElement("autoLearn");
            attr = item->Attribute("desc");
            this->ui->studyBtn->setText(attr);

            item = xml_ele->FirstChildElement("saveImg");
            attr = item->Attribute("desc");
            this->ui->saveImgBtn->setText(attr);

            item = xml_ele->FirstChildElement("belt");
            attr = item->Attribute("desc");
            this->ui->beltPowerBtn->setText(attr);

            item = xml_ele->FirstChildElement("grain");
            attr = item->Attribute("desc");
            this->ui->currentNumBox->SetUnitText(attr, ui->currentNumBox->font().pixelSize());

            item = xml_ele->FirstChildElement("grainPerBottle");
            attr = item->Attribute("desc");
            this->ui->singleNumBox->SetUnitText(attr, ui->currentNumBox->font().pixelSize());

            item = xml_ele->FirstChildElement("grainPerSec");
            attr = item->Attribute("desc");
            this->ui->countSpeedBox->SetUnitText(attr, ui->currentNumBox->font().pixelSize());

            item = xml_ele->FirstChildElement("bottlePerMin");
            attr = item->Attribute("desc");
            this->ui->bottleSpeedBox->SetUnitText(attr, ui->currentNumBox->font().pixelSize());

            item = xml_ele->FirstChildElement("bottle");
            attr = item->Attribute("desc");
            this->ui->BottleCountBox->SetUnitText(attr, ui->currentNumBox->font().pixelSize());

            item = xml_ele->FirstChildElement("swRecipe");
            attr = item->Attribute("desc");
            set->ui->treeWidget->headerItem()->setText(0, attr);

            item = xml_ele->FirstChildElement("swRecipeName");
            attr = item->Attribute("desc");
            set->ui->label->setText(attr);

            item = xml_ele->FirstChildElement("swLoad");
            attr = item->Attribute("desc");
            set->ui->loadBtn->setText(attr);

            item = xml_ele->FirstChildElement("swNew");
            attr = item->Attribute("desc");
            set->ui->newBtn->setText(attr);

            item = xml_ele->FirstChildElement("swSave");
            attr = item->Attribute("desc");
            set->ui->saveBtn->setText(attr);

            item = xml_ele->FirstChildElement("swDel");
            attr = item->Attribute("desc");
            set->ui->delBtn->setText(attr);

            item = xml_ele->FirstChildElement("swExit");
            attr = item->Attribute("desc");
            set->ui->ExitBtn->setText(attr);

            item = xml_ele->FirstChildElement("ip");
            attr = item->Attribute("desc");
            set->ui->tabWidget->setTabText(0, attr);

            item = xml_ele->FirstChildElement("ipQuantity");
            attr = item->Attribute("desc");
            set->ui->label_14->setText(attr);

            item = xml_ele->FirstChildElement("ipThreshold");
            attr = item->Attribute("desc");
            set->ui->label_5->setText(attr);

            item = xml_ele->FirstChildElement("ipPreprocess");
            attr = item->Attribute("desc");
            set->ui->label_26->setText(attr);

            item = xml_ele->FirstChildElement("ipArea");
            attr = item->Attribute("desc");
            set->ui->label_7->setText(attr);

            item = xml_ele->FirstChildElement("ipRadius");
            attr = item->Attribute("desc");
            set->ui->label_9->setText(attr);

            item = xml_ele->FirstChildElement("ipFill");
            attr = item->Attribute("desc");
            set->ui->label_11->setText(attr);

            item = xml_ele->FirstChildElement("ipUnfitArea");
            attr = item->Attribute("desc");
            set->ui->label_25->setText(attr);

            item = xml_ele->FirstChildElement("ipUnfitRadius");
            attr = item->Attribute("desc");
            set->ui->label_32->setText(attr);

            item = xml_ele->FirstChildElement("ipRemnent");
            attr = item->Attribute("desc");
            set->ui->label_51->setText(attr);

            item = xml_ele->FirstChildElement("ipOperater");
            attr = item->Attribute("desc");
            set->ui->label_33->setText(attr);

            item = xml_ele->FirstChildElement("ipOpenRound");
            attr = item->Attribute("desc");
            set->ui->preProcessCombox->setItemText(0, attr);

            item = xml_ele->FirstChildElement("ipOpenRect");
            attr = item->Attribute("desc");
            set->ui->preProcessCombox->setItemText(1, attr);

            item = xml_ele->FirstChildElement("ipCloseRound");
            attr = item->Attribute("desc");
            set->ui->preProcessCombox->setItemText(2, attr);

            item = xml_ele->FirstChildElement("ipCloseRect");
            attr = item->Attribute("desc");
            set->ui->preProcessCombox->setItemText(3, attr);

            item = xml_ele->FirstChildElement("ipGrainBottle");
            attr = item->Attribute("desc");
            set->ui->singleButtleQuantity->SetUnitText(attr, 14);

            item = xml_ele->FirstChildElement("ipGrain");
            attr = item->Attribute("desc");
            set->ui->restWarnBox->SetUnitText(attr, 14);

            item = xml_ele->FirstChildElement("cp");
            attr = item->Attribute("desc");
            set->ui->tabWidget->setTabText(1, attr);

            item = xml_ele->FirstChildElement("cpLineFreq");
            attr = item->Attribute("desc");
            set->ui->label_3->setText(attr);

            item = xml_ele->FirstChildElement("cpGain");
            attr = item->Attribute("desc");
            set->ui->label_2->setText(attr);

            item = xml_ele->FirstChildElement("cpExposure");
            attr = item->Attribute("desc");
            set->ui->label_4->setText(attr);

            item = xml_ele->FirstChildElement("cpRTQuant");
            attr = item->Attribute("desc");
            set->ui->label_15->setText(attr);

            item = xml_ele->FirstChildElement("cpBottQuant");
            attr = item->Attribute("desc");
            set->ui->label_19->setText(attr);

            item = xml_ele->FirstChildElement("cpCoordX");
            attr = item->Attribute("desc");
            set->ui->label_16->setText(attr);

            item = xml_ele->FirstChildElement("cpCoordY");
            attr = item->Attribute("desc");
            set->ui->label_20->setText(attr);

            item = xml_ele->FirstChildElement("cpFull");
            attr = item->Attribute("desc");
            set->ui->label_17->setText(attr);

            item = xml_ele->FirstChildElement("cpBad");
            attr = item->Attribute("desc");
            set->ui->label_21->setText(attr);

            item = xml_ele->FirstChildElement("mc");
            attr = item->Attribute("desc");
            set->ui->tabWidget->setTabText(2, attr);

            item = xml_ele->FirstChildElement("mcBelt");
            attr = item->Attribute("desc");
            set->ui->beltBtn->setText(attr);

            item = xml_ele->FirstChildElement("mcBlock");
            attr = item->Attribute("desc");
            set->ui->blockBtn->setText(attr);

            item = xml_ele->FirstChildElement("mcRemove");
            attr = item->Attribute("desc");
            set->ui->removeBtn->setText(attr);

            item = xml_ele->FirstChildElement("mcFunnel");
            attr = item->Attribute("desc");
            set->ui->funnelBtn->setText(attr);

            item = xml_ele->FirstChildElement("mcBuffer");
            attr = item->Attribute("desc");
            set->ui->bufferBtn->setText(attr);

            item = xml_ele->FirstChildElement("mcShaker");
            attr = item->Attribute("desc");
            set->ui->shackerBtn->setText(attr);

            item = xml_ele->FirstChildElement("mcBuffer1");
            attr = item->Attribute("desc");
            set->ui->bufferBtn_1->setText(attr);

            item = xml_ele->FirstChildElement("mcBuffer2");
            attr = item->Attribute("desc");
            set->ui->bufferBtn_2->setText(attr);

            item = xml_ele->FirstChildElement("mcBuffer3");
            attr = item->Attribute("desc");
            set->ui->bufferBtn_3->setText(attr);

            item = xml_ele->FirstChildElement("mcBuffer4");
            attr = item->Attribute("desc");
            set->ui->bufferBtn_4->setText(attr);

            item = xml_ele->FirstChildElement("mcBuffer5");
            attr = item->Attribute("desc");
            set->ui->bufferBtn_5->setText(attr);

            item = xml_ele->FirstChildElement("mcBuffer6");
            attr = item->Attribute("desc");
            set->ui->bufferBtn_6->setText(attr);

            item = xml_ele->FirstChildElement("mcBuffer7");
            attr = item->Attribute("desc");
            set->ui->bufferBtn_7->setText(attr);

            item = xml_ele->FirstChildElement("mcBuffer8");
            attr = item->Attribute("desc");
            set->ui->bufferBtn_8->setText(attr);

            item = xml_ele->FirstChildElement("ep");
            attr = item->Attribute("desc");
            set->ui->tabWidget->setTabText(3, attr);

            item = xml_ele->FirstChildElement("epCut");
            attr = item->Attribute("desc");
            set->ui->label_34->setText(attr);

            item = xml_ele->FirstChildElement("epDown");
            attr = item->Attribute("desc");
            set->ui->label_35->setText(attr);

            item = xml_ele->FirstChildElement("epFill");
            attr = item->Attribute("desc");
            set->ui->label_49->setText(attr);

            item = xml_ele->FirstChildElement("epChange");
            attr = item->Attribute("desc");
            set->ui->label_36->setText(attr);

            item = xml_ele->FirstChildElement("epExpelTime");
            attr = item->Attribute("desc");
            set->ui->label_39->setText(attr);

            item = xml_ele->FirstChildElement("epExpelDelay");
            attr = item->Attribute("desc");
            set->ui->label_40->setText(attr);

            item = xml_ele->FirstChildElement("epShake");
            attr = item->Attribute("desc");
            set->ui->label_37->setText(attr);

            item = xml_ele->FirstChildElement("epBolckBottle2");
            attr = item->Attribute("desc");
            set->ui->label_38->setText(attr);

            item = xml_ele->FirstChildElement("epVibr1Volt");
            attr = item->Attribute("desc");
            set->ui->label_41->setText(attr);

            item = xml_ele->FirstChildElement("epVibr1Freq");
            attr = item->Attribute("desc");
            set->ui->label_42->setText(attr);

            item = xml_ele->FirstChildElement("epVibr2Volt");
            attr = item->Attribute("desc");
            set->ui->label_43->setText(attr);

            item = xml_ele->FirstChildElement("epVibr2Freq");
            attr = item->Attribute("desc");
            set->ui->label_44->setText(attr);

            item = xml_ele->FirstChildElement("epVibr3Volt");
            attr = item->Attribute("desc");
            set->ui->label_45->setText(attr);

            item = xml_ele->FirstChildElement("epVibr3Freq");
            attr = item->Attribute("desc");
            set->ui->label_46->setText(attr);

            item = xml_ele->FirstChildElement("epStopRadio");
            attr = item->Attribute("desc");
            set->ui->label_50->setText(attr);

            item = xml_ele->FirstChildElement("epMotorUp");
            attr = item->Attribute("desc");
            //set->ui->MotorUpbtn->setText(attr);

            item = xml_ele->FirstChildElement("epShed");
            attr = item->Attribute("desc");
            //set->ui->sheddingBtn->setText(attr);

            item = xml_ele->FirstChildElement("epMotorDown");
            attr = item->Attribute("desc");
            //set->ui->MotorDownbtn->setText(attr);

            item = xml_ele->FirstChildElement("op");
            attr = item->Attribute("desc");
            set->ui->tabWidget->setTabText(4, attr);

            item = xml_ele->FirstChildElement("opRunTime");
            attr = item->Attribute("desc");
            set->ui->label_29->setText(attr);

            item = xml_ele->FirstChildElement("opLanguage");
            attr = item->Attribute("desc");
            set->ui->label_52->setText(attr);

            item = xml_ele->FirstChildElement("opImageSave");
            attr = item->Attribute("desc");
            set->ui->groupBox->setTitle(attr);

            item = xml_ele->FirstChildElement("opIsSave");
            attr = item->Attribute("desc");
            set->ui->IsSaveImg->setText(attr);

            item = xml_ele->FirstChildElement("opDirectory");
            attr = item->Attribute("desc");
            set->ui->label_30->setText(attr);

            item = xml_ele->FirstChildElement("opDays");
            attr = item->Attribute("desc");
            set->ui->label_31->setText(attr);

            item = xml_ele->FirstChildElement("opPath");
            attr = item->Attribute("desc");
            set->ui->saveImgPathBtn->setText(attr);

            item = xml_ele->FirstChildElement("log");
            attr = item->Attribute("desc");
            set->ui->tabWidget->setTabText(5, attr);

            break;
        }
    }
}

QString MainWindow::findTranslation(const char* name)
{
    if(loadXML()){
        tinyxml2::XMLElement     *xml_ele;
        QString text = set->ui->comboBox->currentText();
        xml_ele = xmlDoc.FirstChildElement()->FirstChildElement("language");
        while(xml_ele){
            QString attr = xml_ele->Attribute("name");
            if(attr == text){
                tinyxml2::XMLElement     *item;
                item = xml_ele->FirstChildElement(name);
                attr = item->Attribute("desc");
                return QString(attr);
            }
            else{
                xml_ele = xml_ele->NextSiblingElement("language");
            }
        }
    }
    return QString();
}

void MainWindow::writeCurrToXML(const char* language)
{
    tinyxml2::XMLElement     *xml_ele;

    xml_ele = xmlDoc.FirstChildElement()->FirstChildElement("set");
    if(xml_ele){
        xml_ele->SetAttribute("current", language);
        xmlErr = xmlDoc.SaveFile("translation_setup.xml");
        if(xmlErr == 0) Log::Instance()->writeInfo("write xml success.");
        else Log::Instance()->writeError("write xml failure.");
    }
    else Log::Instance()->writeError("No element named set.");
}

void MainWindow::BkIMgFit()
{
    vg->setViewSize_Fit();
}

void MainWindow::setLog(XVLogWidget* Log)
{
   QFont LogFont;
   LogFont.setFamily("Microsoft YaHei");
   LogFont.setPixelSize(30);
   Log->setFont(LogFont);
}

void MainWindow::setLED(QLabel* label, int color, int size)
{

    // 该函数将label控件变成一个圆形指示灯，需要指定颜色color以及直径size
    // color 0:grey 1:red 2:green 3:yellow
    // size  单位是像素

    // 将label中的文字清空
    label->setText(" ");

    // 先设置矩形大小
    // 如果ui界面设置的label大小比最小宽度和高度小，矩形将被设置为最小宽度和最小高度；
    // 如果ui界面设置的label大小比最小宽度和高度大，矩形将被设置为最大宽度和最大高度；
    QString min_width = QString("min-width: %1px;").arg(size);              // 最小宽度：size
    QString min_height = QString("min-height: %1px;").arg(size);            // 最小高度：size
    QString max_width = QString("max-width: %1px;").arg(size);              // 最小宽度：size
    QString max_height = QString("max-height: %1px;").arg(size);            // 最小高度：size
    // 再设置边界形状及边框
    QString border_radius = QString("border-radius: %1px;").arg(size/2);    // 边框是圆角，半径为size/2
    QString border = QString("border:1px solid black;");                    // 边框为1px黑色
    //QString HCenter = QString("align: center");
     //label->setAlignment(Qt::AlignmentFlag::AlignHCenter);
     //label->setAlignment(Qt::AlignmentFlag::AlignVCenter);
    // 最后设置背景颜色
    QString background = "background-color:";
    switch (color) {
    case 0:
        // 灰色
        background += "rgb(190,190,190)";
        break;
    case 1:
        // 红色
        background += "rgb(255,0,0)";
        break;
    case 2:
        // 绿色
        background += "rgb(0,255,0)";
        break;
    case 3:
        // 黄色
        background += "rgb(255,255,0)";
        break;
    default:
        break;
    }
    QString alignment = QString("text-align:center");
    const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background ;//+ alignment;
    label->setStyleSheet(SheetStyle);

    label->setAlignment(Qt::AlignmentFlag::AlignHCenter);
    label->setAlignment(Qt::AlignmentFlag::AlignVCenter);
}

void MainWindow::resizeEvent(QResizeEvent *)
{
//    if(sa)
//    {
//        //qDebug()<<height();
//        sa->setGeometry(0,70,width(),height()-0);
//        ui->centralwidget->setMinimumSize(width(),height()-0);
//    }
    ;
}

//关闭窗口事件
void MainWindow::closeEvent(QCloseEvent *)
{
    /*保存当前配置路径*/
    QString filename = QApplication::applicationDirPath() + "/Config" + "/system";
    QSettings *iniWrite = new QSettings(filename, QSettings::IniFormat);
    iniWrite->setValue("LastConfigPath",
                       ("/Config/" + set->ui->treeWidget->currentItem()->text(0)));

    QString filename1 = QApplication::applicationDirPath() + "/Config" + "/" + set->ui->treeWidget->currentItem()->text(0);

    set->writeConfig(filename1);
    ui->start->setChecked(false);
}

void MainWindow::Showexec()
{
    vg->setViewSize_Fit();
    ui->curRecipe->setText(set->currentMode);
    dateLab->setText(QDate::currentDate().toString("yyyy-MM-dd"));
    timeLab->setText(QTime::currentTime().toString("hh:mm:ss"));
    ui->countSpeedBox->setValue(cp->countSpeed);
    ui->bottleSpeedBox->setValue(cp->bottleSpeed);
    ui->BottleCountBox->setValue(mt->bottleCount);

    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false  && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        modbus_read_bits(mt->modbus,1,1,&m1[0]);        //读取有瓶信号
        modbus_read_bits(mt->modbus,354,1,&m354[0]);    //读取过量多次报警
        modbus_read_bits(mt->modbus,355,1,&m355[0]);    //读取过量报警给出Log
        modbus_read_bits(mt->modbus,0,1,&m0[0]);
        mt->isModbusMain = false;
    }
    mutex_modbus.unlock();
    if(mt->modbus_state == true)
    {
        if(m0[0] == 1)
        {
            if(EStoped == false)
            {
                QImage BkImg1(QApplication::applicationDirPath()+"/ico/stopLogo.png");
                vg->clearPainter();
                vg->setBkImg(BkImg1);
                on_stopBtn_pressed();
                on_stopBtn_released();
                EStoped = true;
            }
        }
        else
        {
           if(EStoped == true)
           {
               QImage BkImg2(QApplication::applicationDirPath()+"/ico/SED_ico.png");
               vg->setBkImg(BkImg2);
               EStoped = false;
           }
        }

         if(m1[0] == 1)
         {
             X1 = 2;
         }
         else
         {
             X1 = 1;
         }

         if(m354[0] == 1)
         {
             overdoseWarn = 1;
         }
         else
         {
             overdoseWarn = 2;
         }
         if(m355[0] == 1)
         {
             Log::Instance()->writeWarn("剔除警告：装瓶过量剔除");
             mutex_modbus.lock();
             modbus_write_bit(mt->modbus,355,false);
             mutex_modbus.unlock();
         }
         //MainWindow::setLED(ui->X1Sig,X1,50);
         //MainWindow::setLED(ui->M354Sig,overdoseWarn,50);
    }

    int cnt = cp->hv_Count;
    int num = cp->singleNum;
    percentage = cnt * 100 / num;
    ui->progressBar->setValue(percentage);

    if(ui->studyBtn->isChecked())
    {
        qDebug() << "studyyyyyyyyyyyy1111111111111111111111";
        if(cp->wStudyRegion.count() > 1100)
        {
            Log::Instance()->writeInfo("已达成条件");
            cp->isStudy = false;
            ui->studyBtn->setText("学习数据");
            ui->saveImgBtn->setEnabled(true);
            //mt->modbus_state = true;
            on_stopBtn_pressed();
            on_stopBtn_released();

            XVRegionStudy();

            ui->studyBtn->setChecked(false);
            learnAreaInArea.data.clear();
            learnAreaInRadius.data.clear();
            cp->wStudyRegion.clear();
            //ui->studyBtn->setChecked(false);
        }
    }
    if(cp->isStudy)
    {
        ui->currentNumBox->setValue(cp->wStudyRegion.count());
    }
    else
    {
        ui->currentNumBox->setValue(cp->hv_Count);
    }
}

void MainWindow::XVRegionStudy()
{
    if(cp->wStudyRegion.count() > 1100){
        qDebug() << "learnnnnnnnnnnnnnnnnnnnnnnnnnnnnn";
        XVRegion region;
        float radius;
        int area;
        for(int i = 0; i<cp->wStudyRegion.count(); i++){
            region = cp->wStudyRegion.at(i);
            area = cp->GetXVRegionArea(region);
            radius = cp->GetXVRegionRadius(region);

            double aadd = static_cast<double>(area);
            learnAreaInArea.data.push_back(aadd);
            learnAreaInRadius.data.push_back(radius);
        }

        qDebug() << learnAreaInArea.data.size();
        int size = learnAreaInArea.data.size();
        for(int i = 0; i < size; ++i){
            qDebug() << learnAreaInArea.data[i];
        }

        grainDataLearn(learnAreaInArea, learnAreaOut);
        if(learnAreaOut.GrainDataLearnResult == 1)
        {
            qDebug() << "successsssssssssssssssssssssssssssssssssssssss";
            qDebug() << learnAreaOut.minThreshold;
            qDebug() << learnAreaOut.maxThreshold;

            set->ui->minArea->setValue((int)learnAreaOut.minThreshold);
            set->ui->maxArea->setValue((int)learnAreaOut.maxThreshold);

            Log::Instance()->writeInfo("学习算法结果面积最大值 = " + QString("%1").arg(learnAreaOut.maxThreshold));
            Log::Instance()->writeInfo("学习算法结果面积最小值 = " + QString("%1").arg(learnAreaOut.minThreshold));
        }
        else
        {
            Log::Instance()->writeWarn("学习数据失败");
        }

        grainDataLearn(learnAreaInRadius, learnAreaOut);
        if(learnAreaOut.GrainDataLearnResult == 1)
        {
            set->ui->minRadius->setValue((int)learnAreaOut.minThreshold);
            set->ui->maxRadius->setValue((int)learnAreaOut.maxThreshold);
            qDebug() << learnAreaOut.minThreshold;
            qDebug() << learnAreaOut.maxThreshold;
            Log::Instance()->writeInfo("学习算法结果半径最大值 = " + QString("%1").arg(learnAreaOut.minThreshold));
            Log::Instance()->writeInfo("学习算法结果半径最小值 = " + QString("%1").arg(learnAreaOut.maxThreshold));
            Log::Instance()->writeInfo("***********学习成功***********");
        }
        else
        {
            Log::Instance()->writeWarn("学习数据失败");
        }
    }
    else
    {
        Log::Instance()->writeWarn("学习数据失败, 数据量太少");
    }
}

void MainWindow::on_clearBtn_clicked()
{
    cp->hv_Count = 0;
    ui->currentNumBox->setValue(0);
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusCount == false)
    {
        cp->isModbusMain = true;
        modbus_write_register(mt->modbus, cp->currentNumAddr, 0);
        cp->isModbusMain = false;
        seriesBS->clear();
        seriesCS->clear();
        cp->seY = 0;
    }
    mutex_modbus.unlock();
}

void MainWindow::on_saveImgBtn_toggled(bool)
{
    if(ui->saveImgBtn->isChecked())
    {
        cp->isSaveImage = true;
        ui->saveImgBtn->setText("结束保存");
        ui->studyBtn->setEnabled(false);
    }
    else
    {
        cp->isSaveImage = false;
        ui->saveImgBtn->setText("保存图片");
        ui->studyBtn->setEnabled(true);
    }
}

void MainWindow::on_studyBtn_toggled(bool)
{
    qDebug() << "studyyyyyyyyyyyy";
    if(ui->studyBtn->isChecked())
    {
        qDebug() << "aaaaaaaaaaaaaaaaaaaaaaaa";
        cp->isStudy = true;
        cp->hv_Count = 0;
        ui->studyBtn->setText("停止学习");
        ui->saveImgBtn->setEnabled(false);
//        on_startBtn_pressed();
//        on_startBtn_released();
        //mt->modbus_state = false;
    }
    else
    {
        qDebug() << "bbbbbbbbbbbbbbbbbbbbbbbbbbbb";
        cp->isStudy = false;
        ui->studyBtn->setText("学习数据");
        ui->saveImgBtn->setEnabled(true);
        //mt->modbus_state = true;
    }
}

//显示图片
void MainWindow::ShowImage()
{
    new std::thread([&](void *ptr)
    {//qDebug()<<QThread::currentThreadId();
        while(true)
        {
            if(ui->start->isChecked())
            {
                QImage qImage;
                if(dcam->isCameraConnect /*&& dcam->isImageQueue*/ && cp->grabSignal2 && cp->grabSignal1)
                {
                    cp->cnt = 0;
                    qImage = cp->showImage;
                    emit signal_showImage(qImage);
                }
            }
            Sleep(40);
        }
    }, this);
}

void MainWindow::slot_showImage(QImage qImage)
{
    vg->clearPainter();
    vg->setBkImg(qImage);
    vg->setViewSize_Fit();

    int channelWidth = qImage.width()/8;

    vg->addLine(QLine(0,qImage.height() / 2, qImage.width(),qImage.height() / 2),false,true,QColor(105,105,105), QColor(105,105,105));

    for(int i=1; i<8; i++)
    {
        vg->addLine(QLine(channelWidth*i, 0, channelWidth*i, qImage.height()+10), false, true, QColor(105,105,105), QColor(105,105,105));
    }
    cp->grabSignal1 = false;
}

void MainWindow::saveImageO()
{
    new std::thread([&](void *ptr)
    {
        while(true)
        {
            if(!cp->wImage.isEmpty())
            {   qDebug()<<"wImage.count "<<cp->wImage.count();
                //QImage oImage = cp->wOImage.dequeue();
                QImage oImage;    // = cp->HImageToQImage(cp->wImage.dequeue());
                //QImage rImage = drawResultImage(oImage, "save");
                SaveImage *saveRunnable = new SaveImage();
                saveRunnable->init(oImage, "ResultImage", set->ui->treeWidget->currentItem()->text(0),
                                   set->ui->minArea->value(), set->ui->maxArea->value(),
                                   set->ui->minRadius->value(), set->ui->maxRadius->value());
                saveRunnable->setAutoDelete(true);
                saveImgPool->start(saveRunnable);
                qDebug()<<"currentThreadNum: "<<saveImgPool->activeThreadCount();
            }
            Sleep(10);
        }
    }, this);
}

void SaveImage::run()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    QImage rImage = drawResultImage(qImage, "save");
    QString savePath1 = savePath + "/" + date.toString("yyyy_MM_dd") + "/"
                        + currentMode;
    //qDebug()<<savePath1;
    QDir savedir(savePath1);
    if(!savedir.exists())
    {
        qDebug()<<QDir().mkpath(savePath1);
    }

    QString saveName = savePath1 + "/" + time.toString("hh_mm_ss_zzz") + ".BMP";
    if(!rImage.save(saveName, "BMP", -1))
    {
        qDebug()<<"保存图片失败";
        //logBar->logDisplay("警告", "保存图片失败", true, true);
        Log::Instance()->writeWarn("保存图片失败");
    }
    if(isErrorImage)
    {
        QString savepath2 = "ErrorImage";
        QString savePath1 = savepath2 + "/" + date.toString("yyyy_MM_dd") + "/"
                            + currentMode;
        //qDebug()<<savePath1;
        QDir savedir(savePath1);
        if(!savedir.exists())
        {
            qDebug()<<QDir().mkpath(savePath1);
        }

        QString saveName = savePath1 + "/" + time.toString("hh_mm_ss_zzz") + ".BMP";
        if(!rImage.save(saveName, "BMP", -1))
        {
            qDebug()<<"保存图片失败";
            Log::Instance()->writeError("保存图片失败");
            logBar->logDisplay("警告", "保存图片失败", true, true);
            Log::Instance()->writeWarn("保存图片失败");
        }
    }
    qDebug()<<"currentThreadId "<<QThread::currentThreadId();
    //Sleep(0);
}

QImage SaveImage::drawResultImage(QImage qImg, QString showOrSave)
{
    QPainter p;
    p.begin(&qImg);
    QFont f;
    f.setPixelSize(30);
    f.setBold(true);
    f.setFamily("微软雅黑");
    p.setFont(f);

    int sortRegionNum, sortRegionNumS;
    HObject dSortRegion, dSortRegionS;
    int currentCount;

    if(showOrSave == "show")
    {
        currentCount = cp->wCount.last();
        sortRegionNum = cp->wSortRegionNum.last();
        for (int i = 0; i < sortRegionNum; i++)
        {
            ;
        }
    }
    else if(showOrSave == "save")
    {
        currentCount = cp->wCount.dequeue();
        sortRegionNumS = cp->wSortRegionNumS.dequeue();
        for (int i = 0; i < sortRegionNumS; i++)
        {
            dSortRegionS = cp->wSortRegionS.dequeue();
            RegionFeatures(dSortRegionS, "area", &ho_AreaS);
            RegionFeatures(dSortRegionS, "outer_radius", &ho_RadiusS);
            wArea.append(ho_AreaS.D());
            wRadius.append(ho_RadiusS.D());

            SmallestRectangle1(dSortRegionS, &hv_Row4, &hv_Column4, &hv_Row5, &hv_Column5);

            GenRectangle1(&ho_Rectangle, hv_Row4, hv_Column4, hv_Row5, hv_Column5);

            if((ho_AreaS < minAreaSet|| ho_AreaS > maxAreaSet) || (ho_RadiusS < minRadiusSet || ho_RadiusS > maxRadiusSet))
            {
                p.setPen(QPen(Qt::red, 2));
            }
            else
            {
                p.setPen(QPen(Qt::green, 2));
            }
            p.drawRect(QRect(QPoint(hv_Column4.D(), hv_Row4.D()),
                             QPoint(hv_Column5.D(), hv_Row5.D())));
        }
    }
    p.setPen(QPen(Qt::red, 2));

    double minArea, maxArea, minRadius, maxRadius;
    minArea = 100000000; maxArea = 0; minRadius = 100000000; maxRadius = 0;
    for(int i = 0; i < wArea.count(); i++)
    {
        if(wArea.at(i) < minArea)
        {
            minArea = wArea.at(i);
        }
        if(wArea.at(i) > maxArea)
        {
            maxArea = wArea.at(i);
        }

        if(wRadius.at(i) < minRadius)
        {
            minRadius = wRadius.at(i);
        }
        if(wRadius.at(i) > maxRadius)
        {
            maxRadius = wRadius.at(i);
        }
    }

    if(minArea == 100000000)
    {
        minArea = 0;
    }
    if(minRadius == 100000000)
    {
        minRadius = 0;
    }

    wArea.clear();
    wRadius.clear();

    p.drawText(QPointF(0, 50), "面积:  最小 " + QString::number(minArea) + "(" + QString::number(minAreaSet) + ")"
                                  + "  最大 " + QString::number(maxArea) + "(" + QString::number(maxAreaSet) + ")");
    p.drawText(QPointF(0, 100), "半径:  最小 " + QString::number(minRadius) + "(" + QString::number(minRadiusSet) + ")"
                                   + "  最大 " + QString::number(maxRadius) + "(" + QString::number(maxRadiusSet) + ")");
    p.drawText(QPointF(qImg.width()-300, 50), "当前数量： " + QString::number(currentCount));
    p.end();

    if(((minArea < minAreaSet || maxArea > maxAreaSet) && (minArea != 0 && maxAreaSet != 0)) || ((minRadius < minRadiusSet || maxRadius > maxRadiusSet) &&  (minRadius != 0 && maxRadius != 0)))
    {
        isErrorImage = true;
    }
    else
    {
        isErrorImage = false;
    }
    return qImg;
}

//工具栏初始化
void MainWindow::toolBarInit()
{
    ui->login->setChecked(false);
    ui->login->setText("用户登入");
    ui->mainInterfaceAction->setEnabled(true);
    ui->mainInterfaceAction->setChecked(true);
    ui->setInterfaceAction->setEnabled(false);
    ui->imageInterfaceAction->setEnabled(false);
    ui->start->setChecked(true);
}


//用户登录界面
void MainWindow::on_login_toggled(bool arg1)
{

    if(ui->login->isChecked())
    {
        QString name = findTranslation("login");
        ui->login->setText(name);
        loginWindow->setWindowModality(Qt::WindowModal);
        loginWindow->setWindowFlag(Qt::WindowMinMaxButtonsHint);
        loginWindow->show();
    }

    if(!ui->login->isChecked())
    {
        QString name = findTranslation("logout");
        ui->login->setText(name);
        ui->setInterfaceAction->setEnabled(false);
        ui->imageInterfaceAction->setEnabled(false);
        Log::Instance()->writeInfo("用户已退出登录");
    }
}

//登录界面确定
void MainWindow::loginBtn()
{
    if(loginWindow->ui->code_lineEdit->text() == "1234567")
    {
        ui->setInterfaceAction->setEnabled(true);
        ui->imageInterfaceAction->setEnabled(true);
        Log::Instance()->writeInfo("用户已登录");
        loginWindow->close();
    }
    else
    {
        Log::Instance()->writeInfo("密码错误");
    }
}

//登录界面取消
void MainWindow::loginCancelBtn()
{
    loginWindow->close();
}

//登录界面关闭
void MainWindow::loginClose()
{
    if(loginWindow->ui->code_lineEdit->text() != "1234567")
    {
        ui->login->setChecked(false);
    }

    loginWindow->ui->code_lineEdit->clear();
}

//主界面
void MainWindow::on_mainInterfaceAction_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->start->setChecked(true);

    if(set->ui->beltBtn->isChecked())
    {
        set->ui->beltBtn->setChecked(false);
        set->on_beltBtn_toggled(false);
    }

    if(set->ui->blockBtn->isChecked())
    {
        set->ui->blockBtn->setChecked(false);
        set->on_blockBtn_toggled(false);
    }

    if(set->ui->bufferBtn->isChecked())
    {
        set->ui->bufferBtn->setChecked(false);
        set->on_bufferBtn_toggled(false);
    }

    if(set->ui->funnelBtn->isChecked())
    {
        set->ui->funnelBtn->setChecked(false);
        set->on_funnelBtn_toggled(false);
    }

    if(set->ui->removeBtn->isChecked())
    {
        set->ui->removeBtn->setChecked(false);
        set->on_removeBtn_toggled(false);
    }

    if(set->ui->shackerBtn->isChecked())
    {
        set->ui->shackerBtn->setChecked(false);
        set->on_shackerBtn_toggled(false);
    }

    if(set->ui->bufferBtn_1->isChecked())
    {
        set->ui->bufferBtn_1->setChecked(false);
        set->on_bufferBtn_1_toggled(false);
    }
    if(set->ui->bufferBtn_2->isChecked())
    {
        set->ui->bufferBtn_2->setChecked(false);
        set->on_bufferBtn_2_toggled(false);
    }
    if(set->ui->bufferBtn_3->isChecked())
    {
        set->ui->bufferBtn_3->setChecked(false);
        set->on_bufferBtn_3_toggled(false);
    }
    if(set->ui->bufferBtn_4->isChecked())
    {
        set->ui->bufferBtn_4->setChecked(false);
        set->on_bufferBtn_4_toggled(false);
    }
    if(set->ui->bufferBtn_5->isChecked())
    {
        set->ui->bufferBtn_5->setChecked(false);
        set->on_bufferBtn_5_toggled(false);
    }
    if(set->ui->bufferBtn_6->isChecked())
    {
        set->ui->bufferBtn_6->setChecked(false);
        set->on_bufferBtn_6_toggled(false);
    }
    if(set->ui->bufferBtn_7->isChecked())
    {
        set->ui->bufferBtn_7->setChecked(false);
        set->on_bufferBtn_7_toggled(false);
    }
    if(set->ui->bufferBtn_8->isChecked())
    {
        set->ui->bufferBtn_8->setChecked(false);
        set->on_bufferBtn_8_toggled(false);
    }
}

//设置界面
void MainWindow::on_setInterfaceAction_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);

    if(set->ui->tabWidget->currentIndex()==2)
    {
        HandModeStop();
    }
    //ui->start->setChecked(false);
}

//图片界面
void MainWindow::on_imageInterfaceAction_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->start->setChecked(false);

    QDate date = QDate::currentDate();

    QString toSavePath = QApplication::applicationDirPath() + "/ErrorImage/" + date.toString("yyyy_MM_dd") + "/"+ set->ui->treeWidget->currentItem()->text(0);

    qDebug()<<"toSavePath = " << toSavePath << endl;

    view->ui->imgPathEdit->setText(toSavePath);

    view->imgNum = 0;
    view->nextImg = true;

    view->fileFetch();

    view->vgView->setViewSize_Fit();

}

//开始按钮
void MainWindow::on_start_toggled(bool arg1)
{
    if(ui->start->isChecked())
    {
        QString str = findTranslation("stop");
        ui->start->setText(str);
        if(!set->countThread->isRunning())
        {
            cp->countThreadSignal = true;
            set->countThread->start();
            dcam->isImageQueue = true;
        }
    }

    if(!ui->start->isChecked())
    {
        QString str = findTranslation("start");
        ui->start->setText(str);

        if(set->countThread->isRunning())
        {
            dcam->isImageQueue = false;
            cp->countThreadSignal = false;
            set->countThread->quit();
            set->countThread->wait();

            on_stopBtn_pressed();
            on_stopBtn_released();
        }

    }
}

void MainWindow::dev_open_window_fit_image (HObject ho_Image, HTuple hv_Row, HTuple hv_Column,
    HTuple hv_WidthLimit, HTuple hv_HeightLimit, HTuple *hv_WindowHandle)
{

    // Local iconic variables
    // Local control variables
    HTuple  hv_MinWidth, hv_MaxWidth, hv_MinHeight;
    HTuple  hv_MaxHeight, hv_ResizeFactor, hv_ImageWidth, hv_ImageHeight;
    HTuple  hv_TempWidth, hv_TempHeight, hv_WindowWidth, hv_WindowHeight;

    //This procedure opens a new graphics window and adjusts the size
    //such that it fits into the limits specified by WidthLimit
    //and HeightLimit, but also maintains the correct image aspect ratio.
    //
    //If it is impossible to match the minimum and maximum extent requirements
    //at the same time (f.e. if the image is very long but narrow),
    //the maximum value gets a higher priority,
    //
    //Parse input tuple WidthLimit
    if (0 != (HTuple((hv_WidthLimit.TupleLength())==0).TupleOr(hv_WidthLimit<0)))
    {
        hv_MinWidth = 500;
        hv_MaxWidth = 800;
    }
    else if (0 != ((hv_WidthLimit.TupleLength())==1))
    {
        hv_MinWidth = 0;
        hv_MaxWidth = hv_WidthLimit;
    }
    else
    {
        hv_MinWidth = ((const HTuple&)hv_WidthLimit)[0];
        hv_MaxWidth = ((const HTuple&)hv_WidthLimit)[1];
    }
    //Parse input tuple HeightLimit
    if (0 != (HTuple((hv_HeightLimit.TupleLength())==0).TupleOr(hv_HeightLimit<0)))
    {
        hv_MinHeight = 400;
        hv_MaxHeight = 600;
    }
    else if (0 != ((hv_HeightLimit.TupleLength())==1))
    {
        hv_MinHeight = 0;
        hv_MaxHeight = hv_HeightLimit;
    }
    else
    {
        hv_MinHeight = ((const HTuple&)hv_HeightLimit)[0];
        hv_MaxHeight = ((const HTuple&)hv_HeightLimit)[1];
    }
    //
    //Test, if window size has to be changed.
    hv_ResizeFactor = 1;
    GetImageSize(ho_Image, &hv_ImageWidth, &hv_ImageHeight);
    //First, expand window to the minimum extents (if necessary).
    if (0 != (HTuple(hv_MinWidth>hv_ImageWidth).TupleOr(hv_MinHeight>hv_ImageHeight)))
    {
        hv_ResizeFactor = (((hv_MinWidth.TupleReal())/hv_ImageWidth).TupleConcat((hv_MinHeight.TupleReal())/hv_ImageHeight)).TupleMax();
    }
    hv_TempWidth = hv_ImageWidth*hv_ResizeFactor;
    hv_TempHeight = hv_ImageHeight*hv_ResizeFactor;
    //Then, shrink window to maximum extents (if necessary).
    if (0 != (HTuple(hv_MaxWidth<hv_TempWidth).TupleOr(hv_MaxHeight<hv_TempHeight)))
    {
        hv_ResizeFactor = hv_ResizeFactor*((((hv_MaxWidth.TupleReal())/hv_TempWidth).TupleConcat((hv_MaxHeight.TupleReal())/hv_TempHeight)).TupleMin());
    }
    hv_WindowWidth = hv_ImageWidth*hv_ResizeFactor;
    hv_WindowHeight = hv_ImageHeight*hv_ResizeFactor;
    //Resize window
    SetWindowAttr("background_color","black");
    OpenWindow(hv_Row,hv_Column,hv_WindowWidth,hv_WindowHeight,0,"invisible","",&(*hv_WindowHandle));
    HDevWindowStack::Push((*hv_WindowHandle));
    if (HDevWindowStack::IsOpen())
    SetPart(HDevWindowStack::GetActive(),0, 0, hv_ImageHeight-1, hv_ImageWidth-1);
    return;
}


void MainWindow::on_startBtn_pressed()
{//rgb(85, 255, 127)

    QString str = findTranslation("running");
    ui->startBtn->setText(str);
    ui->startBtn->setStyleSheet("QPushButton#startBtn{min-width: 150px;\
                                 min-height: 80px;\
                                 background: rgb(85, 255, 127);\
                                 border-radius: 4px;\
                                 font: 14pt '微软雅黑';}");
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusCount == false){
        mt->isModbusMain = true;
        modbus_write_bit(mt->modbus,300,true);
        mt->isModbusMain = false;
    }
    mutex_modbus.unlock();
}

void MainWindow::LedFlash()
{
    //setLED(ui->X1Sig,3,50);

    FlashTimes++;

    Log::Instance()->writeInfo("FlashTimes = " + QString::number(FlashTimes));
    if(FlashTimes > 5)
    {
        disconnect(LEDFlashTimer, SIGNAL(timeout()), this, SLOT(LEDFlash()));
        LEDFlashTimer->stop();
        FlashTimes = 0;
    }
}

void MainWindow::on_startBtn_released()
{//rgb(85, 255, 0)

    ui->startBtn->setStyleSheet("QPushButton#startBtn{\
                                min-width: 150px;\
                                min-height: 80px;\
                                background:rgb(255, 165, 0);\
                                border-radius: 4px;\
                                font: 14pt '微软雅黑';}");
    ui->clearBufferBtn->setStyleSheet("QPushButton#clearBufferBtn{\
                                      min-width: 150px;\
                                      min-height: 80px;\
                                      background:rgb(180, 180, 180);\
                                      border-radius: 4px;\
                                      font: 14pt '微软雅黑';}");
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        modbus_write_bit(mt->modbus,300,false);
        mt->isModbusMain = false;

        workingState = true;
        ui->startBtn->setEnabled(false);
    }
    mutex_modbus.unlock();
}

void MainWindow::on_stopBtn_pressed()
{
    QString str = findTranslation("startUp");
    ui->startBtn->setText(str);

    ui->stopBtn->setStyleSheet("QPushButton#stopBtn{\
                                min-width: 150px;\
                                min-height: 80px;\
                                background:rgb(255, 0, 127);\
                                border-radius: 4px;\
                                font: 14pt '微软雅黑';}");
    ui->startBtn->setStyleSheet("QPushButton#startBtn{\
                                min-width: 150px;\
                                min-height: 80px;\
                                background:rgb(85, 255, 0);\
                                border-radius: 4px;\
                                font: 14pt '微软雅黑';}");
    ui->clearBufferBtn->setStyleSheet("QPushButton#clearBufferBtn{\
                                min-width: 150px;\
                                min-height: 80px;\
                                background:rgb(255, 255, 0);\
                                border-radius: 4px;\
                                font: 14pt '微软雅黑';}");

    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        modbus_write_bit(mt->modbus,302,true);
        modbus_write_bit(mt->modbus,400,true);
        mt->isModbusMain = false;

        ui->startBtn->setEnabled(true);
        workingState = false;
    }
    mutex_modbus.unlock();
}

void MainWindow::on_stopBtn_released()
{
    ui->stopBtn->setStyleSheet("QPushButton#stopBtn{\
                                min-width: 150px;\
                                min-height: 80px;\
                                background:rgb(255, 0, 0);\
                                border-radius: 4px;\
                                font: 14pt '微软雅黑';}");
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        modbus_write_bit(mt->modbus,302,false);
        modbus_write_bit(mt->modbus,400,false);
        mt->isModbusMain = false;

        workingState = false;
    }
    mutex_modbus.unlock();
}

void MainWindow::on_resetBtn_pressed()
{
    //ui->stopBtn->setStyleSheet("background: #D6D5B7");

    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
         mt->isModbusMain = true;
         modbus_write_bit(mt->modbus,400,true);
         mt->isModbusMain = false;

    }
    mutex_modbus.unlock();
}
void MainWindow::on_resetBtn_released()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
         mt->isModbusMain = true;
         modbus_write_bit(mt->modbus,400,false);
         mt->isModbusMain = false;
    }
    mutex_modbus.unlock();
}


void MainWindow::on_FullScreen_toggled(bool arg1)
{
;
}

void MainWindow::on_Exit_triggered()
{
    on_stopBtn_pressed();
    on_startBtn_released();

    QApplication* app;
    app->quit();
}
void MainWindow::ExitProgram()
{
    on_Exit_triggered();
}


void MainWindow::on_clearBottleBtn_pressed()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        modbus_write_bit(mt->modbus,28,true);
        mt->isModbusMain = false;
    }
    mutex_modbus.unlock();
}

void MainWindow::on_clearBottleBtn_released()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        modbus_write_bit(mt->modbus,28,false);
        mt->isModbusMain = false;
    }
    mutex_modbus.unlock();
}

void MainWindow::on_beltPowerBtn_toggled(bool checked)
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        if( ui->beltPowerBtn->isChecked())
        {
            modbus_write_bit(mt->modbus,10,true);
        }
        else
        {
            modbus_write_bit(mt->modbus,10,false);
        }
        mt->isModbusMain = false;
    }
    mutex_modbus.unlock();
}

void MainWindow::on_clearBufferBtn_pressed()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        if(workingState == true)
        {
            Log::Instance()->writeInfo("清瓶前请先复位");
        }
        else
        {
            cp->hv_Count = 0;
            ui->currentNumBox->setValue(0);
           mt->isModbusMain = true;
           modbus_write_bit(mt->modbus,9,true);
           cp->isModbusMain = true;
           modbus_write_register(mt->modbus, cp->currentNumAddr, 0);
           cp->isModbusMain = false;
           seriesBS->clear();
           seriesCS->clear();
           cp->seY = 0;
           mt->isModbusMain = false;
        }
    }
    mutex_modbus.unlock();
}

void MainWindow::on_clearBufferBtn_released()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        modbus_write_bit(mt->modbus,9,false);
        mt->isModbusMain = false;
    }
    mutex_modbus.unlock();
}

void MainWindow::on_shaker1Add_clicked()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        int val = set->ui->shaker1VBox->value() + 1;
        set->ui->shaker1VBox->setValue(val);
        //set->on_shaker1VBox_editingFinished();
        modbus_write_register(mt->modbus,HD + 100,val);
        ui->Shaker1VBox->setValue(set->ui->shaker1VBox->value());
        mt->isModbusMain = false;
    }
    mutex_modbus.unlock();
}

void MainWindow::on_shaker1Dec_clicked()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        int val = set->ui->shaker1VBox->value() - 1;
        set->ui->shaker1VBox->setValue(val);
        //set->on_shaker1VBox_editingFinished();
        modbus_write_register(mt->modbus,HD + 100,val);
        ui->Shaker1VBox->setValue(set->ui->shaker1VBox->value());
        mt->isModbusMain = false;
    }
    mutex_modbus.unlock();
}

void MainWindow::on_shaker2Add_clicked()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        int val = set->ui->shaker2VBox->value() + 1;
        set->ui->shaker2VBox->setValue(val);
        //set->on_shaker2VBox_editingFinished();
        modbus_write_register(mt->modbus,HD + 104,val);
        ui->Shaker2VBox->setValue(set->ui->shaker2VBox->value());
        mt->isModbusMain = false;
    }
    mutex_modbus.unlock();
}

void MainWindow::on_shaker2Dec_clicked()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        int val = set->ui->shaker2VBox->value() - 1;
        set->ui->shaker2VBox->setValue(val);
        //set->on_shaker2VBox_editingFinished();
        modbus_write_register(mt->modbus,HD + 104,val);
        ui->Shaker2VBox->setValue(set->ui->shaker2VBox->value());
        mt->isModbusMain = false;
    }
    mutex_modbus.unlock();
}

void MainWindow::on_shaker3Add_clicked()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        int val = set->ui->shaker3VBox->value() + 1;
        set->ui->shaker3VBox->setValue(val);
        //set->on_shaker3VBox_editingFinished();
        modbus_write_register(mt->modbus,HD + 102,val);
        ui->Shaker3VBox->setValue(set->ui->shaker3VBox->value());
        mt->isModbusMain = false;
    }
    mutex_modbus.unlock();
}

void MainWindow::on_shaker3Dec_clicked()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        int val = set->ui->shaker3VBox->value() - 1;
        set->ui->shaker3VBox->setValue(val);
        //set->on_shaker3VBox_editingFinished();
        modbus_write_register(mt->modbus,HD + 102,val);
        ui->Shaker3VBox->setValue(set->ui->shaker3VBox->value());
        mt->isModbusMain = false;
    }
    mutex_modbus.unlock();
}

void MainWindow::ChangeShaker1VText()
{
    ui->Shaker1VBox->setValue(set->ui->shaker1VBox->value());
}

void MainWindow::ChangeShaker2VText()
{
    ui->Shaker2VBox->setValue(set->ui->shaker2VBox->value());
}
void MainWindow::ChangeShaker3VText()
{
    ui->Shaker3VBox->setValue(set->ui->shaker3VBox->value());
}
void MainWindow::HandModeStop()
{
    on_stopBtn_pressed();
    on_stopBtn_released();
}

void MainWindow::on_singleNumBox_editingFinished()
{
    set->ui->singleButtleQuantity->setValue(ui->singleNumBox->value());
    cp->singleNum = ui->singleNumBox->value();
    mutex_modbus.lock();
    if(mt->modbus_state == true)
    {
        modbus_write_register(mt->modbus, set->ui->singleNumAddr->value(), ui->singleNumBox->value());
    }
    mutex_modbus.unlock();
}
void MainWindow::on_Shaker1VBox_editingFinished()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        set->ui->shaker1VBox->setValue(ui->Shaker1VBox->value());
        modbus_write_register(mt->modbus,HD + 100,ui->Shaker1VBox->value());
        mt->isModbusMain = false;
    }
    mutex_modbus.unlock();
}
void MainWindow::on_Shaker2VBox_editingFinished()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        set->ui->shaker2VBox->setValue(ui->Shaker2VBox->value());
        modbus_write_register(mt->modbus,HD + 104,ui->Shaker2VBox->value());
        mt->isModbusMain = false;
    }
    mutex_modbus.unlock();
}
void MainWindow::on_Shaker3VBox_editingFinished()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false && mt->isModbusCount == false)
    {
        mt->isModbusMain = true;
        set->ui->shaker3VBox->setValue(ui->Shaker3VBox->value());
        modbus_write_register(mt->modbus,HD + 102,ui->Shaker3VBox->value());
        mt->isModbusMain = false;
    }
    mutex_modbus.unlock();
}
void MainWindow::SingleNumBoxChanged()
{
    ui->singleNumBox->setValue(set->ui->singleButtleQuantity->value());
    //Log::Instance()->writeInfo("set->ui->singleButtleQuantity->value() = " + QString::number(set->ui->singleButtleQuantity->value()));
}
