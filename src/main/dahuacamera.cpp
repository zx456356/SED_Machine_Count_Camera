#include "dahuacamera.h"
#include <QDebug>
#include "mainwindow.h"
using namespace Dahua::GenICam;
using namespace Dahua::Infra;
//#pragma execution_character_set("utf-8")
#define DEFAULT_SHOW_RATE (200) // Ĭ����ʾ֡��
#define DEFAULT_ERROR_STRING ("N/A")
#define MAX_FRAME_STAT_NUM (50)
#define MIN_LEFT_LIST_NUM (2)
#define MAX_STATISTIC_INTERVAL (5000000000) // List�ĸ���ʱ������һ֡��ʱ�������


DaHuaCamera::DaHuaCamera(QObject *parent) : QObject(parent)
    , m_thdDisplayThread(CThreadLite::ThreadProc(&DaHuaCamera::DisplayThreadProc, this), "Display")
    , m_nDisplayInterval(0)
    , m_nFirstFrameTime(0)
    , m_nLastFrameTime(0)
    //, m_bNeedUpdate(true)
    //, m_nTotalFrameCount(0)
{
    if(init_Camera())
    {
        isCameraConnect = true;
    }
    else
    {
        isCameraConnect = false;
    }
    isImageQueue = false;

}

DaHuaCamera::~DaHuaCamera()
{
    if (NULL != m_pStreamSource && m_pStreamSource->isGrabbing())
        m_pStreamSource->stopGrabbing();
    if (NULL != m_pCamera && m_pCamera->isConnected())
        m_pCamera->disConnect();
}

//���ȡͼ
/**
 * @brief �����ʼ��
 * ��ʼ������������������豸�����������ʼ�ɼ�
 * @return �ɹ�����true,���򷵻�false
 */
bool DaHuaCamera::init_Camera()
{
    //�������������
    CSystem &systemObj = CSystem::getInstance();

    if (false == systemObj.discovery(m_vCameraPtrList))
    {
        Log::Instance()->writeInfo("δ�������");
        return false;
    }
    if (m_vCameraPtrList.size() < 1)
    {

    }
    else
    {
        SetCemera(m_vCameraPtrList[0]->getKey());
        IEventSubscribePtr eventPtr = systemObj.createEventSubscribe(m_pCamera);
        qDebug()<<m_vCameraPtrList[0]->getKey();
        eventPtr->subscribeConnectArgs(ConnectArgProc(&DaHuaCamera::onDeviceLinkNotify, this));
    }

    //�������
    if (CameraOpen())
    {
        Log::Instance()->writeInfo("���������");
        // ������������
        CameraChangeTrig(DaHuaCamera::trigContinous);
        GetExposeTime();
        GetAdjustPlus();
        GetLineRate();

        userSet = systemObj.createUserSetControl(m_pCamera);
        userSet->setCurrentUserSet(IUserSetControl::userSet1);

        if(CameraStart())
        {
            Log::Instance()->writeInfo("��������ɹ�");
        }
        else
        {
            Log::Instance()->writeInfo("�������ʧ��");
        }


        //qRegisterMetaType<uint64_t>("uint64_t");
        //connect(this, SIGNAL(signalShowImage(uint8_t*, int, int, uint64_t)), this, SLOT(ShowImage(uint8_t*, int, int, uint64_t)));
        //�������Ƿ����
//        QTimer *timer2 = new QTimer(this);
//        connect(timer2, SIGNAL(timeout()), this, SLOT(CameraReconnection()));
//        timer2->start(1000);

        return true;
    }
    else
    {
        logBar->logDisplay("����", "�������ʧ��", true, true);
        Log::Instance()->writeWarn("���������");
        return false;
    }

    return false;
}

/**
 * @brief ȡ���ص�����
 * ��ͼƬ�������
 * @param frame �ɼ�����ͼƬ
 */
void DaHuaCamera::FrameCallback(const Dahua::GenICam::CFrame &frame)
{
    if(isImageQueue)
    {
        CFrameInfo frameInfo;
        frameInfo.m_nWidth = frame.getImageWidth();
        frameInfo.m_nHeight = frame.getImageHeight();
        frameInfo.m_nBufferSize = frame.getImageSize();
        frameInfo.m_nPaddingX = frame.getImagePadddingX();
        frameInfo.m_nPaddingY = frame.getImagePadddingY();
        frameInfo.m_ePixelType = frame.getImagePixelFormat();
        frameInfo.m_pImageBuf = (BYTE *)malloc(sizeof(BYTE)* frameInfo.m_nBufferSize);
        frameInfo.m_nTimeStamp = frame.getImageTimeStamp();
        frameInfo.m_nImage = frame.getImage();


        //qDebug()<<"��ǰʱ�� "<<QTime::currentTime().toString("hh_mm_ss_zzz");
        //qDebug()<<"ʱ��� "<<frame.getImageTimeStamp();
        //Log::Instance()->WriteInfo("")
//        QFile file("debug.txt");
//        file.open(QIODevice::ReadWrite | QIODevice::Append);
//        QTextStream stream(&file);
//        stream << QTime::currentTime().toString("hh_mm_ss_zzz") << "    " <<frame.getImageTimeStamp()<< "    " <<m_qDisplayFrameQueue.size() <<"\r\n";
//        //stream << frame.getImageTimeStamp() << "\r\n";



        /* �ڴ�����ʧ�ܣ�ֱ�ӷ��� */
        if (frameInfo.m_pImageBuf != NULL)
        {
            memcpy(frameInfo.m_pImageBuf, frame.getImage(), frame.getImageSize());

//            if(m_qDisplayFrameQueue.size() > 5)
//            {
//                logBar->logDisplay("����", "����ʱ�����", true, true);
//
//            }
            //qDebug()<<"m_qDisplayFrameQueue.size() "<<m_qDisplayFrameQueue.size();
            if (m_qDisplayFrameQueue.size() > 64)
            {
                Log::Instance()->writeWarn("ͼ������ݴ�ͼ����ĿΪ" + QString::number(m_qDisplayFrameQueue.size()));
                CFrameInfo frameOld;
                m_qDisplayFrameQueue.get(frameOld);
                free(frameOld.m_pImageBuf);
            }

            m_qDisplayFrameQueue.push_back(frameInfo);
        }

        recvNewFrame(frame);
    }


}

// �����ع�
bool DaHuaCamera::SetExposeTime(double dExposureTime)
{

    if (NULL == m_pCamera)
    {
        printf("Set ExposureTime fail. No camera or camera is not connected.\n");
        Log::Instance()->writeWarn("�����ع�ʧ�ܣ�δ�������");
        return false;
    }
    CDoubleNode nodeExposureTime(m_pCamera, "ExposureTime");

    if (false == nodeExposureTime.isValid())
    {
        printf("get ExposureTime node fail.\n");
        return false;
    }


    if (false == nodeExposureTime.isAvailable())
    {
        printf("ExposureTime is not available.\n");
        return false;
    }

    if (false == nodeExposureTime.setValue(dExposureTime))
    {
        printf("set ExposureTime value = %f fail.\n", dExposureTime);
        Log::Instance()->writeWarn("�����ع�ʧ��");
        return false;
    }
    return true;
}

// ��������
bool DaHuaCamera::SetAdjustPlus(double dGainRaw)
{
    if (NULL == m_pCamera)
    {
        printf("Set GainRaw fail. No camera or camera is not connected.\n");
        Log::Instance()->writeWarn("��������ʧ�ܣ�δ�������");
        return false;
    }

    CDoubleNode nodeGainRaw(m_pCamera, "GainRaw");

    if (false == nodeGainRaw.isValid())
    {
        printf("get GainRaw node fail.\n");
        return false;
    }

    if (false == nodeGainRaw.isAvailable())
    {
        printf("GainRaw is not available.\n");
        return false;
    }

    if (false == nodeGainRaw.setValue(dGainRaw))
    {
        printf("set GainRaw value = %f fail.\n", dGainRaw);
       Log::Instance()->writeWarn("��������ʧ��");
        //logBar->logDisplay("����", "��������ʧ��", true, false);
        return false;
    }

    return true;
}

// ������Ƶ
bool DaHuaCamera::SetLineRate(double LineRate)
{
    if (NULL == m_pCamera)
    {
        printf("Set AcquisitionLineRate fail. No camera or camera is not connected.\n");
        Log::Instance()->writeWarn("������Ƶʧ�ܣ�δ�������");
        return false;
    }

    CDoubleNode nodeLineRate(m_pCamera, "AcquisitionLineRate");

    if (false == nodeLineRate.isValid())
    {
        printf("get LineRate node fail.\n");
        return false;
    }

    if (false == nodeLineRate.isAvailable())
    {
        printf("LineRate is not available.\n");
        return false;
    }

    if (false == nodeLineRate.setValue(LineRate))
    {
        printf("set GainRaw value = %f fail.\n", LineRate);
        Log::Instance()->writeWarn("������Ƶʧ��");
        return false;
    }

    return true;
}

bool DaHuaCamera::GetExposeTime()
{
    if (NULL == m_pCamera)
    {
        printf("Get ExposureTime fail. No camera or camera is not connected.\n");
        Log::Instance()->writeWarn("��ȡ�ع�ʧ�ܣ�δ�������");
        return false;
    }
    CDoubleNode nodeExposureTime(m_pCamera, "ExposureTime");

    if (false == nodeExposureTime.isValid())
    {
        printf("get ExposureTime node fail.\n");
        return false;
    }


    if (false == nodeExposureTime.isAvailable())
    {
        printf("ExposureTime is not available.\n");
        return false;
    }

    if (false == nodeExposureTime.getValue(exposeTime))
    {
        Log::Instance()->writeWarn("��ȡ�ع�ֵʧ��");
        return false;
    }
    qDebug()<<"exposeTime " <<exposeTime;
    return true;
}

bool DaHuaCamera::GetAdjustPlus()
{
    if (NULL == m_pCamera)
    {
        printf("Get GainRaw fail. No camera or camera is not connected.\n");
        Log::Instance()->writeWarn("��ȡ����ʧ�ܣ�δ�������");
        return false;
    }

    CDoubleNode nodeGainRaw(m_pCamera, "GainRaw");

    if (false == nodeGainRaw.isValid())
    {
        printf("get GainRaw node fail.\n");
        return false;
    }

    if (false == nodeGainRaw.isAvailable())
    {
        printf("GainRaw is not available.\n");
        return false;
    }

    if (false == nodeGainRaw.getValue(gainRaw))
    {
        Log::Instance()->writeWarn("��ȡ����ʧ��");
        return false;
    }
    qDebug()<<"gainRaw " <<gainRaw;
    return true;
}

bool DaHuaCamera::GetLineRate()
{
    if (NULL == m_pCamera)
    {
        printf("Get AcquisitionLineRate fail. No camera or camera is not connected.\n");
        Log::Instance()->writeWarn("��ȡ��Ƶʧ�ܣ�δ�������");
        return false;
    }

    CDoubleNode nodeLineRate(m_pCamera, "AcquisitionLineRate");

    if (false == nodeLineRate.isValid())
    {
        printf("get LineRate node fail.\n");
        return false;
    }

    if (false == nodeLineRate.isAvailable())
    {
        printf("LineRate is not available.\n");
        return false;
    }

    if (false == nodeLineRate.getValue(lineRate))
    {
        Log::Instance()->writeWarn("��ȡ��Ƶʧ��");
        return false;
    }
    qDebug()<<"lineRate " <<lineRate;
    return true;
}


// �����
bool DaHuaCamera::CameraOpen(void)
{
    if (NULL == m_pCamera)
    {
        printf("connect camera fail. No camera.\n");
        Log::Instance()->writeWarn("�������ʧ�ܣ�δ�������");
        return false;
    }

    if (true == m_pCamera->isConnected())
    {
        printf("camera is already connected.\n");
        Log::Instance()->writeInfo("������ӳɹ�");
        return true;
    }

    if (false == m_pCamera->connect())
    {
        printf("connect camera fail.\n");
        Log::Instance()->writeWarn("�������ʧ��");
        return false;
    }

    return true;
}

// �ر����
bool DaHuaCamera::CameraClose(void)
{
    if (NULL == m_pCamera)
    {
        printf("disconnect camera fail. No camera.\n");
         Log::Instance()->writeWarn("�ر����ʧ�ܣ�δ�������");
        return false;
    }

    if (false == m_pCamera->isConnected())
    {
        printf("camera is already disconnected.\n");
        Log::Instance()->writeInfo("����ѶϿ�����");
        return true;
    }

    if (false == m_pCamera->disConnect())
    {
        printf("disconnect camera fail.\n");
        Log::Instance()->writeWarn("�ر����ʧ��");
        return false;
    }

    return true;
}

// ��ʼ�ɼ�
bool DaHuaCamera::CameraStart()
{

    if (NULL == m_pStreamSource)
    {
        m_pStreamSource = CSystem::getInstance().createStreamSource(m_pCamera);
        m_pStreamSource->setBufferCount(64);
    }

    if (NULL == m_pStreamSource)
    {
        return false;
    }

    if (m_pStreamSource->isGrabbing())
    {
        return true;
    }

    bool bRet = m_pStreamSource->attachGrabbing(IStreamSource::Proc(&DaHuaCamera::FrameCallback, this));
    if (!bRet)
    {
        return false;
    }

    if (!m_pStreamSource->startGrabbing())
    {
        return false;
    }

    return true;
}

// ֹͣ�ɼ�
bool DaHuaCamera::CameraStop()
{
    if (m_pStreamSource != NULL)
    {
        m_pStreamSource->detachGrabbing(IStreamSource::Proc(&DaHuaCamera::FrameCallback, this));
        m_pStreamSource->stopGrabbing();
        m_pStreamSource.reset();
    }

    /* �����ʾ���� */
    m_qDisplayFrameQueue.clear();
    return true;
}

// �л��ɼ���ʽ��������ʽ �������ɼ����ⲿ���������������
bool DaHuaCamera::CameraChangeTrig(ETrigType trigType)
{
    if (NULL == m_pCamera)
    {
        printf("Change Trig fail. No camera or camera is not connected.\n");
        return false;
    }

    if (trigContinous == trigType)
    {
        //���ô���ģʽ
        CEnumNode nodeTriggerMode(m_pCamera, "TriggerMode");
        if (false == nodeTriggerMode.isValid())
        {
            printf("get TriggerMode node fail.\n");
            return false;
        }
        if (false == nodeTriggerMode.setValueBySymbol("Off"))
        {
            printf("set TriggerMode value = Off fail.\n");
            return false;
        }
    }
    else if (trigSoftware == trigType)
    {
        //���ô�����
        CEnumNode nodeTriggerSelector(m_pCamera, "TriggerSelector");
        if (false == nodeTriggerSelector.isValid())
        {
            printf("get TriggerSelector node fail.\n");
            return false;
        }
        if (false == nodeTriggerSelector.setValueBySymbol("FrameStart"))
        {
            printf("set TriggerSelector value = FrameStart fail.\n");
            return false;
        }

        //���ô���ģʽ
        CEnumNode nodeTriggerMode(m_pCamera, "TriggerMode");
        if (false == nodeTriggerMode.isValid())
        {
            printf("get TriggerMode node fail.\n");
            return false;
        }
        if (false == nodeTriggerMode.setValueBySymbol("On"))
        {
            printf("set TriggerMode value = On fail.\n");
            return false;
        }

        //���ô���ԴΪ����
        CEnumNode nodeTriggerSource(m_pCamera, "TriggerSource");
        if (false == nodeTriggerSource.isValid())
        {
            printf("get TriggerSource node fail.\n");
            return false;
        }
        if (false == nodeTriggerSource.setValueBySymbol("Software"))
        {
            printf("set TriggerSource value = Software fail.\n");
            return false;
        }
    }
    else if (trigLine == trigType)
    {
        //���ô�����
        CEnumNode nodeTriggerSelector(m_pCamera, "TriggerSelector");
        if (false == nodeTriggerSelector.isValid())
        {
            printf("get TriggerSelector node fail.\n");
            return false;
        }
        if (false == nodeTriggerSelector.setValueBySymbol("FrameStart"))
        {
            printf("set TriggerSelector value = FrameStart fail.\n");
            return false;
        }


        //���ô���ԴΪLine1����
        CEnumNode nodeTriggerSource(m_pCamera, "TriggerSource");
        if (false == nodeTriggerSource.isValid())
        {
            printf("get TriggerSource node fail.\n");
            return false;
        }
        if (false == nodeTriggerSource.setValueBySymbol("Line1"))
        {
            printf("set TriggerSource value = Line1 fail.\n");
            return false;
        }

        //���ô���ģʽ
        CEnumNode nodeTriggerMode(m_pCamera, "TriggerMode");
        if (false == nodeTriggerMode.isValid())
        {
            printf("get TriggerMode node fail.\n");
            return false;
        }
        if (false == nodeTriggerMode.setValueBySymbol("On"))
        {
            printf("set TriggerMode value = On fail.\n");
            return false;
        }
    }

    return true;
}

// ִ��һ������
bool DaHuaCamera::ExecuteSoftTrig(void)
{
    if (NULL == m_pCamera)
    {
        printf("Set GainRaw fail. No camera or camera is not connected.\n");
        return false;
    }

    CCmdNode nodeTriggerSoftware(m_pCamera, "TriggerSoftware");
    if (false == nodeTriggerSoftware.isValid())
    {
        printf("get TriggerSoftware node fail.\n");
        return false;
    }
    if (false == nodeTriggerSoftware.execute())
    {
        printf("set TriggerSoftware fail.\n");
        return false;
    }

    printf("ExecuteSoftTrig success.\n");
    return true;
}

// ���õ�ǰ���
void DaHuaCamera::SetCemera(const QString& strKey)
{
    CSystem &systemObj = CSystem::getInstance();
    m_pCamera = systemObj.getCameraPtr(strKey.toStdString().c_str());
}

// �������
void DaHuaCamera::onDeviceLinkNotify(const SConnectArg &conArg)
{
    if (SConnectArg::offLine == conArg.m_event)
    {
        printf("*********** ������� ***********\n");
        CameraStop();
        isCameraConnect = false;
        //logBar->logDisplay("����", "����Ͽ�����", true, true);
        Log::Instance()->writeWarn("����Ͽ�����");

    }
    else if (SConnectArg::onLine == conArg.m_event)
    {
        printf("������ߣ���������.\n");
        // �û��Զ��崦�� �� һ�������������������ʼ������ʼ��ͼ
        if(init_Camera())
        {
            isCameraConnect = true;
        }

    }
}

// ��ʾ�߳�
void DaHuaCamera::DisplayThreadProc(Dahua::Infra::CThreadLite& lite)
{
    return;
    while (lite.looping())
    {
        time.start();
        CFrameInfo frameInfo;

        if (false == m_qDisplayFrameQueue.get(frameInfo, 500))
        {
            continue;
        }

        // �ж��Ƿ�Ҫ��ʾ��������ʾ���ޣ�200֡�����Ͳ���ת�롢��ʾ����
        if (!isTimeToDisplay())
        {
            /* �ͷ��ڴ� */
            free(frameInfo.m_pImageBuf);
            continue;
        }
        /* mono8��ʽ�ɲ���ת�룬ֱ����ʾ��������ʽ��Ҫ����ת�������ʾ */
        if (Dahua::GenICam::gvspPixelMono8 == frameInfo.m_ePixelType)
        {
            //��ʾ�߳��з�����ʾ�źţ������߳�����ʾͼ��
            //emit signalShowImage(frameInfo.m_pImageBuf, frameInfo.m_nWidth, frameInfo.m_nHeight, frameInfo.m_ePixelType);
            ShowImage(frameInfo.m_pImageBuf, frameInfo.m_nWidth, frameInfo.m_nHeight, frameInfo.m_ePixelType);
        }
        else
        {
            /* ת�� */
            uint8_t *pRGBbuffer = NULL;
            int nRgbBufferSize = 0;
            nRgbBufferSize = frameInfo.m_nWidth * frameInfo.m_nHeight * 3;
            pRGBbuffer = (uint8_t *)malloc(nRgbBufferSize);
            if (pRGBbuffer == NULL)
            {
                /* �ͷ��ڴ� */
                free(frameInfo.m_pImageBuf);
                printf("RGBbuffer malloc failed.\n");
                continue;
            }

            IMGCNV_SOpenParam openParam;
            openParam.width = frameInfo.m_nWidth;
            openParam.height = frameInfo.m_nHeight;
            openParam.paddingX = frameInfo.m_nPaddingX;
            openParam.paddingY = frameInfo.m_nPaddingY;
            openParam.dataSize = frameInfo.m_nBufferSize;
            openParam.pixelForamt = frameInfo.m_ePixelType;

            IMGCNV_EErr status = IMGCNV_ConvertToRGB24(frameInfo.m_pImageBuf, &openParam, pRGBbuffer, &nRgbBufferSize);
            if (IMGCNV_SUCCESS != status)
            {
                /* �ͷ��ڴ� */
                printf("IMGCNV_ConvertToRGB24 failed.\n");
                free(frameInfo.m_pImageBuf);
                free(pRGBbuffer);
                return;
            }

            /* �ͷ��ڴ� */
            free(frameInfo.m_pImageBuf);

            //��ʾ�߳��з�����ʾ�źţ������߳�����ʾͼ��
            //emit signalShowImage(pRGBbuffer, openParam.width, openParam.height, openParam.pixelForamt);

        }
    }
}

bool DaHuaCamera::isTimeToDisplay()
{
    CGuard guard(m_mxTime);

    // ����ʾ
    if (m_nDisplayInterval <= 0)
    {
        return false;
    }

    // ��һ֡������ʾ
    if (m_nFirstFrameTime == 0 || m_nLastFrameTime == 0)
    {
        m_nFirstFrameTime = m_elapsedTimer.nsecsElapsed();
        m_nLastFrameTime = m_nFirstFrameTime;

        return true;
    }

    // ��ǰ֡����һ֡�ļ�����������ʾ�������ʾ
    uint64_t nCurTimeTmp = m_elapsedTimer.nsecsElapsed();
    uint64_t nAcquisitionInterval = nCurTimeTmp - m_nLastFrameTime;
    if (nAcquisitionInterval > m_nDisplayInterval)
    {
        m_nLastFrameTime = nCurTimeTmp;
        return true;
    }

    // ��ǰ֡����ڵ�һ֡��ʱ����
    uint64_t nPre = (m_nLastFrameTime - m_nFirstFrameTime) % m_nDisplayInterval;
    if (nPre + nAcquisitionInterval > m_nDisplayInterval)
    {
        m_nLastFrameTime = nCurTimeTmp;
        return true;
    }

    return false;
}

// ������ʾƵ��
void DaHuaCamera::setDisplayFPS(int nFPS)
{
    if (nFPS > 0)
    {
        CGuard guard(m_mxTime);

        m_nDisplayInterval = 1000 * 1000 * 1000.0 / nFPS;
    }
    else
    {
        CGuard guard(m_mxTime);
        m_nDisplayInterval = 0;
    }
}

//��ʾͼƬ
bool DaHuaCamera::ShowImage(uint8_t* pRgbFrameBuf, int nWidth, int nHeight, uint64_t nPixelFormat)
{
    if (NULL == pRgbFrameBuf ||
        nWidth == 0 ||
        nHeight == 0)
    {
        printf("%s image is invalid.\n", __FUNCTION__);
        return false;
    }
    if (Dahua::GenICam::gvspPixelMono8 == nPixelFormat)
    {
        img = QImage(pRgbFrameBuf, nWidth, nHeight, QImage::Format_Grayscale8);
    }
    else
    {
        img = QImage(pRgbFrameBuf, nWidth, nHeight, QImage::Format_RGB888);
    }

    QTime time = QTime::currentTime();
    QString path = QString("test") + "/" + time.toString("hh_mm_ss_zzz") + ".JPG";
    //qDebug()<<path;
    img.save(path);
    //free(pRgbFrameBuf);


    return true;
}

void DaHuaCamera::recvNewFrame(const CFrame& pBuf)
{
//	QMutexLocker locker(&m_mxStatistic);
//	if (m_listFrameStatInfo.size() >= MAX_FRAME_STAT_NUM)
//	{
//		m_listFrameStatInfo.pop_front();
//	}
//	m_listFrameStatInfo.push_back(FrameStatInfo(pBuf.getImageSize(), m_elapsedTimer.nsecsElapsed()));
//	++m_nTotalFrameCount;

//	if (m_listFrameStatInfo.size() > MIN_LEFT_LIST_NUM)
//	{
//		FrameStatInfo infoFirst = m_listFrameStatInfo.front();
//		FrameStatInfo infoLast = m_listFrameStatInfo.back();
//        while (m_listFrameStatInfo.size() > MIN_LEFT_LIST_NUM && infoLast.m_nPassTime - infoFirst.m_nPassTime > MAX_STATISTIC_INTERVAL)
//		{
//			m_listFrameStatInfo.pop_front();
//			infoFirst = m_listFrameStatInfo.front();
//		}
//	}

//	m_bNeedUpdate = true;
}
