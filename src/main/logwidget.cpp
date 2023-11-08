#include "logwidget.h"
#include "ui_logwidget.h"

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidget)
{
    ui->setupUi(this);

    log_bar_init();

    cleanUpLog();

    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteOperation()));  //删除所有行


}

LogWidget::~LogWidget()
{
    delete ui;
}

//日志栏初始化
void LogWidget::log_bar_init()
{
    ui->tableWidget->verticalHeader()->hide();  //取消行号
    ui->tableWidget->clearContents();           //清除内容

    ui->tableWidget->setColumnWidth(0, 120);
    ui->tableWidget->setColumnWidth(1, 120);
    ui->tableWidget->setColumnWidth(2, 250);


    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    //日志栏右击菜单
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);   //设置右击菜单显示方法
    tableMenu = new QMenu(ui->tableWidget);
    deleteAction = new QAction("删除", this);
    displayMenu = new QMenu("显示等级", ui->tableWidget);
    infoDisplay = new QAction("消息", this);
    warningDisplay = new QAction("警告", this);
    errorDisplay = new QAction("错误", this);
    allDisplay = new QAction("所有", this);
    displayMenu->addAction(infoDisplay);
    displayMenu->addAction(warningDisplay);
    displayMenu->addAction(errorDisplay);
    displayMenu->addAction(allDisplay);
    tableMenu->addMenu(displayMenu);
    tableMenu->addAction(deleteAction);

    displayGroup = new QActionGroup(this);
    displayGroup->addAction(infoDisplay);
    displayGroup->addAction(warningDisplay);
    displayGroup->addAction(errorDisplay);
    displayGroup->addAction(allDisplay);
    displayGroup->setExclusive(true);       //显示状态互斥

    //动作选中状态显示
    infoDisplay->setCheckable(true);
    warningDisplay->setCheckable(true);
    errorDisplay->setCheckable(true);
    allDisplay->setCheckable(true);
    allDisplay->setChecked(true);   //默认显示所有


}

//定时清理日志
void LogWidget::cleanUpLog()
{
    QString path = "Log";
    QDir dir(path);
    QFileInfoList infolist = dir.entryInfoList(QDir::Files|QDir::NoDotAndDotDot);
    for(int i=0;i<infolist.count();i++)
    {
        if(infolist.at(i).isFile())
        {
            QFileInfo fileInfo(infolist.at(i));
            QDir savePath(infolist.at(i).absoluteFilePath());
            QFile file(infolist.at(i).fileName());
            qDebug()<<infolist.at(i).filePath();
            QDateTime date = QDateTime::currentDateTime().addDays(3);

            if(date.secsTo(fileInfo.birthTime()) < 0)
            {
                if(remove(infolist.at(i).filePath().toStdString().data()) == 0)
                {
                    qDebug()<<"日志清理完成";
                }

            }
        }
    }
}

//菜单弹出在鼠标点击位置
void LogWidget::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    tableMenu->exec(QCursor::pos());

    //一直执行信息显示函数
    QTimer *mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(isDisplay()));
    mTimer->start(10);


}

//删除日志所有行
void LogWidget::deleteOperation()
{
    for(int row = ui->tableWidget->rowCount() - 1;row >= 0; row--)
    {
        ui->tableWidget->removeRow(row);
    }
}

/**
 * @brief 日志显示、保存
 * @param type  日志类型
 * @param msg   日志内容
 * @param isDisplay 是否显示
 * @param isText    是否保存到文件
 */
void LogWidget::logDisplay(QString type, QString msg, bool isDisplay, bool isText)
{
    if(isDisplay)
    {   
        date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        Rowcount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(Rowcount);
        ui->tableWidget->setItem(Rowcount, 0, new QTableWidgetItem(QString::number(Rowcount+1, 10)));//序号
        ui->tableWidget->setItem(Rowcount, 1, new QTableWidgetItem(type));      //类型
        ui->tableWidget->setItem(Rowcount, 2, new QTableWidgetItem(date));      //时间
        ui->tableWidget->setItem(Rowcount, 3, new QTableWidgetItem(msg));       //内容

        ui->tableWidget->item(Rowcount, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(Rowcount, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->item(Rowcount, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        if(type == "消息")
        {
            ui->tableWidget->item(Rowcount, 0)->setForeground(QColor(0, 0, 0));
            ui->tableWidget->item(Rowcount, 1)->setForeground(QColor(0, 0, 0));
            ui->tableWidget->item(Rowcount, 2)->setForeground(QColor(0, 0, 0));
            ui->tableWidget->item(Rowcount, 3)->setForeground(QColor(0, 0, 0));
        }
        else if(type == "警告")
        {
            ui->tableWidget->item(Rowcount, 0)->setForeground(QColor(120, 120, 0));
            ui->tableWidget->item(Rowcount, 1)->setForeground(QColor(120, 120, 0));
            ui->tableWidget->item(Rowcount, 2)->setForeground(QColor(120, 120, 0));
            ui->tableWidget->item(Rowcount, 3)->setForeground(QColor(120, 120, 0));
        }
        else if(type == "错误")
        {
            ui->tableWidget->item(Rowcount, 0)->setForeground(QColor(255, 0, 0));
            ui->tableWidget->item(Rowcount, 1)->setForeground(QColor(255, 0, 0));
            ui->tableWidget->item(Rowcount, 2)->setForeground(QColor(255, 0, 0));
            ui->tableWidget->item(Rowcount, 3)->setForeground(QColor(255, 0, 0));
        }

        ui->tableWidget->scrollToBottom();  //滚动条自动滚到底部
    }

    if(isText)
    {
        QFile logFile("Log/"+QDateTime::currentDateTime().toString("yyyy-MM-dd")+".txt");
        logFile.open(QIODevice::ReadWrite | QIODevice::Append);
        QTextStream stream(&logFile);
        stream<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<"  ["
              <<type<<"]  "<<msg<<endl;

    }




}

//日志信息显示筛选
void LogWidget::isDisplay()
{
    Rowcount = ui->tableWidget->rowCount();
    if(infoDisplay->isChecked())
    {
        for(int i = 0; i < Rowcount; i++)
        {
            QString text = ui->tableWidget->item(i, 1)->text();
            if(text == "消息")
            {
                ui->tableWidget->setRowHidden(i, false);
            }
            else
            {
                ui->tableWidget->setRowHidden(i, true);
            }
        }
    }

    if(warningDisplay->isChecked())
    {
        for(int i = 0; i < Rowcount; i++)
        {
            QString text = ui->tableWidget->item(i, 1)->text();
            if(text == "警告")
            {
                ui->tableWidget->setRowHidden(i, false);
            }
            else
            {
                ui->tableWidget->setRowHidden(i, true);
            }
        }
    }

    if(errorDisplay->isChecked())
    {
        for(int i = 0; i < Rowcount; i++)
        {
            QString text = ui->tableWidget->item(i, 1)->text();
            if(text == "错误")
            {
                ui->tableWidget->setRowHidden(i, false);
            }
            else
            {
                ui->tableWidget->setRowHidden(i, true);
            }
        }
    }

    if(allDisplay->isChecked())
    {
        for(int i = 0; i < Rowcount; i++)
        {
            ui->tableWidget->setRowHidden(i, false);
        }
    }

}
