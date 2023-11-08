/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       dahuacamera.h
 * @brief      ��������� Function
 *
 * @author     yyf
 * @date       2022/08/18
 * @history
 *****************************************************************************/

#ifndef DAHUACAMERA_H
#define DAHUACAMERA_H

#include <QObject>
#include "GenICam/System.h"
#include "Media/ImageConvert.h"
#include "MessageQue.h"
#include <QImage>
#include <QTime>
#include <QTimer>
#include <QElapsedTimer>
#include <QMutex>
#include <QFileDialog>
#include <QTextCodec>
#include <QFileInfoList>
#include <QFileInfo>

#include "modbust.h"
#include "logwidget.h"

#include "../include/xvlog.h"
#include "../include/xvlogwidget.h"
//#include "mainwindow.h"


/* ֡��Ϣ */
class CFrameInfo : public Dahua::Memory::CBlock
{
public:
    CFrameInfo()
    {
        m_pImageBuf = NULL;
        m_nBufferSize = 0;
        m_nWidth = 0;
        m_nHeight = 0;
        m_ePixelType = Dahua::GenICam::gvspPixelMono8;
        m_nPaddingX = 0;
        m_nPaddingY = 0;
        m_nTimeStamp = 0;
        m_nImage = 0;
    }

    ~CFrameInfo()
    {
    }

public:
    BYTE		*m_pImageBuf;
    int			m_nBufferSize;
    int			m_nWidth;
    int			m_nHeight;
    Dahua::GenICam::EPixelType	m_ePixelType;
    int			m_nPaddingX;
    int			m_nPaddingY;
    uint64_t	m_nTimeStamp;
    const void* m_nImage;
};

using namespace Dahua::GenICam;

class DaHuaCamera : public QObject
{
    Q_OBJECT
public:
    explicit DaHuaCamera(QObject *parent = nullptr);
    ~DaHuaCamera();
    /* ö�ٴ�����ʽ */
    enum ETrigType
    {
        trigContinous = 0,	// ��������
        trigSoftware = 1,	// �������
        trigLine = 2,		// �ⲿ����
    };

    //�����ʼ��
    bool init_Camera();

    QTime time, time1;

public:

    // ȡ���ص�����
    void FrameCallback(const Dahua::GenICam::CFrame & frame);
    // �����
    bool CameraOpen(void);
    // �ر����
    bool CameraClose(void);
    // ��ʼ�ɼ�
    bool CameraStart(void);
    // ֹͣ�ɼ�
    bool CameraStop(void);
    // �л��ɼ���ʽ��������ʽ �������ɼ����ⲿ���������������
    bool CameraChangeTrig(ETrigType trigType);
    // ִ��һ������
    bool ExecuteSoftTrig(void);
    // �����ع�
    bool SetExposeTime(double dExposureTime);
    // ��������
    bool SetAdjustPlus(double dGainRaw);
    // ������Ƶ
    bool SetLineRate(double lineRate);
    // ��ȡ�ع�ֵ
    bool GetExposeTime();
    // ��ȡ����ֵ
    bool GetAdjustPlus();
    // ��ȡ�ع�ֵ
    bool GetLineRate();
    // ���õ�ǰ���
    void SetCemera(const QString& strKey);
    //�������
    void onDeviceLinkNotify(const SConnectArg& conArg);

private slots:

    // ��ʾ�߳�
    void DisplayThreadProc(Dahua::Infra::CThreadLite& lite);

    // ������ʾƵ�ʣ�Ĭ��һ������ʾ30֡
    void setDisplayFPS(int nFPS);

    // �����֡�Ƿ���ʾ
    bool isTimeToDisplay();

    void recvNewFrame(const CFrame& pBuf);

    bool ShowImage(uint8_t* pRgbFrameBuf, int nWidth, int nHeight, uint64_t nPixelFormat);

public:
    //�������
    Dahua::GenICam::ICameraPtr m_pCamera;							// ��ǰ���
    Dahua::GenICam::IStreamSourcePtr m_pStreamSource;				// ������
    IUserSetControlPtr userSet;

    Dahua::Infra::CThreadLite           m_thdDisplayThread;			// ��ʾ�߳�
    TMessageQue<CFrameInfo>				m_qDisplayFrameQueue;		// ��ʾ����

    Dahua::Infra::TVector<Dahua::GenICam::ICameraPtr> m_vCameraPtrList;	// ���ֵ�����б�


    /* ������ʾ֡�� */
    Dahua::Infra::CMutex				m_mxTime;
    int									m_nDisplayInterval;         // ��ʾ���
    uintmax_t							m_nFirstFrameTime;          // ��һ֡��ʱ���
    uintmax_t							m_nLastFrameTime;           // ��һ֡��ʱ���
    QElapsedTimer						m_elapsedTimer;				// ������ʱ��������ʾ֡��

    QImage img;
    bool isCameraConnect;
    bool isImageQueue;
    double exposeTime, gainRaw, lineRate;

};

#endif // DAHUACAMERA_H
