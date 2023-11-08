#include "countprocess.h"
#include <vector>
#include <numeric>

QMutex  mutex_modbus;
modbust *mt;
DaHuaCamera *dcam;

uint64_t imageTimeStamp;
#define CON_IMAGE_NUM     1

CountProcess::CountProcess(Ui::SettingWidget *setWidget)
{
    mt = new modbust(setWidget);
    dcam = new DaHuaCamera(this);

qRegisterMetaType<QVector<int>>("QVector<int>");

    singleNum = setWidget->singleButtleQuantity->value();
    currentNumAddr = setWidget->currentNumAddr->value();
    singleNumAddr = setWidget->singleNumAddr->value();
    insertCoordXAddr = setWidget->insertCoordXAddr->value();
    insertCoordYAddr = setWidget->insertCoordYAddr->value();
    fullSignalAddr = setWidget->fullSignalAddr->value();
    flawSignalAddr = setWidget->flawSignalAddr->value();

    //saveImagePath = setWidget->saveImgPath->text();
    setRuntimeValue = 0;
    operatorSize = 1;
    hv_MinThreshold = 0;
    hv_MaxThreshold = 0;
    hv_MinArea = 0;
    hv_MaxArea = 0;
    hv_MinCircleRadius = 0;
    hv_MaxCircleRadius = 0;
    hv_MinFill = 0;
    hv_MaxFill = 0;
    flawAreaMin = 0;
    flawAreaMax = 0;
    flawRadiusMin = 0;
    flawRadiusMax = 0;

    imageTimeStamp = 0;
    hv_Count = 0;
    hv_BottleCount = 0;
    countTem = 0;
    countTemS = 0;
    countLast = 0;
    preProcessIndex = 0;
    operatorSize = 0;

    grabSignal1 = false;
    grabSignal2 = false;
    isSaveImage = false;
    isStudy = false;
    isRemnants = false;
    imageIndex = 0;

    countSpeed = 0;
    countSpeedM = 0;
    bottleSpeed = 0;
    bottleSpeedM = 0;
    timeCountSpeed.start();
    timeBottleSpeed.start();


    tubes[0] = 0;
    tubes[8] = 1640;
    for (int var = 0; var < 8; ++var)
    {//创建料道信号
        tubes[var + 1] = tubes[var] + (1640 / 8);
        tubeNumber[var] = 0;
    }    

}

CountProcess::~CountProcess()
{
    delete dcam;
    delete mt;
}

/**
 * @brief 计数函数
 */
void CountProcess::count()
{

    while(countThreadSignal && dcam->isCameraConnect)
    {
        QElapsedTimer time1;
        time1.start();
        CFrameInfo info;
        QMutexLocker locker(&mutex_modbus);

        if (dcam->m_qDisplayFrameQueue.get(info,50))
        {
            XVImage mirrord_image;
            XVImage tiled_image;
            XVSplitRegionToBlobsOut blobs;

            wid = info.m_nWidth;
            hei = info.m_nHeight;
            CreateXVImage(wid, hei, info.m_pImageBuf, &_imageUp);
            free(info.m_pImageBuf);

            MirrorXVImage(_imageUp, &mirrord_image);
            if(_imageDown.width != wid || _imageDown.height != hei){
                CreateBlankXVImage(wid, hei, &_imageDown);
            }
            TileXVImage(mirrord_image, _imageDown, &tiled_image);
            ProcessTiledImage(tiled_image, &blobs);
            if(DealwithBlobs(blobs)){
                KickoutDouble();
                OtherThings(time1);
            }
        }
        else Sleep(1);
    }
}

bool CountProcess::QImgToXVImg(QImage Qimg,XVImage &XVimg)
{
    if(Qimg.bits() == nullptr)
        return false;
    XVimg.depth = Qimg.depth() / 8;
    XVimg.width = Qimg.width();
    XVimg.height = Qimg.height();
    size_t size = XVimg.width * XVimg.height * XVimg.depth;
    XVimg.type = UInt8;
    XVimg.data = (uchar*)malloc(size);
    XVimg.pitch = (XVimg.width * XVimg.depth * 1 + 3) / 4 * 4;
    memcpy(XVimg.data,Qimg.bits(),size);
    return true;
}

void CountProcess::XVImgToQImg(XVImage XVimg, QImage &Qimg)
{
    QImage::Format format;
    if(XVimg.depth == 1)
    {
        format = QImage::Format_Grayscale8;
    }
    else if(XVimg.depth == 3)
    {
        format = QImage::Format_RGB888;
    }
    else
    {
        Q_ASSERT(false);
    }
    Qimg = QImage(XVimg.data,XVimg.width,XVimg.height,XVimg.pitch,format);
}

void CountProcess::CreateXVImage(int width, int height, uchar *data, XVImage *img)
{
    img->width = width;
    img->height = height;
    img->type = UInt8;
    img->depth = 1;
    img->pitch = (width + 3) / 4 * 4;
    size_t size = width * height * sizeof(uchar);
    img->data = (uchar*)malloc(size);
    memcpy(img->data, data, size);
}

void CountProcess::CreateBlankXVImage(int width, int height, XVImage *img)
{
    size_t size = width * height * _imageUp.depth;
    img->data = (uchar*)malloc(size);
    memset(img->data, 255, size);
    img->width = width;
    img->height = height;
    img->type = _imageUp.type;
    img->depth = _imageUp.depth;
    img->pitch = _imageUp.pitch;
}

bool CountProcess::CopyXVImage(XVImage &img1, XVImage *img2)
{
    if(img1.data == nullptr) return false;
    img2->width = img1.width;
    img2->height = img1.height;
    img2->type = img1.type;
    img2->pitch = img1.pitch;
    img2->depth = img1.depth;
    size_t  size = img1.width * img1.height * img1.depth;
    img2->data = (uchar *)malloc(size);
    if(img2->data){
        memcpy(img2->data, img1.data, size);
        return true;
    }
    return false;
}

void CountProcess::PaintXVRegion(XVRegion &region, XVImage &image, int val)
{
    XVSetImagePixelsIn set_in;
    XVSetImagePixelsOut set_out;
    set_in.inRoi = region;
    set_in.inImage = &image;
    set_in.inPixel.ch1 = val;
    set_in.inPixel.ch2 = 0;
    set_in.inPixel.ch3 = 0;
    set_in.inPixel.ch4 = 0;

    if(XVSetImagePixels(set_in, set_out) == 0){
        free(image.data);
        XVImage image = set_out.outImage;
        CopyXVImage(image, &_imageDown);
        free(image.data);
    }
}

bool CountProcess::TestRegionIntersection(XVRegion &reg1, XVRegion &reg2)
{
    XVRegionIntersectionIn in;
    XVRegionIntersectionOut out;
    in.inRegion1 = reg1;
    in.inRegion2 = reg2;
    XVRegionIntersection(in, out);

    return out.outRegion.frameWidth > 0 ? true : false;
}

void CountProcess::OutRangeWarn(int area, int rad)
{
    Log::Instance()->writeWarn("出现未计入数据的阴影，面积= " +
                               QString::number(area)+ "(" +
                               QString::number(hv_MinArea) + "," +
                               QString::number(hv_MaxArea) + ")" + "，半径= " +
                               QString::number(rad) + "(" +
                               QString::number(hv_MinCircleRadius) + "," +
                               QString::number(hv_MaxCircleRadius) + ")");
}

void CountProcess::FlawWarn(int area, int rad)
{
    if((area < flawAreaMax && area > flawAreaMin) ||
       (rad < flawRadiusMax && rad > flawRadiusMin) ||
       ((area > hv_MaxArea) || (rad  > hv_MaxCircleRadius))){
        isRemnants = true;
        Log::Instance()->writeWarn("残料警告,面积= " +
                                   QString::number(area) + "(" +
                                   QString::number(flawAreaMin) + "," +
                                   QString::number(flawAreaMax)  + ")" + "，半径= " +
                                   QString::number(rad) + "(" +
                                   QString::number(flawRadiusMin) + "," +
                                   QString::number(flawRadiusMax) + ")");
    }
}

void CountProcess::ProcessTiledImage(XVImage &tiled_image, XVSplitRegionToBlobsOut *blobs)
{
    XVRectangleRegionIn rect_in;
    XVRectangleRegionOut rect_out;
    rect_in.inRectangle.origin.x = 0;
    rect_in.inRectangle.origin.y = 0;
    rect_in.inRectangle.width = wid;
    rect_in.inRectangle.height = hei * 2;
    rect_in.inRectangle.angle = 0;
    rect_in.inAlignment.optional = XVOptionalType::NUL;
    rect_in.inFrameWidth = wid;
    rect_in.inFrameHeight = hei * 2;
    XVRectangleRegion(rect_in, rect_out);

    XVThresholdImageToRegionMonoIn thre_in;
    XVThresholdImageToRegionMonoOut thre_out;
    thre_in.inImage = &tiled_image;
    thre_in.inMin = hv_MinThreshold;
    thre_in.inMax = hv_MaxThreshold;
    thre_in.inAlignment.optional = XVOptionalType::NUL;
    thre_in.inRegion = rect_out.outRegion;
    if(XVThresholdImageToRegionMono(thre_in, thre_out) == 0)
        free(tiled_image.data);

    XVRegionMorphIn morph_in;
    XVRegionMorphOut morph_out;
    morph_in.inRegion = thre_out.outRegion;
    morph_in.inRadiusX = 1;
    morph_in.inRadiusY = 1;
    switch (preProcessIndex)
    {
    case 0:
        morph_in.inKernel = XVMorphShape::Cross;
        morph_in.inMorphType = XVMorphType::Open;
        XVRegionMorph(morph_in, morph_out);
        break;
    case 1:
        morph_in.inKernel = XVMorphShape::Rect;
        morph_in.inMorphType = XVMorphType::Open;
        XVRegionMorph(morph_in, morph_out);
        break;
    case 2:
        morph_in.inKernel = XVMorphShape::Cross;
        morph_in.inMorphType = XVMorphType::Close;
        XVRegionMorph(morph_in, morph_out);
        break;
    case 3:
        morph_in.inKernel = XVMorphShape::Rect;
        morph_in.inMorphType = XVMorphType::Close;
        XVRegionMorph(morph_in, morph_out);
        break;
    default:break;
    }

    XVFillRegionHolesIn fill_in;
    XVFillRegionHolesOut fill_out;
    fill_in.inRegion = morph_out.outRegion;
    XVFillRegionHoles(fill_in, fill_out);

    XVSplitRegionToBlobsIn split_in;
    split_in.inRegion = fill_out.outRegion;
    XVSplitRegionToBlobs(split_in, *blobs);
}

bool CountProcess::DealwithBlobs(XVSplitRegionToBlobsOut &blobs)
{
    int n_region = blobs.outRegions.size();

    if(n_region == 0){
        free(_imageUp.data);
        return false;
    }
    DrawMainWindowImage();
    for(int i = 0; i != n_region; ++i){
        XVRegion reg = blobs.outRegions.at(i);
        XVRegion rect_reg = CreateRectXVRegion(wid, 1);

        if(TestRegionIntersection(reg, rect_reg)){
            PaintXVRegion(reg, _imageDown, 20);
            continue;
        }
        if(isStudy){//向学习功能传递参数
            wStudyRegion.append(reg);
        }
        else{
            CountUndCommunication(reg);
        }
    }
    return true;
}

void CountProcess::KickoutDouble()
{
    for (int i = 0; i < 9; ++i){
        int cnt = hv_Count;
        if(singleNum - cnt <= restWarn && tubeNumber[i] > 1){
            isDoubleRemove = true;
            Log::Instance()->writeWarn("剔除警告：第 " + QString::number(i + 1) +
                                       "料道出现叠料,数目为：" + QString::number(tubeNumber[i]) + "粒");
        }
        tubeNumber[i] = 0;
    }
}

void CountProcess::DrawMainWindowImage()
{
    XVImgToQImg(_imageUp, in_img);
    static QImage largeImage = QImage(wid, CON_IMAGE_NUM * hei, in_img.format());
    QPainter painter(&largeImage);
    if(cnt < CON_IMAGE_NUM){
        painter.drawImage(QPoint(0, hei * cnt), in_img);
        free(_imageUp.data);
        ++cnt;
    }
    if(cnt >= CON_IMAGE_NUM){
        grabSignal2 = false;
        showImage = largeImage;
        grabSignal1 = true;
        grabSignal2 = true;
        cnt = 0;
    }
}

XVImage CountProcess::CropXVImage(XVImage &image)
{
    XVRectangleRegionIn crop_region_in;
    XVRectangleRegionOut crop_region_out;
    crop_region_in.inRectangle.origin.x = 0;
    crop_region_in.inRectangle.origin.y = 0;
    crop_region_in.inRectangle.width = wid;
    crop_region_in.inRectangle.height = hei;
    crop_region_in.inRectangle.angle = 0;
    crop_region_in.inAlignment.optional = XVOptionalType::NUL;
    crop_region_in.inFrameWidth = wid;
    crop_region_in.inFrameHeight = hei;
    XVRectangleRegion(crop_region_in, crop_region_out);

    XVCopyAndFillIn copy_in;
    XVCopyAndFillOut copy_out;
    copy_in.inImage = image;
    copy_in.inRoi = crop_region_out.outRegion;
    copy_in.inCopyAndFillType = CopyAndFillType::Copy;
    copy_in.alignment.optional = XVOptionalType::NUL;
    XVCopyAndFill(copy_in, copy_out);
    return copy_out.outImage;
}

void CountProcess::OtherThings(QElapsedTimer& timer)
{
    countLast = hv_Count;
    if(hv_Count >= singleNum && !isStudy)
    {
        hv_Count = hv_Count - singleNum;
        bottleSpeedM++;
    }
    if(!isStudy && mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
    {
        mt->isModbusCount = true;
        modbus_write_register(mt->modbus, currentNumAddr, hv_Count);
        mt->isModbusCount = false;
    }

    if(isSaveImage)
    {
        wImage.enqueue(hImageShow);
        wCount.enqueue(hv_Count);
        wSortRegionNumS.enqueue(countTemS);
        countTem = 0;
        countTemS = 0;
    }
    if(!isStudy && countLast >= singleNum && mt->modbus_state == true){
        if(mt->isModbusMdu == false && mt->isModbusMain == false){
            mt->isModbusCount = true;
            modbus_write_bit(mt->modbus, fullSignalAddr, 1);
            modbus_write_bit(mt->modbus, flawSignalAddr, isRemnants);
            if(isDoubleRemove == true){
                modbus_write_bit(mt->modbus, 330, isDoubleRemove);
            }
            uint16_t d62[1];
            modbus_read_registers(mt->modbus,62,1,&d62[0]);
            bottleSpeed = (int)d62[0];

            if(setRuntimeValue > runtime){
                Sleep(setRuntimeValue - runtime);
            }
            runtime = timer.elapsed();
            isRemnants = false;
            mt->isModbusCount = false;
            isDoubleRemove =false;
        }
    }
    if(timeCountSpeed.elapsed() >= 1000){
        countSpeed = countSpeedM;
        countSpeedM = 0;
        timeCountSpeed.start();
    }
    if(timeBottleSpeed.elapsed() >= 60000){
        bottleSpeedM = 0;
        timeBottleSpeed.start();
    }
}

bool CountProcess::MirrorXVImage(XVImage &in, XVImage *out)
{
    XVGeometricTransformationIn tran_in;
    XVGeometricTransformationOut tran_out;
    tran_in.inImage = &in;
    tran_in.inMirrorType = XVMirrorType::VerticalMirror;
    tran_in.inTransformationType = XVTransformationType::Mirror;
    if(XVGeometricTransformation(tran_in, tran_out) == 0){
        *out = tran_out.outImage;
        return true;
    }
    return false;
}

bool CountProcess::TileXVImage(XVImage &in1, XVImage &in2, XVImage *out)
{
    XVTileImageOffsetIn tile_in;
    XVTileImageOffsetOut tile_out;
    tile_in.inImgs.push_back(in1);
    tile_in.inImgs.push_back(in2);
    if(XVTileImageOffset(tile_in, tile_out) == 0){
        *out = tile_out.outImage;
        free(in1.data);
        XVRegion rect = CreateRectXVRegion(wid, hei);
        PaintXVRegion(rect, _imageDown, 255);
        return true;
    }
    return false;
}

XVRegion CountProcess::CreateRectXVRegion(int width, int height)
{
    XVRectangleRegionIn rect_in;
    XVRectangleRegionOut rect_out;
    rect_in.inRectangle.origin.x = 0;
    rect_in.inRectangle.origin.y = 0;
    rect_in.inRectangle.width = width;
    rect_in.inRectangle.height = height;
    rect_in.inRectangle.angle = 0;
    rect_in.inAlignment.optional = XVOptionalType::NUL;
    rect_in.inFrameWidth = width;
    rect_in.inFrameHeight = height;
    XVRectangleRegion(rect_in, rect_out);

    return rect_out.outRegion;
}

void CountProcess::CountUndCommunication(XVRegion &reg)
{
    int n_untop = 0;
    uint16_t row[20] = {0};
    uint16_t column[20] = {0};
    uint16_t clear[20] = {0};
    int area = GetXVRegionArea(reg);
    int rad = GetXVRegionRadius(reg);

    if((area >= hv_MinArea && area <= hv_MaxArea) &&
       (rad >= hv_MinCircleRadius && rad <= hv_MaxCircleRadius)){
        if(!isStudy){
            ++hv_Count;
            ++countSpeedM;

            XVRegionBoundingRectIn bound_in;
            XVRegionBoundingRectOut bound_out;
            bound_in.inRegion = reg;
            XVRegionBoundingRect(bound_in, bound_out);

            //need to check
            row[n_untop] = bound_out.outCenter.x;
            column[n_untop] = bound_out.outRightDown.y;

            for (int i = 0; i < 8; ++i){
                if(row[n_untop] > tubes[i] && row[n_untop] < tubes[i + 1]){
                    tubeNumber[i] ++;
                }
            }
            if(!isStudy && mt->modbus_state == true && mt->isModbusMdu == false && mt->isModbusMain == false)
            {
                mt->isModbusCount = true;
                modbus_write_registers(mt->modbus, insertCoordXAddr + n_untop, 1, &row[n_untop]);
                modbus_write_registers(mt->modbus, insertCoordYAddr + n_untop, 1, &column[n_untop]);
                modbus_write_registers(mt->modbus, insertCoordYAddr + n_untop + 1, 20 - n_untop, &clear[n_untop]);
                modbus_write_registers(mt->modbus, insertCoordXAddr + n_untop + 1, 20 - n_untop, &clear[n_untop]);
                modbus_write_register(mt->modbus, 3, n_untop + 1);
                modbus_write_bit(mt->modbus, 1000, 1);
                mt->isModbusCount = false;
            }
            n_untop++;
        }
    }
    else OutRangeWarn(area, rad);
    FlawWarn(area, rad);
}

int CountProcess::GetXVRegionArea(XVRegion &region)
{
    XVRegionAreaIn area_in;
    XVRegionAreaOut area_out;
    area_in.inRegion = region;
    XVRegionArea(area_in, area_out);

    return area_out.outArea;
}

float CountProcess::GetXVRegionRadius(XVRegion &region)
{
    XVRegionBoundingCircleIn circle_in;
    XVRegionBoundingCircleOut circle_out;
    circle_in.inRegion = region;
    XVRegionBoundingCircle(circle_in, circle_out);

    return circle_out.outCircle.radius;
}

/**
 * @brief 保存图片
 * @param qImage    要保存的图片
 * @param savePath  保存路径
 */
void CountProcess::saveImage(QImage qImage, QString savePath)
{
    QElapsedTimer savetime;
    savetime.start();
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    QString savePath1 = savePath + "/" + date.toString("yyyy_MM_dd") + "/"
                        + currentMode;
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
        logBar->logDisplay(QStringLiteral("警告"), QStringLiteral("保存图片失败"), true, true);
    }
    //WriteImage(wHImage.dequeue(), "jpeg", 0, savePath1.toStdString().c_str());
    qDebug()<<"savetime "<<savetime.elapsed();
}

/**
 * @brief 延时函数
 * @param msec  延时时间（ms）
 */
void CountProcess::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    //qDebug()<<"dieTime"<<QTime::currentTime();
    while( QTime::currentTime() < dieTime )
    {
        //QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    //qDebug()<<"sleeptime"<<QTime::currentTime();

}
