#include "saveimage.h"

SaveImage::SaveImage(QObject *parent) : QObject(parent)
{

}

void SaveImage::init(QImage qImage, QString savePath)
{
    this->qImage = qImage;
    this->savePath = savePath;
}

void SaveImage::run()
{
    QTime savetime;
    savetime.start();
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    QString savePath1 = savePath + "/" + date.toString("yyyy_MM_dd") + "/"
                        + 111;
    //qDebug()<<savePath1;
    QDir savedir(savePath1);
    if(!savedir.exists())
    {
        qDebug()<<QDir().mkpath(savePath1);
    }

    QString saveName = savePath1 + "/" + time.toString("hh_mm_ss_zzz") + ".JPG";
    //qDebug()<<saveName;
    if(!qImage.save(saveName))
    {
        qDebug()<<"保存图片失败";
        //logBar->logDisplay("警告", "保存图片失败", true, true);
    }
    qDebug()<<"savetime "<<savetime.elapsed();
    qDebug()<<"currentThreadId "<<QThread::currentThreadId();
}

//void SaveImage::drawImage(QImage qImage, QQueue<int> count, QQueue<int> countTem, QQueue<HObject> sortRegion)
//{
//    QTime drawtime;
//    drawtime.start();
//    QPainter p;
//    p.begin(&qImage);
//    //p.setPen(QPen(Qt::green, 2));
//    QFont f;
//    f.setPixelSize(30);
//    f.setBold(true);
//    f.setFamily("微软雅黑");
//    p.setFont(f);

//    //qDebug()<<"wImageIndexCount "<<cp->wImageIndexShow.count();
//    int sortRegionNum, sortRegionNumS;
//    HObject dSortRegion, dSortRegionS;
//    int dImageIndex;
//    int currentCount;


//    if(1)
//    {
//        currentCount = count.dequeue();
//        //sortRegionNum = cp->wSortRegionNum.dequeue();
//        sortRegionNumS = countTem.dequeue();
//        //qDebug()<<sortRegionNumS;
//        for (int i = 0; i < sortRegionNumS; i++)
//        {
//            dSortRegionS = sortRegion.dequeue();
//            RegionFeatures(dSortRegionS, "area", &ho_AreaS);
//            RegionFeatures(dSortRegionS, "outer_radius", &ho_RadiusS);
//            wArea.append(ho_AreaS.D());
//            wRadius.append(ho_RadiusS.D());

//            SmallestRectangle1(dSortRegionS, &hv_Row4, &hv_Column4, &hv_Row5, &hv_Column5);
//            GenRectangle1(&ho_Rectangle, hv_Row4, hv_Column4, hv_Row5, hv_Column5);

//            if(ho_AreaS < set->ui->minArea->value() || ho_AreaS > set->ui->maxArea->value() ||
//                    ho_RadiusS < set->ui->minRadius->value() || ho_RadiusS > set->ui->maxRadius->value())
//            {
//                p.setPen(QPen(Qt::red, 2));
//                //qDebug()<<"QPen red";

//            }
//            else
//            {
//               p.setPen(QPen(Qt::green, 2));
//               //qDebug()<<"QPen green";
//            }

//            p.drawRect(QRect(QPoint(hv_Column4.D(), hv_Row4.D()),
//                             QPoint(hv_Column5.D(), hv_Row5.D())));

//        }


//    }

//    p.setPen(QPen(Qt::red, 2));

//    double minArea, maxArea, minRadius, maxRadius;
//    minArea = 100000000; maxArea = 0; minRadius = 100000000; maxRadius = 0;
//    //qDebug()<<cp->wAreaShow.count();
//    for(int i = 0; i < wArea.count(); i++)
//    {
//        if(wArea.at(i) < minArea)
//        {
//            minArea = wArea.at(i);
//        }
//        if(wArea.at(i) > maxArea)
//        {
//            maxArea = wArea.at(i);
//        }

//        if(wRadius.at(i) < minRadius)
//        {
//            minRadius = wRadius.at(i);
//        }
//        if(wRadius.at(i) > maxRadius)
//        {
//            maxRadius = wRadius.at(i);
//        }
//    }

//    if(minArea == 100000000)
//    {
//        minArea = 0;
//    }
//    if(minRadius == 100000000)
//    {
//        minRadius = 0;
//    }

//    wArea.clear();
//    wRadius.clear();
//    //vg->addText("Area:  " + QString::number(minArea) + "  " + QString::number(maxArea), 25, QPointF(0, 0), QColor(255, 0, 0));
//    //vg->addText("Radius:    " + QString::number(minRadius) + "  " + QString::number(maxRadius), 25, QPointF(0, 50), QColor(255, 0, 0));

//    p.drawText(QPointF(0, 50), "面积:  最小 " + QString::number(minArea) + "(" + QString::number(set->ui->minArea->value()) + ")"
//                                  + "  最大 " + QString::number(maxArea) + "(" + QString::number(set->ui->maxArea->value()) + ")");
//    p.drawText(QPointF(0, 100), "半径:  最小 " + QString::number(minRadius) + "(" + QString::number(set->ui->minRadius->value()) + ")"
//                                   + "  最大 " + QString::number(maxRadius) + "(" + QString::number(set->ui->maxRadius->value()) + ")");
//    p.drawText(QPointF(qImg.width()-300, 50), "当前数量： " + QString::number(currentCount));
//    p.end();

//    if(minArea < set->ui->minArea->value() || maxArea > set->ui->maxArea->value() ||
//        minRadius < set->ui->minRadius->value() || maxRadius > set->ui->maxRadius->value())
//    {
//        isErrorImage = true;
//    }
//    else
//    {
//        isErrorImage = false;
//    }
//    qDebug()<<"drawtime "<<drawtime.elapsed();
//    return qImg;
//}
