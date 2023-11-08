/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       countprocess.h
 * @brief      ʵ����ɨ�������� Function
 *
 * @author     yyf
 * @date       2022/08/18
 * @history
 *****************************************************************************/

#ifndef COUNTPROCESS_H
#define COUNTPROCESS_H

#include <QObject>
#include <QImage>
#include <QCoreApplication>
#include <QEventLoop>
#include <QVector>
#include <QQueue>


#include "halconcpp/HalconCpp.h"
#include "halconcpp/HDevThread.h"
#include "dahuacamera.h"
#include "BlobAnalysis.h"
#include "Preprocess.h"
#include "XVBase.h"


using namespace HalconCpp;
using namespace XVL;
extern QMutex  mutex_modbus;

extern modbust *mt;
extern DaHuaCamera *dcam;

extern uint64_t imageTimeStamp;

class CountProcess : public QObject
{
    Q_OBJECT
public:
    CountProcess(Ui::SettingWidget *setWidget);
    ~CountProcess();

    void Sleep(int);

    int     countTem, countTemS, countLast;
    HObject hImageShow;
    HObject ho_SortedRegionsShow, ho_EmptyRegion;
    int  hv_Count, hv_BottleCount, hv_CountShow, hv_Number4Show;
    bool    countThreadSignal;
    bool    grabSignal1, grabSignal2, isModbusCount, isModbusMain;
    int     runtime;
    int     saveNumC;
    QElapsedTimer   timeCountSpeed, timeBottleSpeed;
    int     countSpeed, bottleSpeed, countSpeedM, bottleSpeedM;
    //int     bottleCount;
    int     preProcessIndex, operatorSize;
   // QVector<int> valueCS,valueBS;

    QVector<XVRegion> wStudyRegion;
    QQueue<HObject> wHImage, wImage, wSortRegion, wSortRegionS;
    QQueue<QImage>  wOImage;
    QQueue<int> wImageIndex, wImageIndexShow, wSortRegionNum,wSortRegionNumS, wCount;
    //in setting->recognition parameters
    int  hv_OperatorSize, hv_MinThreshold,  hv_MaxThreshold, hv_MinArea, hv_MaxArea;
    int  hv_MinCircleRadius, hv_MaxCircleRadius, hv_MinFill, hv_MaxFill;
    //in setting->recognition parameters
    int     singleNum, flawAreaMin,flawAreaMax, flawRadiusMin,flawRadiusMax;
    bool    isSaveImage, isStudy, isRemnants,isDoubleRemove;
    QString saveImagePath;
    QString currentMode;
    int     setRuntimeValue,restWarn;
    //in setting->camera parameters
    int     currentNumAddr, singleNumAddr, insertCoordXAddr, insertCoordYAddr, fullSignalAddr, flawSignalAddr;
    int     imageIndex;
    bool bitCount;


    int tubes[9];
    int tubeNumber[8];
    int seY,seCS;

    int cnt = 0;
    QImage showImage;

public slots:
    void count();

    void saveImage(QImage qImage, QString savePath);

private:
    XVImage        _imageUp, _imageDown;
    int            wid, hei;
    QImage         in_img;
    vector<XVImage> _vecImage;

private:
    void CreateXVImage(int , int , uchar *, XVImage *);
    bool QImgToXVImg(QImage ,XVImage &);
    void XVImgToQImg(XVImage , QImage &);
    void CreateBlankXVImage(int , int , XVImage *);
    bool CopyXVImage(XVImage &, XVImage *);
    void PaintXVRegion(XVRegion &, XVImage &, int );
    void ProcessTiledImage(XVImage &, XVSplitRegionToBlobsOut *);
    bool DealwithBlobs(XVSplitRegionToBlobsOut &);
    bool TestRegionIntersection(XVRegion &, XVRegion &);
    void OutRangeWarn(int, int);
    void FlawWarn(int, int);
    void KickoutDouble();
    void DrawMainWindowImage();
    XVImage CropXVImage(XVImage &);
    void OtherThings(QElapsedTimer &);
    bool MirrorXVImage(XVImage &, XVImage *);
    bool TileXVImage(XVImage &, XVImage &, XVImage *);
    XVRegion CreateRectXVRegion(int, int);
    void CountUndCommunication(XVRegion &);

public:
    int GetXVRegionArea(XVRegion &);
    float GetXVRegionRadius(XVRegion &);
};

#endif // COUNTPROCESS_H
