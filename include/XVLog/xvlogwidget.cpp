#include "xvlogwidget.h"
#include <QHeaderView>
#include <QCoreApplication>

XVLogWidget::XVLogWidget(QString iconPath, QWidget *parent) :
    QWidget(parent),mIconPath(QCoreApplication::applicationDirPath()+"/ico/log/")
{
    Q_UNUSED(iconPath)
    mainLayout = new QVBoxLayout(this);
    mainLayout->setMargin(0);
    mTableWidget = new QTableWidget();
    mainLayout->addWidget(mTableWidget);

    mTableWidget->setColumnCount(5); //设置列数
    mTableWidget->setColumnWidth(0,this->fontMetrics().width("9999999"));
    mTableWidget->setColumnWidth(1,this->fontMetrics().width("message")*1);
    mTableWidget->setColumnWidth(2,this->fontMetrics().width("15:28:47")+20);
    //设置表头内容
    QStringList header;
    header << QString(QObject::tr("序号"))
                << QString(QObject::tr("类型"))
                << QString(QObject::tr("时间"))
                << QString(QObject::tr("信息"))
                << QString(QObject::tr("来源"));


    mTableWidget->setHorizontalHeaderLabels(header);//设置表头
    mTableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    mTableWidget->horizontalHeader()->setFixedHeight(this->fontMetrics().height()+5); //设置表头的高度
    mTableWidget->verticalHeader()->setDefaultSectionSize(this->fontMetrics().height()+5); //设置行高
    mTableWidget->setFocusPolicy(Qt::NoFocus);   //去除选中虚线框
    mTableWidget->horizontalHeader()->setHighlightSections(false);    //点击表时不对表头行光亮（获取焦点）
    mTableWidget->setFrameShape(QFrame::NoFrame); //设置无边框
    mTableWidget->setShowGrid(false); //设置不显示格子线
    mTableWidget->verticalHeader()->setVisible(false); //设置垂直头不可见
    mTableWidget->setAutoScroll(true);


    QFont LogFont;
    LogFont.setFamily("Microsoft YaHei");

    mTableWidget->setFont(LogFont);

    mTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    mTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次选择一行
    mTableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);  //可多选（Ctrl、Shift、  Ctrl+A都可以）

//    mTableWidget->horizontalHeader()->setSectionsClickable(false);
    mTableWidget->setStyleSheet("background:#3B3B3B;color:#FFFFFF;"
                                "selection-background-color:#00A0E8;selection-color:#FFFFFF;"
                                "font-size:10pt;"
                                "font-family:Microsoft YaHei;"
                                );
    mTableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{"
                                                    "border-left:none;border-top:none;border-right:1px solid rgb(35,35,35);"
                                                    "border-bottom:1px solid rgb(35,35,35);"
                                                    "background:rgb(54,54,54);color:#FFFFFF;"
                                                    "font-size:10pt;"
                                                    "font-family:Microsoft YaHei;}");


    QObject::connect(Log::Instance(),SIGNAL(signal_curLogData(LogData)),this,SLOT(slot_curLogData(LogData)),Qt::QueuedConnection);

    initMenu();
    this->levelChanged(OffLevel);
    initLogShow(true,true,true,true,false);
}

XVLogWidget::~XVLogWidget()
{
}

//void XVLogWidget::setStyle(QString tableWidgetStyle,QString tableHeaderStyle)
//{
//    mTableWidget->setStyleSheet(tableWidgetStyle);
//    mTableWidget->horizontalHeader()->setStyleSheet(tableHeaderStyle);
//}

void XVLogWidget::tableFlush()
{
    int m_row = 0;
    mTableWidget->clearContents();

    QString levelToString;
    QIcon icon;
    QString source;
    LogDataList *logList;
    switch (mLogLevel)
    {
        case TraceLevel : logList = &mTraceLogList; break;
        case InfoLevel : logList = &mInfoLogList; break;
        case WarnLevel : logList = &mWarnLogList; break;
        case ErrorLevel : logList = &mErrorLogList; break;
        case OffLevel: logList = &mAllLogList; break;
        default: break;
    }
    for(LogDataList::iterator it = logList->begin(),endIt = logList->end();it != endIt;it++)
    {
        switch ((*it).logData.level)
        {
            case TraceLevel : levelToString = QString(QObject::tr("跟踪")); icon = QIcon(mIconPath+"trace.png"); break;
            case InfoLevel : levelToString = QString(QObject::tr("消息")); icon = QIcon(mIconPath+"info.png"); break;
            case WarnLevel : levelToString = QString(QObject::tr("警告")); icon = QIcon(mIconPath+"warn.png"); break;
            case ErrorLevel : levelToString = QString(QObject::tr("错误")); icon = QIcon(mIconPath+"error.png"); break;
            default : break;
        }
        if ((*it).logData.location)
        {
            source = "";
            source.append((*it).logData.atFile).append(":").append(QString::number((*it).logData.atLine));
        }
        else
        {
            source = "";
            source.append("unknown");
        }
        mTableWidget->setRowCount(m_row+1);
        mTableWidget->setItem(m_row,0,new QTableWidgetItem(QString::number((*it).number)));
        mTableWidget->setItem(m_row,1,new QTableWidgetItem(icon,levelToString));
        mTableWidget->setItem(m_row,2,new QTableWidgetItem((*it).logData.timestamp));
        mTableWidget->setItem(m_row,3,new QTableWidgetItem((*it).logData.info));
        mTableWidget->setItem(m_row,4,new QTableWidgetItem(source));

        m_row++;
    }
    tableScroll();
}

void XVLogWidget::slot_curLogData(const LogData &logData)
{
    mNumber++;

    MyLogData mData = logDataToMyLogData(mNumber, logData);
    mAllLogList.append(mData);
    if (mAllLogList.count() > mRowCount)
        mAllLogList.removeFirst();

    QString levelToString;
    QIcon icon;
    QString source;

    switch (logData.level)
    {
        case TraceLevel :
        {
            mTraceLogList.append(mData);
            if (mTraceLogList.count() > mRowCount)
                mTraceLogList.removeFirst();
            levelToString = QString(QObject::tr("跟踪"));
            icon = QIcon(mIconPath+"trace.png");
            break;
        }
        case InfoLevel :
        {
            mInfoLogList.append(mData);
            if (mInfoLogList.count() > mRowCount)
                mInfoLogList.removeFirst();
            levelToString = QString(QObject::tr("消息"));
            icon = QIcon(mIconPath+"info.png");
            break;
        }
        case WarnLevel :
        {
            mWarnLogList.append(mData);
            if (mWarnLogList.count() > mRowCount)
                mWarnLogList.removeFirst();
            levelToString = QString(QObject::tr("警告"));
            icon = QIcon(mIconPath+"warn.png");
            break;
        }
        case ErrorLevel :
        {
            mErrorLogList.append(mData);
            if (mErrorLogList.count() > mRowCount)
                mErrorLogList.removeFirst();
            levelToString = QString(QObject::tr("错误"));
            icon = QIcon(mIconPath+"error.png");
            break;
        }
        default : break;
    }
    if (mLogLevel != OffLevel)
    {
        if (logData.level != mLogLevel)
            return;//筛选需要显示的日志
    }
    if (logData.location)
    {
        source.append(logData.atFile).append(":").append(QString::number(logData.atLine));
    }
    else
    {
        source.append("unknown");
    }

    if (mTableWidget->rowCount() >= mRowCount)
        mTableWidget->removeRow(0);
    int m_row = mTableWidget->rowCount();

    mTableWidget->setRowCount(m_row+1);
    mTableWidget->setItem(m_row,0,new QTableWidgetItem(QString::number(mNumber)));
    mTableWidget->setItem(m_row,1,new QTableWidgetItem(icon,levelToString));
    mTableWidget->setItem(m_row,2,new QTableWidgetItem(logData.timestamp));
    mTableWidget->setItem(m_row,3,new QTableWidgetItem(logData.info));
    mTableWidget->setItem(m_row,4,new QTableWidgetItem(source));

    tableScroll();
}

void XVLogWidget::slot_copyData()
{
//未实现
}

MyLogData XVLogWidget::logDataToMyLogData(quint64 num, const LogData &logData)
{
    MyLogData data;
    data.number = num;
    data.logData = logData;
    return data;
}

void XVLogWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void XVLogWidget::setRowCount(int num)
{
    Q_ASSERT(num >= 0);
    mRowCount = num;
}

int XVLogWidget::getRowCount()
{
    return mRowCount;
}

void XVLogWidget::clearLogDataList()
{
    mTraceLogList.clear();
    mInfoLogList.clear();
    mWarnLogList.clear();
    mErrorLogList.clear();
    mAllLogList.clear();

    mNumber = 0;
    mTableWidget->clearContents();
    mTableWidget->setRowCount(0);
}

void XVLogWidget::tableScroll()
{
    mTableWidget->scrollToBottom();
}

void XVLogWidget::levelChanged(LogLevel level)
{
    mLogLevel = level;
    tableFlush();
}

void XVLogWidget::initMenu()
{
    mMenu = new QMenu(this);
    QMenu *m1 = new QMenu(QObject::tr("日志等级"));
    m1->setIcon(QIcon(mIconPath+"level.png"));
    QMenu *m2 = new QMenu(QObject::tr("显示设置"));
    m2->setIcon(QIcon(mIconPath+"show.png"));

    actTrace = new QAction(QObject::tr("跟踪"));
    actTrace->setCheckable(true);
    actInfo = new QAction(QObject::tr("消息"));
    actInfo->setCheckable(true);
    actWarn = new QAction(QObject::tr("警告"));
    actWarn->setCheckable(true);
    actError = new QAction(QObject::tr("错误"));
    actError->setCheckable(true);
    actAll = new QAction(QObject::tr("所有"));
    actAll->setCheckable(true);

    QActionGroup *group = new QActionGroup(this);
    group->addAction(actTrace);
    group->addAction(actInfo);
    group->addAction(actWarn);
    group->addAction(actError);
    group->addAction(actAll);
    m1->addActions(group->actions());
    actAll->setChecked(true);

    actNum = new QAction(QObject::tr("序号"));
    actNum->setCheckable(true);
    actTime = new QAction(QObject::tr("时间"));
    actTime->setCheckable(true);
    actType = new QAction(QObject::tr("类型"));
    actType->setCheckable(true);
    actMsg = new QAction(QObject::tr("信息"));
    actMsg->setCheckable(true);
    actSource = new QAction(QObject::tr("来源"));
    actSource->setCheckable(true);

    m2->addAction(actNum);
    m2->addAction(actTime);
    m2->addAction(actType);
    m2->addAction(actMsg);
    m2->addAction(actSource);

    actClear = new QAction(QIcon(mIconPath+"delete.png"),QObject::tr("删除"));

    mMenu->addMenu(m1);
    mMenu->addMenu(m2);
    mMenu->addSeparator();
    mMenu->addAction(actClear);

    QObject::connect(actTrace,&QAction::triggered,this,&XVLogWidget::slot_actTrace_clicked);
    QObject::connect(actInfo,&QAction::triggered,this,&XVLogWidget::slot_actInfo_clicked);
    QObject::connect(actWarn,&QAction::triggered,this,&XVLogWidget::slot_actWarn_clicked);
    QObject::connect(actError,&QAction::triggered,this,&XVLogWidget::slot_actError_clicked);
    QObject::connect(actAll,&QAction::triggered,this,&XVLogWidget::slot_actAll_clicked);
    QObject::connect(actNum,&QAction::triggered,this,&XVLogWidget::slot_actNum_clicked);
    QObject::connect(actTime,&QAction::triggered,this,&XVLogWidget::slot_actTime_clicked);
    QObject::connect(actType,&QAction::triggered,this,&XVLogWidget::slot_actType_clicked);
    QObject::connect(actMsg,&QAction::triggered,this,&XVLogWidget::slot_actMsg_clicked);
    QObject::connect(actSource,&QAction::triggered,this,&XVLogWidget::slot_actSource_clicked);
    QObject::connect(actClear,&QAction::triggered,this,&XVLogWidget::slot_actClear_clicked);
}

void XVLogWidget::slot_actNum_clicked()
{
    mTableWidget->setColumnHidden(0, !actNum->isChecked());
}

void XVLogWidget::slot_actType_clicked()
{
    mTableWidget->setColumnHidden(1,!actType->isChecked());
}

void XVLogWidget::slot_actTime_clicked()
{
    mTableWidget->setColumnHidden(2,!actTime->isChecked());
}

void XVLogWidget::slot_actMsg_clicked()
{
    mTableWidget->setColumnHidden(3,!actMsg->isChecked());
}

void XVLogWidget::slot_actSource_clicked()
{
    mTableWidget->setColumnHidden(4,!actSource->isChecked());
}

void XVLogWidget::slot_actClear_clicked()
{
    clearLogDataList();
}

void XVLogWidget::contextMenuEvent(QContextMenuEvent *event)
{
    mMenu->exec(QCursor::pos());
    event->accept();
}

void XVLogWidget::slot_actTrace_clicked()
{
    this->levelChanged(TraceLevel);
}

void XVLogWidget::slot_actInfo_clicked()
{
    this->levelChanged(InfoLevel);
}

void XVLogWidget::slot_actWarn_clicked()
{
    this->levelChanged(WarnLevel);
}

void XVLogWidget::slot_actError_clicked()
{
    this->levelChanged(ErrorLevel);
}

void XVLogWidget::slot_actAll_clicked()
{
    this->levelChanged(OffLevel);
}

void XVLogWidget::initLogShow(bool num, bool type, bool time, bool msg, bool source)
{
    actNum->setChecked(num);
    mTableWidget->setColumnHidden(0, !num);
    actType->setChecked(type);
    mTableWidget->setColumnHidden(1,!type);
    actTime->setChecked(time);
    mTableWidget->setColumnHidden(2,!time);
    actMsg->setChecked(msg);
    mTableWidget->setColumnHidden(3,!msg);
#ifdef QT_DEBUG
    actSource->setChecked(source);
    mTableWidget->setColumnHidden(4,!source);
#else
    Q_UNUSED(source)
    actSource->setEnabled(false);
    mTableWidget->setColumnHidden(4,true);
#endif
}
