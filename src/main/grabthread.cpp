#include "grabthread.h"
#include <windows.h>
#include "MindVisionCamera/CameraApi.h"
#include <QDebug>

extern tSdkCameraCapbility CameraInfo;
extern int                  pCamera;
extern tSdkFrameHead        pFrameHead;
tSdkImageResolution     *pImageSizeDesc; // 预设分辨率选择
tSdkImageResolution     sResolution;  //获取当前设置到分辨率

extern BYTE* pFrameBuffer;
extern BYTE* pRawData;
extern BYTE* pReadBuffer;

grabThread::grabThread()
{

    isQuit = false;

    for(int i = 0; i < 256; i++)
    {
       grayColourTable.append(qRgb(i, i, i));
    }

}

void grabThread::run()
{
    while(!isQuit)
    {
        if (CameraGetImageBuffer(pCamera,&pFrameHead,&pRawData,2000) == CAMERA_STATUS_SUCCESS)
        {
            CameraImageProcess(pCamera,pRawData,pFrameBuffer,&pFrameHead);
            CameraReleaseImageBuffer(pCamera,pRawData);

//            //获得当前预览的分辨率。
//            pImageSizeDesc=CameraInfo.pImageSizeDesc;
//            CameraGetImageResolution(pCamera,&sResolution);

//            int img_width = pImageSizeDesc[sResolution.iIndex].iWidth;
//            int img_height = pImageSizeDesc[sResolution.iIndex].iHeight;
//            int img_size= img_width * img_height;

            int img_width = pFrameHead.iWidth;
            int img_height = pFrameHead.iHeight;
            int img_size = img_width * img_height;

            if(pFrameHead.uiMediaType==CAMERA_MEDIA_TYPE_MONO8)
            {
                memcpy(pReadBuffer,pFrameBuffer,img_size);

                QImage img(pReadBuffer, img_width, img_height, QImage::Format_Indexed8);
                img.setColorTable(grayColourTable);
                emit sendImage(img);
            }
            else
            {
                memcpy(pReadBuffer,pFrameBuffer,img_size*3);

                QImage img = QImage((const uchar*)pReadBuffer, img_width, img_height, QImage::Format_RGB888);
                emit sendImage(img);
            }


        }
        else
        {
            printf("timeout \n");
            usleep(1000);
        }
    }
}

void grabThread::quit()
{
    isQuit = true;
}
