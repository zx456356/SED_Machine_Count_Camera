/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       dahuacamera.h
 * @brief      大华相机管理 Function
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


/* 帧信息 */
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
    /* 枚举触发方式 */
    enum ETrigType
    {
        trigContinous = 0,	// 连续拉流
        trigSoftware = 1,	// 软件触发
        trigLine = 2,		// 外部触发
    };

    //相机初始化
    bool init_Camera();

    QTime time, time1;

public:

    // 取流回调函数
    void FrameCallback(const Dahua::GenICam::CFrame & frame);
    // 打开相机
    bool CameraOpen(void);
    // 关闭相机
    bool CameraClose(void);
    // 开始采集
    bool CameraStart(void);
    // 停止采集
    bool CameraStop(void);
    // 切换采集方式、触发方式 （连续采集、外部触发、软件触发）
    bool CameraChangeTrig(ETrigType trigType);
    // 执行一次软触发
    bool ExecuteSoftTrig(void);
    // 设置曝光
    bool SetExposeTime(double dExposureTime);
    // 设置增益
    bool SetAdjustPlus(double dGainRaw);
    // 设置行频
    bool SetLineRate(double lineRate);
    // 获取曝光值
    bool GetExposeTime();
    // 获取增益值
    bool GetAdjustPlus();
    // 获取曝光值
    bool GetLineRate();
    // 设置当前相机
    void SetCemera(const QString& strKey);
    //相机重连
    void onDeviceLinkNotify(const SConnectArg& conArg);

private slots:

    // 显示线程
    void DisplayThreadProc(Dahua::Infra::CThreadLite& lite);

    // 设置显示频率，默认一秒钟显示30帧
    void setDisplayFPS(int nFPS);

    // 计算该帧是否显示
    bool isTimeToDisplay();

    void recvNewFrame(const CFrame& pBuf);

    bool ShowImage(uint8_t* pRgbFrameBuf, int nWidth, int nHeight, uint64_t nPixelFormat);

public:
    //相机变量
    Dahua::GenICam::ICameraPtr m_pCamera;							// 当前相机
    Dahua::GenICam::IStreamSourcePtr m_pStreamSource;				// 流对象
    IUserSetControlPtr userSet;

    Dahua::Infra::CThreadLite           m_thdDisplayThread;			// 显示线程
    TMessageQue<CFrameInfo>				m_qDisplayFrameQueue;		// 显示队列

    Dahua::Infra::TVector<Dahua::GenICam::ICameraPtr> m_vCameraPtrList;	// 发现的相机列表


    /* 控制显示帧率 */
    Dahua::Infra::CMutex				m_mxTime;
    int									m_nDisplayInterval;         // 显示间隔
    uintmax_t							m_nFirstFrameTime;          // 第一帧的时间戳
    uintmax_t							m_nLastFrameTime;           // 上一帧的时间戳
    QElapsedTimer						m_elapsedTimer;				// 用来计时，控制显示帧率

    QImage img;
    bool isCameraConnect;
    bool isImageQueue;
    double exposeTime, gainRaw, lineRate;

};

#endif // DAHUACAMERA_H
