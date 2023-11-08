#include "settingwidget.h"
#include "ui_settingwidget.h"
#include "modbust.h"
#include "mainwindow.h"
#include "tinyxml2.h"

CountProcess *cp;

#define HD 41088

SettingWidget::SettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
    configInit();

    cp = new CountProcess(ui);
    countThread = new QThread(this);
    connect(countThread, SIGNAL(started()), cp, SLOT(count()));
    cp->moveToThread(countThread);
    countThread->setPriority(QThread::HighestPriority);

    isFirst = true;
    on_loadBtn_clicked();
    isFirst = false;
    QTimer *cleanTime = new QTimer(this);
    connect(cleanTime, SIGNAL(timeout()), this, SLOT(cleanUpImage()));
    //cleanUpImage();
    cleanTime->start(100);

    //ui->cutTimeBox->setSpecialValueText("--ms");
    ui->cutTimeBox->SetUnitText("ms",14);
    //ui->blockTwoBox->setSpecialValueText("--ms");
    ui->blockTwoBox->SetUnitText("ms",14);
    //ui->loadTimeBox->setSpecialValueText("--ms");
    ui->loadTimeBox->SetUnitText("ms",14);
    //ui->bufferTimeBox->setSpecialValueText("--ms");
    ui->bufferTimeBox->SetUnitText("ms",14);
    //ui->fallTimeBox->setSpecialValueText("--ms");
    ui->fallTimeBox->SetUnitText("ms",14);
    //ui->removeOutBox->setSpecialValueText("--ms");
    ui->removeOutBox->SetUnitText("ms",14);
    //ui->removeBackBox->setSpecialValueText("--ms");
    ui->removeBackBox->SetUnitText("ms",14);
    //ui->shaker1VBox->setSpecialValueText("--V");
    ui->shaker1VBox->SetUnitText("V",14);
    //ui->shaker2VBox->setSpecialValueText("--V");
    ui->shaker2VBox->SetUnitText("V",14);
    //ui->shaker3VBox->setSpecialValueText("--V");
    ui->shaker3VBox->SetUnitText("V",14);
    //ui->shaker1HzBox->setSpecialValueText("--Hz");
    ui->shaker1HzBox->SetUnitText("Hz",14);
    //ui->shaker2HzBox->setSpecialValueText("--Hz");
    ui->shaker2HzBox->SetUnitText("Hz",14);
    //ui->shaker3HzBox->setSpecialValueText("--Hz");
    ui->shaker3HzBox->SetUnitText("Hz",14);
    //ui->stopRateBox->setSpecialValueText("--%");
    ui->stopRateBox->SetUnitText("%",14);
    //ui->shakeTimeBox->setSpecialValueText("--ms");
    ui->shakeTimeBox->SetUnitText("ms",14);
    /////通讯参数单位设置/////
    //ui->minArea->setSpecialValueText("--px");
    ui->minArea->SetUnitText("Pixel",14);
    //ui->maxArea->setSpecialValueText("--px");
    ui->maxArea->SetUnitText("Pixel",14);
    //ui->minRadius->setSpecialValueText("--px");
    ui->minRadius->SetUnitText("Pixel",14);
    //ui->maxRadius->setSpecialValueText("--px");
    ui->maxRadius->SetUnitText("Pixel",14);
    //
    //ui->flawAreaMax->setSpecialValueText("--px");
    ui->flawAreaMax->SetUnitText("Pixel",14);
    //ui->flawAreaMin->setSpecialValueText("--px");
    ui->flawAreaMin->SetUnitText("Pixel",14);
    //ui->flawRadiusMax->setSpecialValueText("--px");
    ui->flawRadiusMax->SetUnitText("Pixel",14);
    //ui->flawRadiusMin->setSpecialValueText("--px");
    ui->flawRadiusMin->SetUnitText("Pixel",14);

}

SettingWidget::~SettingWidget()
{
    delete ui;
    if(countThread->isRunning())
    {
        cp->countThreadSignal = false;
        countThread->quit();
        countThread->wait();
    }
}

/**
 * @brief 定时清理图片文件夹
 * @param path  保存图片文件夹路径
 */
void SettingWidget::cleanUpImage()
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    QString savePath;
    for (int i = 0; i < 2; i++)
    {
        if(i == 0)
        {
            savePath = "ResultImage";
        }
        if(i == 1)
        {
            savePath = "ErrorImage";
        }

        QString savePath1 = savePath + "/" + date.toString("yyyy_MM_dd") + "/"
                            + ui->treeWidget->currentItem()->text(0);
        QDir dir(savePath1);
        //qDebug()<<savePath1;
        if(!dir.exists())
        {
            return;
        }
        QFileInfoList infolist = dir.entryInfoList(QDir::Files|QDir::NoDotAndDotDot);
        //qDebug()<<"infolist.count() "<<infolist.count();
        if(infolist.count()-ui->saveImgDays->text().toInt()>0)
        {
            for(int i=0;i<infolist.count()-ui->saveImgDays->text().toInt();i++)
            {
    //            QFileInfo fileInfo(infolist.at(i));
    //            QDir savePath(infolist.at(i).absoluteFilePath());
                QString fileName = infolist.at(i).absoluteFilePath();
                //qDebug()<<"filename "<<fileName;
    //            QDateTime date = QDateTime::currentDateTime().addDays(-ui->saveImgDays->text().toInt());
    //            savePath.removeRecursively();
                remove(fileName.toLatin1().data());
            }
        }

    }

}

/**********配方加载、新建、保存、删除**********/

//配方界面初始化
void SettingWidget::configInit()
{
    //配方界面初始化
    ui->peiFang->setHidden(false);

    //获取配置文件夹下所有文件名
    QDir dir(QApplication::applicationDirPath() + "/Config");

    QStringList filter;
    filter<<QString("*");
    dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
    dir.setNameFilters(filter);  //设置文件名称过滤器，只为filters格式

    int dir_count = dir.count();
    if(dir_count <= 0)
    {
        return;
    }

    for(int i=0; i<dir_count; i++)
    {
        QString filename = dir[i];  //文件名称
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
        item->setText(0, filename);
        ui->treeWidget->addTopLevelItem(item);
    }

    /*加载上一次配置*/
    QString filename = QApplication::applicationDirPath() + "/system";
    QSettings *iniRead = new QSettings(filename, QSettings::IniFormat);
    QString lastpath = QApplication::applicationDirPath() + iniRead->value("LastConfigPath").toString();

    qDebug() << "lastpath = "<<lastpath << endl;


    int item_count = ui->treeWidget->topLevelItemCount();

    qDebug() << "item_count = " << item_count <<endl;

    for(int i = 0; i <  item_count; i++)
    {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        QString item_text = QApplication::applicationDirPath() + "/Config" + "/" + item->text(0);

        qDebug() << "item_text = " << item_text << endl;

        //qDebug() << "lastPath = " << lastpath <<endl;

        if(item_text == lastpath)
        {
            ui->treeWidget->setCurrentItem(item);
            qDebug() << "LastConfig查找完成" << endl;
            readConfig(lastpath);
            qDebug() << "ConfigReadOver" << endl;
        }

        //if(item->text(0) == "system")
        //{
        //    delete item;
        //}
    }
    qDebug() <<"ConfigINI完成"<<endl;
}

//加载配方
void SettingWidget::on_loadBtn_clicked()
{
    if(ui->treeWidget->currentItem()->text(0) == "")
    {
        return;
    }
    QString filename = QApplication::applicationDirPath() + "/Config" + "/" + ui->treeWidget->currentItem()->text(0);
    readConfig(filename);

    QString filename_lastConfig = QApplication::applicationDirPath() + "/system";
    QSettings *iniWrite_LC = new QSettings(filename_lastConfig, QSettings::IniFormat);
    iniWrite_LC->setValue("LastConfigPath", QString("/Config/" + ui->treeWidget->currentItem()->text(0)));

    //QString lastpath = QApplication::applicationDirPath() + iniRead->value("LastConfigPath").toString();

   //on_expousetime_editingFinished();
   //
   //on_gainRaw_editingFinished();
   //
   //on_lineRate_editingFinished();

   on_ipAddress_editingFinished();

   on_singleButtleQuantity_editingFinished();

   on_preProcessCombox_currentIndexChanged(0);

   on_operatorSize_editingFinished();

   on_minThreshold_editingFinished();

   on_maxThreshold_editingFinished();

   on_minArea_editingFinished();

   on_maxArea_editingFinished();

   on_minRadius_editingFinished();

   on_maxRadius_editingFinished();

   on_minFill_editingFinished();

   on_maxFill_editingFinished();

    qDebug() << "算法参数写入成功_1" << endl;

    on_flawAreaMin_editingFinished();

    on_flawAreaMax_editingFinished();

    on_flawRadiusMin_editingFinished();

    on_flawRadiusMax_editingFinished();

    qDebug() << "算法参数写入成功_2" << endl;

    ///////Modbus通讯写入/////////

    on_cutTimeBox_editingFinished();

    on_fallTimeBox_editingFinished();

    on_bufferTimeBox_editingFinished();

    //on_switchTimeBox_editingFinished();

    on_removeOutBox_editingFinished();

    on_removeBackBox_editingFinished();

    on_shaker1VBox_editingFinished();

    on_shaker2VBox_editingFinished();

    on_shaker3VBox_editingFinished();

    on_shaker1HzBox_editingFinished();

    on_shaker2HzBox_editingFinished();

    on_shaker3HzBox_editingFinished();

    qDebug() << "电气参数写入成功" << endl;
    ////////Modbus通讯写入结束/////////

    on_currentNumAddr_editingFinished();

    on_singleNumAddr_editingFinished();

    on_insertCoordXAddr_editingFinished();

    on_insertCoordYAddr_editingFinished();

    on_fullSignalAddr_editingFinished();

    //on_flawSignalAddr_editingFinished();

    on_setRuntime_editingFinished();

    //on_saveImgPath_textChanged();

    on_saveImgDays_editingFinished();

    on_cutTimeBox_editingFinished();

    on_fallTimeBox_editingFinished();

    //on_blockTimeBox_editingFinished();

    on_loadTimeBox_editingFinished();

    on_stopRateBox_editingFinished();

    on_shakeTimeBox_editingFinished();

    on_blockTwoBox_editingFinished();

    on_restWarnBox_editingFinished();



    emit Shaker1VBoxChanged();
    emit Shaker2VBoxChanged();
    emit Shaker3VBoxChanged();
    emit SingleNumBoxChanged_Sig();
    //Log::Instance()->writeInfo("SingleNumBoxChanged_Siganl 已发送");

    //ui->curRecipe->setText("当前型号：" + ui->treeWidget->currentItem()->text(0));
    cp->currentMode = ui->treeWidget->currentItem()->text(0);
    logBar->logDisplay("消息", ui->treeWidget->currentItem()->text(0) + "加载成功", true, false);
    Log::Instance()->writeInfo(ui->treeWidget->currentItem()->text(0) + "配方加载成功");
}

//新建配方
void SettingWidget::on_newBtn_clicked()
{
    if(ui->lineEdit->text() == "")
    {
        Log::Instance()->writeWarn("非法配方名称");
        return;
    }
    QString filename = QApplication::applicationDirPath() + "/Config" + "/" + ui->lineEdit->text();
    writeConfig(filename);

    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
    item->setText(0, ui->lineEdit->text());
    ui->treeWidget->addTopLevelItem(item);
    ui->treeWidget->setCurrentItem(item);
    Log::Instance()->writeInfo("新建配方：" + ui->lineEdit->text());

}

//保存配方
void SettingWidget::on_saveBtn_clicked()
{
    QString filename = QApplication::applicationDirPath() + "/Config" + "/" + ui->treeWidget->currentItem()->text(0);
    writeConfig(filename);
    Log::Instance()->writeInfo("配置已保存到" + ui->treeWidget->currentItem()->text(0));
}

//删除配方
void SettingWidget::on_delBtn_clicked()
{
    //logBar->logDisplay("消息", ui->treeWidget->currentItem()->text(0) + " 配方已删除", true, false);
    Log::Instance()->writeInfo(ui->treeWidget->currentItem()->text(0) + " 配方已删除");

    QString filename = QApplication::applicationDirPath() + "/Config" + "/" + ui->treeWidget->currentItem()->text(0);
    QFile::remove(filename);

    delete ui->treeWidget->currentItem();
}

//写入配置
void SettingWidget::writeConfig(QString filename)
{
    QSettings *iniWrite = new QSettings(filename, QSettings::IniFormat);

    iniWrite->setValue("Recp_name", ui->lineEdit->text());

    //相机参数
    iniWrite->setValue("Camera/Expousetime", ui->expousetime->value());
    iniWrite->setValue("Camera/GainRaw", ui->gainRaw->value());
    iniWrite->setValue("Camera/LineRate", ui->lineRate->value());

    //算法参数
    iniWrite->setValue("Parameter/SingleButtleNum", ui->singleButtleQuantity->value());
    iniWrite->setValue("Parameter/PreProcess", ui->preProcessCombox->currentText());
    iniWrite->setValue("Parameter/OperatorSize", ui->operatorSize->value());
    //iniWrite->setValue("Parameter/ClosingRadius", ui->closingRadius->value());
    iniWrite->setValue("Parameter/MinThreshold", ui->minThreshold->value());
    iniWrite->setValue("Parameter/MaxThreshold", ui->maxThreshold->value());
    iniWrite->setValue("Parameter/MinArea", ui->minArea->value());
    iniWrite->setValue("Parameter/MaxArea", ui->maxArea->value());
    iniWrite->setValue("Parameter/MinRadius", ui->minRadius->value());
    iniWrite->setValue("Parameter/MaxRadius", ui->maxRadius->value());
    iniWrite->setValue("Parameter/MinFill", ui->minFill->value());
    iniWrite->setValue("Parameter/MaxFill", ui->maxFill->value());
    iniWrite->setValue("Parameter/FlawAreaMin", ui->flawAreaMin->value());
    iniWrite->setValue("Parameter/FlawAreaMax", ui->flawAreaMax->value());
    iniWrite->setValue("Parameter/FlawRadiusMin", ui->flawRadiusMin->value());
    iniWrite->setValue("Parameter/FlawRadiusMax", ui->flawRadiusMax->value());
    iniWrite->setValue("Parameter/RestWarn",ui->restWarnBox->value());
    //iniWrite->setValue("Parameter/RunTimeSet", ui->setRuntTme->value());

    //通讯参数
    iniWrite->setValue("Modbus/IPAddress", ui->ipAddress->text());
    iniWrite->setValue("Modbus/CurrentNumAddr", ui->currentNumAddr->value());
    iniWrite->setValue("Modbus/SingleNumAddr", ui->singleNumAddr->value());
    iniWrite->setValue("Modbus/InsertCoordXAddr", ui->insertCoordXAddr->value());
    iniWrite->setValue("Modbus/InsertCoordYAddr", ui->insertCoordYAddr->value());
    iniWrite->setValue("Modbus/FullSignalAddr", ui->fullSignalAddr->value());
    iniWrite->setValue("Modbus/FlawSignalAddr", ui->flawSignalAddr->value());

    iniWrite->setValue("Modbus/CutTime",ui->cutTimeBox->value());
    iniWrite->setValue("Modbus/FallTime",ui->fallTimeBox->value());
    //iniWrite->setValue("Modbus/BlockTime",ui->blockTimeBox->value());
    iniWrite->setValue("Modbus/BufferTime",ui->bufferTimeBox->value());
    //iniWrite->setValue("Modbus/SwitchTime",ui->switchTimeBox->value());
    iniWrite->setValue("Modbus/RemoveOutTime",ui->removeOutBox->value());
    iniWrite->setValue("Modbus/RemoveBackTime",ui->removeBackBox->value());
    iniWrite->setValue("Modbus/LoadTime",ui->loadTimeBox->value());
    iniWrite->setValue("Modbus/ShakeTime",ui->shakeTimeBox->value());
    iniWrite->setValue("Modbus/BlockTwoTime",ui->blockTwoBox->value());

    iniWrite->setValue("Modbus/Shaker1V",ui->shaker1VBox->value());
    iniWrite->setValue("Modbus/Shaker1HZ",ui->shaker1HzBox->value());
    iniWrite->setValue("Modbus/Shaker2V",ui->shaker2VBox->value());
    iniWrite->setValue("Modbus/Shaer2HZ",ui->shaker2HzBox->value());
    iniWrite->setValue("Modbus/Shaker3V",ui->shaker3VBox->value());
    iniWrite->setValue("Modbus/Shaker3HZ",ui->shaker3HzBox->value());
    iniWrite->setValue("Modbus/StopRate",ui->stopRateBox->value());

    //其他参数
    iniWrite->setValue("Other/SetRuntime", ui->setRuntime->value());
    //iniWrite->setValue("Other/SaveImgPath", ui->saveImgPath->text());
    iniWrite->setValue("Other/SaveImgDays", ui->saveImgDays->text());

    delete iniWrite;
}

//读取配置
void SettingWidget::readConfig(QString filename)
{
    QSettings *iniRead = new QSettings(filename, QSettings::IniFormat);
    //相机参数
    //ui->expousetime->setValue(iniRead->value("Camera/Expousetime").toDouble());
    //ui->gainRaw->setValue(iniRead->value("Camera/GainRaw").toInt());
    //ui->lineRate->setValue(iniRead->value("Camera/LineRate").toInt());

    //算法参数
    ui->singleButtleQuantity->setValue(iniRead->value("Parameter/SingleButtleNum").toInt());
    qDebug() << "Parameter/PreProcess = " << iniRead->value("Parameter/PreProcess").toString() << endl;
    ui->preProcessCombox->setCurrentText(iniRead->value("Parameter/PreProcess").toString());
    //qDebug() << "ui->preProcessCombox->setCurrentText = " << ui->preProcessCombox->currentText() << endl;
    ui->operatorSize->setValue(iniRead->value("Parameter/OperatorSize").toInt());
    //ui->closingRadius->setValue(iniRead->value("Parameter/ClosingRadius").toInt());
    ui->minThreshold->setValue(iniRead->value("Parameter/MinThreshold").toInt());
    ui->maxThreshold->setValue(iniRead->value("Parameter/MaxThreshold").toInt());
    ui->minArea->setValue(iniRead->value("Parameter/MinArea").toInt());
    ui->maxArea->setValue(iniRead->value("Parameter/MaxArea").toInt());
    ui->minRadius->setValue(iniRead->value("Parameter/MinRadius").toInt());
    ui->maxRadius->setValue(iniRead->value("Parameter/MaxRadius").toInt());
    ui->minFill->setValue(iniRead->value("Parameter/MinFill").toDouble());
    ui->maxFill->setValue(iniRead->value("Parameter/MaxFill").toDouble());

      ui->flawAreaMin->setValue(iniRead->value("Parameter/FlawAreaMin").toInt());
      ui->flawAreaMax->setValue(iniRead->value("Parameter/FlawAreaMax").toInt());
      ui->flawRadiusMin->setValue(iniRead->value("Parameter/FlawRadiusMin").toInt());
      ui->flawRadiusMax->setValue(iniRead->value("Parameter/FlawRadiusMax").toInt());
      ui->restWarnBox->setValue(iniRead->value("Parameter/RestWarn").toInt());
      qDebug() << "算法参数加载完成" << endl;
      //通讯参数
      ui->ipAddress->setText(iniRead->value("Modbus/IPAddress").toString());
      ui->currentNumAddr->setValue(iniRead->value("Modbus/CurrentNumAddr").toInt());
      qDebug() << "通讯参数加载完成" << endl;

     ui->cutTimeBox->setValue(iniRead->value("Modbus/CutTime").toInt());
     ui->fallTimeBox->setValue(iniRead->value("Modbus/FallTime").toInt());
     //ui->blockTimeBox->setValue(iniRead->value("Modbus/BlockTime").toInt());
     ui->bufferTimeBox->setValue(iniRead->value("Modbus/BufferTime").toInt());
     //ui->switchTimeBox->setValue(iniRead->value("Modbus/SwitchTime").toInt());
     ui->removeOutBox->setValue(iniRead->value("Modbus/RemoveOutTime").toInt());
     ui->removeBackBox->setValue(iniRead->value("Modbus/RemoveBackTime").toInt());
     ui->loadTimeBox->setValue(iniRead->value("Modbus/LoadTime").toInt());
     ui->shakeTimeBox->setValue(iniRead->value("Modbus/ShakeTime").toInt());
     ui->blockTwoBox->setValue(iniRead->value("Modbus/BlockTwoTime").toInt());

    ui->shaker1VBox->setValue(iniRead->value("Modbus/Shaker1V").toInt());
    ui->shaker1HzBox->setValue(iniRead->value("Modbus/Shaker1HZ").toInt());
    ui->shaker2VBox->setValue(iniRead->value("Modbus/Shaker2V").toInt());
    ui->shaker2HzBox->setValue(iniRead->value("Modbus/Shaer2HZ").toInt());
    ui->shaker3VBox->setValue(iniRead->value("Modbus/Shaker3V").toInt());
    ui->shaker3HzBox->setValue(iniRead->value("Modbus/Shaker3HZ").toInt());
    ui->stopRateBox->setValue(iniRead->value("Modbus/StopRate").toInt());

    ui->singleNumAddr->setValue(iniRead->value("Modbus/SingleNumAddr").toInt());
    ui->insertCoordXAddr->setValue(iniRead->value("Modbus/InsertCoordXAddr").toInt());

    ui->insertCoordYAddr->setValue(iniRead->value("Modbus/InsertCoordYAddr").toInt());
    ui->fullSignalAddr->setValue(iniRead->value("Modbus/FullSignalAddr").toInt());
    ui->flawSignalAddr->setValue(iniRead->value("Modbus/FlawSignalAddr").toInt());
    qDebug() << "电气参数加载完成"  << endl;
    //其他参数
    ui->setRuntime->setValue(iniRead->value("Other/SetRunTime").toInt());
    //qDebug()<<iniRead->value("Other/SaveImgPath").toString();
    //ui->saveImgPath->setText("E:/LineScanCount/ShanTouYN/LineScan_Count_YNDaHua/bin/release/ResultImage");
    //ui->saveImgPath->setText(iniRead->value("Other/SaveImgPath").toString());
    ui->saveImgDays->setText(iniRead->value("Other/SaveImgDays").toString());

    currentMode = "当前型号：" + ui->treeWidget->currentItem()->text(0);


    delete iniRead;
}

/**********配方end**********/

/**********相机参数*********/
//曝光
void SettingWidget::on_expousetime_editingFinished()
{
    if(isFirst)
    {
        dcam->SetExposeTime(dcam->exposeTime);
        ui->expousetime->setValue(dcam->exposeTime);
    }
    else
    {
        dcam->SetExposeTime(ui->expousetime->value());
        dcam->CameraStop();
        dcam->userSet->saveUserSet(dcam->userSet->userSet1);
        dcam->CameraStart();
    }
}

//增益
void SettingWidget::on_gainRaw_editingFinished()
{
    if(isFirst)
    {
        dcam->SetAdjustPlus(dcam->gainRaw);
        ui->gainRaw->setValue(dcam->gainRaw);
    }
    else
    {
        dcam->SetAdjustPlus(ui->gainRaw->value());
        dcam->CameraStop();
        dcam->userSet->saveUserSet(dcam->userSet->userSet1);
        dcam->CameraStart();
    }
}

//行频
void SettingWidget::on_lineRate_editingFinished()
{
    if(isFirst)
    {
        dcam->SetLineRate(dcam->lineRate);
        ui->lineRate->setValue(dcam->lineRate);
    }
    else
    {
        dcam->SetLineRate(ui->lineRate->value());
        dcam->CameraStop();
        dcam->userSet->saveUserSet(dcam->userSet->userSet1);
        dcam->CameraStart();
    }
}

/**********相机end*********/

/**********通讯参数*********/
//ip地址
void SettingWidget::on_ipAddress_editingFinished()
{
    mt->ipAddress = ui->ipAddress->text();
}

void SettingWidget::on_currentNumAddr_editingFinished()
{
    cp->currentNumAddr = ui->currentNumAddr->value();
}

void SettingWidget::on_singleNumAddr_editingFinished()
{
    cp->singleNumAddr = ui->singleNumAddr->value();

}

void SettingWidget::on_insertCoordXAddr_editingFinished()
{
    cp->insertCoordXAddr = ui->insertCoordXAddr->value();
}

void SettingWidget::on_insertCoordYAddr_editingFinished()
{
    cp->insertCoordYAddr = ui->insertCoordYAddr->value();
}

void SettingWidget::on_fullSignalAddr_editingFinished()
{
    cp->fullSignalAddr = ui->fullSignalAddr->value();
}

void SettingWidget::on_flawSignalAddr_editingFinished()
{
    cp->flawSignalAddr = ui->flawSignalAddr->value();
}


/**********通讯end*********/

/**********算法参数*********/

//单瓶数量
void SettingWidget::on_singleButtleQuantity_editingFinished()
{
    cp->singleNum = ui->singleButtleQuantity->value();
    emit SingleNumBoxChanged_Sig();
    //Log::Instance()->writeInfo("SingleNumBoxChanged_Siganl 已发送");
    mutex_modbus.lock();
    if(mt->modbus_state == true)
    {
        modbus_write_register(mt->modbus, ui->singleNumAddr->value(), ui->singleButtleQuantity->value());
    }
    mutex_modbus.unlock();
}

void SettingWidget::on_preProcessCombox_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    if(ui->preProcessCombox->currentText() == QStringLiteral("开运算_圆"))
    {
        cp->preProcessIndex = 0;
    }

    if(ui->preProcessCombox->currentText() == QStringLiteral("开运算_方"))
    {
        cp->preProcessIndex = 1;
    }

    if(ui->preProcessCombox->currentText() == QStringLiteral("闭运算_圆"))
    {
        cp->preProcessIndex = 2;
    }

    if(ui->preProcessCombox->currentText() == QStringLiteral("闭运算_方"))
    {
        cp->preProcessIndex = 3;
    }
}

void SettingWidget::on_operatorSize_editingFinished()
{
    cp->operatorSize = ui->operatorSize->value();
}

void SettingWidget::on_minThreshold_editingFinished()
{
    cp->hv_MinThreshold = ui->minThreshold->value();
}

void SettingWidget::on_maxThreshold_editingFinished()
{
    cp->hv_MaxThreshold = ui->maxThreshold->value();
}

void SettingWidget::on_minArea_editingFinished()
{
    cp->hv_MinArea = ui->minArea->value();
}

void SettingWidget::on_maxArea_editingFinished()
{
    cp->hv_MaxArea = ui->maxArea->value();
}

void SettingWidget::on_minRadius_editingFinished()
{
    cp->hv_MinCircleRadius = ui->minRadius->value();
}

void SettingWidget::on_maxRadius_editingFinished()
{
    cp->hv_MaxCircleRadius = ui->maxRadius->value();
}

void SettingWidget::on_minFill_editingFinished()
{
    cp->hv_MinFill = ui->minFill->value();
}

void SettingWidget::on_maxFill_editingFinished()
{
    cp->hv_MaxFill = ui->maxFill->value();
}

/**********算法end*********/

void SettingWidget::on_setRuntime_editingFinished()
{
    cp->setRuntimeValue = ui->setRuntime->value();
}

void SettingWidget::on_IsSaveImg_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    if(ui->IsSaveImg->isChecked())
    {
        cp->isSaveImage = true;
    }
    if(!ui->IsSaveImg->isChecked())
    {
        cp->isSaveImage = false;
    }
}

//void SettingWidget::on_saveImgPath_textChanged()
//{
//    //qDebug()<<666;
//    //cp->saveImagePath = ui->saveImgPath->text();
//}

void SettingWidget::on_saveImgDays_editingFinished()
{
    saveImgDays = ui->saveImgDays->text().toInt();
}

//void SettingWidget::on_saveImgPathBtn_clicked()
//{
//    //ui->saveImgPath->setText(QFileDialog::getExistingDirectory());
//}

void SettingWidget::on_beltBtn_toggled(bool)
{   
    bool chk = ui->beltBtn->isChecked();
    mutex_modbus.lock();
    modbus_write_bit(mt->modbus, 120, chk);
    mutex_modbus.unlock();
}

void SettingWidget::on_shackerBtn_toggled(bool)
{
    bool chk = ui->shackerBtn->isChecked();
    mutex_modbus.lock();
    modbus_write_bit(mt->modbus, 125, chk);
    mutex_modbus.unlock();
}

void SettingWidget::on_bufferBtn_toggled(bool)
{
    bool chk = ui->bufferBtn->isChecked();
    mutex_modbus.lock();
    modbus_write_bit(mt->modbus, 124, chk);
    mutex_modbus.unlock();
}
void SettingWidget::on_blockBtn_toggled(bool)
{
    bool chk = ui->blockBtn->isChecked();
    mutex_modbus.lock();
    modbus_write_bit(mt->modbus, 121, chk);
    mutex_modbus.unlock();
}
void SettingWidget::on_funnelBtn_toggled(bool)
{
    bool chk = ui->funnelBtn->isChecked();
    mutex_modbus.lock();
    modbus_write_bit(mt->modbus, 123, chk);
    mutex_modbus.unlock();
}
void SettingWidget::on_removeBtn_toggled(bool)
{
    bool chk = ui->removeBtn->isChecked();
    mutex_modbus.lock();
    modbus_write_bit(mt->modbus, 122, chk);
    mutex_modbus.unlock();
}

void SettingWidget::on_bufferBtn_1_toggled(bool)
{
    bool chk = ui->bufferBtn_1->isChecked();
    mutex_modbus.lock();
    modbus_write_bit(mt->modbus, 361, chk);
    mutex_modbus.unlock();
}
void SettingWidget::on_bufferBtn_2_toggled(bool)
{
    bool chk = ui->bufferBtn_2->isChecked();
    mutex_modbus.lock();
    modbus_write_bit(mt->modbus, 362, chk);
    mutex_modbus.unlock();
}
void SettingWidget::on_bufferBtn_3_toggled(bool)
{
    bool chk = ui->bufferBtn_3->isChecked();
    mutex_modbus.lock();
    modbus_write_bit(mt->modbus, 363, chk);
    mutex_modbus.unlock();

}
void SettingWidget::on_bufferBtn_4_toggled(bool)
{
    bool chk = ui->bufferBtn_4->isChecked();
    mutex_modbus.lock();
    modbus_write_bit(mt->modbus, 364, chk);
    mutex_modbus.unlock();
}
void SettingWidget::on_bufferBtn_5_toggled(bool)
{
    bool chk = ui->bufferBtn_5->isChecked();
    mutex_modbus.lock();
    modbus_write_bit(mt->modbus, 365, chk);
    mutex_modbus.unlock();
}
void SettingWidget::on_bufferBtn_6_toggled(bool)
{
    bool chk = ui->bufferBtn_6->isChecked();
    mutex_modbus.lock();
    modbus_write_bit(mt->modbus, 366, chk);
    mutex_modbus.unlock();
}
void SettingWidget::on_bufferBtn_7_toggled(bool)
{
    bool chk = ui->bufferBtn_7->isChecked();
    mutex_modbus.lock();
    modbus_write_bit(mt->modbus, 367, chk);
    mutex_modbus.unlock();
}
void SettingWidget::on_bufferBtn_8_toggled(bool)
{
    bool chk = ui->bufferBtn_8->isChecked();
    mutex_modbus.lock();
    modbus_write_bit(mt->modbus, 368, chk);
    mutex_modbus.unlock();
}

void SettingWidget::on_MotorUpbtn_pressed()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_bit(mt->modbus,80,true);
    }
    mutex_modbus.unlock();
}
void SettingWidget::on_MotorUpbtn_released()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_bit(mt->modbus,80,false);
    }
    mutex_modbus.unlock();
}
void SettingWidget::on_MotorDownbtn_pressed()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_bit(mt->modbus,81,true);
    }
    mutex_modbus.unlock();
}
void SettingWidget::on_MotorDownbtn_released()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_bit(mt->modbus,81,false);
    }
    mutex_modbus.unlock();
}

void SettingWidget::on_sheddingBtn_toggled(bool)
{
    //bool chk = ui->sheddingBtn->isChecked();
    mutex_modbus.lock();
    //modbus_write_bit(mt->modbus, 82, chk);
    mutex_modbus.unlock();
}

void SettingWidget::on_cutTimeBox_editingFinished()             //卡料时间
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_register(mt->modbus, HD + 122, ui->cutTimeBox->value());
    }
    mutex_modbus.unlock();
}

void SettingWidget::on_fallTimeBox_editingFinished()            //落料时间
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_register(mt->modbus, HD + 123, ui->fallTimeBox->value());
    }
    mutex_modbus.unlock();
}
//void SettingWidget::on_blockTimeBox_editingFinished()
//{
//    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
//    {
//        //modbus_write_register(mt->modbus, HD + 132, ui->blockTimeBox->value());
//    }
//}
void SettingWidget::on_bufferTimeBox_editingFinished()          //换瓶时间
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_register(mt->modbus, HD + 132, ui->bufferTimeBox->value());
    }
    mutex_modbus.unlock();
}
//void SettingWidget::on_switchTimeBox_editingFinished()
//{
//    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
//    {
//        //modbus_write_register(mt->modbus, HD + 133, ui->switchTimeBox->value());
//    }
//}
void SettingWidget::on_removeOutBox_editingFinished()       //瑕疵剔除时间
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_register(mt->modbus, HD + 134, ui->removeOutBox->value());
    }
    mutex_modbus.unlock();
}
void SettingWidget::on_removeBackBox_editingFinished()      //瑕疵剔除延时
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_register(mt->modbus, HD + 135, ui->removeBackBox->value());
    }
    mutex_modbus.unlock();
}

void SettingWidget::on_shaker1VBox_editingFinished()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_register(mt->modbus, HD + 100, ui->shaker1VBox->value());
        emit Shaker1VBoxChanged();
    }
    mutex_modbus.unlock();
}

void SettingWidget::on_shaker1HzBox_editingFinished()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_register(mt->modbus, HD + 101, ui->shaker1HzBox->value());
    }
    mutex_modbus.unlock();
}

void SettingWidget::on_shaker2VBox_editingFinished()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_register(mt->modbus, HD + 104, ui->shaker2VBox->value());
        emit Shaker2VBoxChanged();
    }
    mutex_modbus.unlock();

}

void SettingWidget::on_shaker2HzBox_editingFinished()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_register(mt->modbus, HD + 105, ui->shaker2HzBox->value());
    }
    mutex_modbus.unlock();
}

void SettingWidget::on_shaker3VBox_editingFinished()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_register(mt->modbus, HD + 102, ui->shaker3VBox->value());
        emit Shaker3VBoxChanged();
    }
    mutex_modbus.unlock();
}

void SettingWidget::on_shaker3HzBox_editingFinished()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_register(mt->modbus, HD + 103, ui->shaker3HzBox->value());
    }
    mutex_modbus.unlock();
}

void SettingWidget::on_flawAreaMin_editingFinished()
{
    cp->flawAreaMin = ui->flawAreaMin->value();
}

void SettingWidget::on_flawAreaMax_editingFinished()
{
    cp->flawAreaMax = ui->flawAreaMax->value();
}

void SettingWidget::on_flawRadiusMin_editingFinished()
{
    cp->flawRadiusMin = ui->flawRadiusMin->value();
}

void SettingWidget::on_flawRadiusMax_editingFinished()
{
    cp->flawRadiusMax = ui->flawRadiusMax->value();
}

void SettingWidget::on_loadTimeBox_editingFinished()            //装瓶时间
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_register(mt->modbus, HD + 136, ui->loadTimeBox->value());
    }
    mutex_modbus.unlock();
}

void SettingWidget::on_stopRateBox_editingFinished()
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_register(mt->modbus, HD + 111, ui->stopRateBox->value());
    }
    mutex_modbus.unlock();
}
void SettingWidget::on_shakeTimeBox_editingFinished()       //抖动时间
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_register(mt->modbus, HD + 137, ui->shakeTimeBox->value());
    }
    mutex_modbus.unlock();
}
void SettingWidget::on_blockTwoBox_editingFinished()        //挡瓶时间2
{
    mutex_modbus.lock();
    if(mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        modbus_write_register(mt->modbus, HD + 138, ui->blockTwoBox->value());
    }
    mutex_modbus.unlock();
}


void SettingWidget::on_restWarnBox_editingFinished()
{
    cp->restWarn = ui->restWarnBox->value();
}

void SettingWidget::on_tabWidget_currentChanged(int)
{
    if(ui->tabWidget->currentIndex() == 2)
    {
        emit tabWidgetEqul_2();
    }
}

void SettingWidget::on_ExitBtn_clicked()
{
    emit exitSig();
}
