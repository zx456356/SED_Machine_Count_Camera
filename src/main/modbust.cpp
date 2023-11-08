
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
        Log::Instance()->writeError("ͨѶ����ʧ�ܣ�δ�����豸");
        modbus_state = false;
    }
    else
    {
        if(modbus_connect(modbus) == 0)
        {
            logBar->logDisplay("��Ϣ", "ͨѶ���ӳɹ�", true, false);
            Log::Instance()->writeInfo("ͨѶ���ӳɹ�");
            modbus_state = true;
        }
        else
        {
            logBar->logDisplay("����", "ͨѶ����ʧ��", true, false);
            Log::Instance()->writeError("ͨѶ����ʧ��");
            modbus_state = false;
        }

        QTimer *mTimer = new QTimer(this);
        connect(mTimer, SIGNAL(timeout()), this, SLOT(modbusTcpReconnect()));
        mTimer->start(5000);
    }
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 1000000;  //����modbus��ʱʱ��Ϊ1000����
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

//ͨѶ����
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
            Log::Instance()->writeWarn("ͨѶ�Ͽ�,������������");
            modbus_close(modbus);

            hd110[0] = -1;
            if(modbus_connect(modbus) == 0)
            {
                Log::Instance()->writeInfo("ͨѶ���ӳɹ�");
                modbus_state = true;
            }
            else
            {
                Log::Instance()->writeWarn("ͨѶ����ʧ��");
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

