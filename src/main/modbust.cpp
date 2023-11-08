
#include <QLineSeries>
QT_CHARTS_USE_NAMESPACE
#include "modbust.h"
#include "ui_modbust.h"

#pragma execution_character_set("utf-8")

LogWidget *logBar;
XVLogWidget *Loge;

QLineSeries *seriesCS = new QLineSeries();
QLineSeries *seriesBS = new QLineSeries();
//QChart *chart;


modbust::modbust(Ui::SettingWidget *setWidget) :
    ui(new Ui::modbust)
{
    ui->setupUi(this);

    logBar = new LogWidget();
    Loge =  new XVLogWidget(qApp->applicationDirPath() + "/ico");
    ipAddress = setWidget->ipAddress->text();

    qDebug()<<"IpAddress "<<ipAddress;
    modbus = modbus_new_tcp(ipAddress.toLatin1().data(), 502);
    if(modbus == NULL)
    {
        Log::Instance()->writeError("通讯连接失败，未发现设备");
        modbus_state = false;
    }
    else
    {
        if(modbus_connect(modbus) == 0)
        {
            logBar->logDisplay("消息", "通讯连接成功", true, false);
            Log::Instance()->writeInfo("通讯连接成功");
            modbus_state = true;
        }
        else
        {
            logBar->logDisplay("警告", "通讯连接失败", true, false);
            Log::Instance()->writeError("通讯连接失败");
            modbus_state = false;
        }

        QTimer *mTimer = new QTimer(this);
        connect(mTimer, SIGNAL(timeout()), this, SLOT(modbusTcpReconnect()));
        mTimer->start(5000);
    }
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 1000000;  //设置modbus超时时间为1000毫秒
    modbus_set_response_timeout(modbus, tv.tv_sec, tv.tv_usec);

    isModbusMdu = true;
    isModbusCount = false;
    isModbusMain = false;
}

modbust::~modbust()
{
    delete ui;
    if (modbus != NULL)
    {
        modbus_close(modbus);
    }
    modbus_state = false;
    modbus_free(modbus);
}

//通讯重连
void modbust::modbusTcpReconnect()
{
    //qDebug()<<123;
    if(isModbusCount == false && isModbusMain == false)
    {
        isModbusMdu = true;
        uint16_t tab_reg[64];
        tab_reg[0] = 20;
        uint16_t hd110[1];


        if(modbus_read_registers(modbus, 41198, 1, &hd110[0]) == -1)
        {
            Log::Instance()->writeWarn("通讯断开,尝试重新连接");
            modbus_close(modbus);

            hd110[0] = -1;
            if(modbus_connect(modbus) == 0)
            {
                Log::Instance()->writeInfo("通讯连接成功");
                modbus_state = true;
            }
            else
            {
                Log::Instance()->writeWarn("通讯连接失败");
                modbus_state = false;

            }
        }
        else
        {
            bottleCount = (int)hd110[0];
        }
        isModbusMdu = false;
    }


}

