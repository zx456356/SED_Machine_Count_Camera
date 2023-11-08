#include "visionregion.h"
#include <QDebug>
#include <QTime>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>

VisionRegion::VisionRegion(VisionItem *parent) : VisionItem(parent)
{

}

VisionRegion::~VisionRegion()
{
    //清空Region数组的内存
    for (size_t i = 0; i< m_vecRegionPair.size(); i++)
    {
        VGRegionPair pair = m_vecRegionPair.at(i);
        pair.region->arrayPointRun.clear();
        delete pair.region;
    }
    m_vecRegionPair.clear();

    if(m_region != nullptr){
        m_region->arrayPointRun.clear();
        delete m_region;
    }
    m_vecLines.clear();
}

void VisionRegion::setRegionData(VGRegion *region, QColor color)
{

    for (size_t i = 0; i< m_vecRegionPair.size(); i++)
    {
        VGRegionPair pair = m_vecRegionPair.at(i);
        pair.region->arrayPointRun.clear();
        delete pair.region;
    }
    m_vecRegionPair.clear();

    if (region != NULL){
        //深拷贝
        if(m_region != nullptr){
            m_region->arrayPointRun.clear();
            delete m_region;
        }
        m_region = new VGRegion();
        for (size_t i = 0; i< region->arrayPointRun.size(); i++)
        {
            VGPointRun pointRun = region->arrayPointRun.at(i);
            m_region->arrayPointRun.push_back(VGPointRun(pointRun.x,pointRun.y,pointRun.length));
        }
        m_region->frameHeight = region->frameHeight;
        m_region->frameWidth = region->frameWidth;
    }


    vector<VGPointRun> vec_point;
    vec_point = m_region->arrayPointRun;

    VGPointRun pointRun;
    QLineF lineF;
    m_vecLines.clear();
    for(unsigned int i=0;i<vec_point.size();i++){
        pointRun = vec_point.at(i);
        lineF.setPoints((QPointF(pointRun.x,pointRun.y)),
                        (QPointF(pointRun.x+pointRun.length,pointRun.y)));
        m_vecLines.append(lineF);
    }
    m_w = m_region->frameWidth;
    m_h = m_region->frameHeight;

    m_regionColor = color;
    this->update();
}

void VisionRegion::setRegionData(vector<VGRegionPair> vec_regionPair)
{
    m_vecRegionPair.clear();
    m_vecLines.clear();
//    m_vecRegionPair = vec_regionPair;

//    //数据深拷贝过来  注意释放
    for (size_t i = 0; i<vec_regionPair.size(); i++)
    {
        VGRegionPair pair = vec_regionPair.at(i);
        VGRegionPair vgPair;
        VGRegion *vgRegion = new VGRegion();
        if (pair.region != NULL){
            //深拷贝
            for (size_t i = 0; i< pair.region->arrayPointRun.size(); i++)
            {
                VGPointRun pointRun = pair.region->arrayPointRun.at(i);
                vgRegion->arrayPointRun.push_back(VGPointRun(pointRun.x,pointRun.y,pointRun.length));
            }
            vgRegion->frameHeight = pair.region->frameHeight;
            vgRegion->frameWidth = pair.region->frameWidth;
        }

        vgPair.color = pair.color;
        vgPair.value = pair.value;
        vgPair.region = vgRegion;
        vgPair.rf = pair.rf;
        vgPair.bShowIndex = pair.bShowIndex;
        vgPair.centerPos = pair.centerPos;
        vgPair.color_index = pair.color_index;

        m_vecRegionPair.push_back(vgPair);
    }

    if(m_vecRegionPair.size() > 0){
        m_w = m_vecRegionPair.at(0).region->frameWidth;
        m_h = m_vecRegionPair.at(0).region->frameHeight;
    }

    this->update();
}

void VisionRegion::addRegionData(VGRegion *region, QColor color)
{
    VGRegionPair pair;
    pair.color = color;
    pair.value = m_vecRegionPair.size();

    VGRegion *vgRegion = new VGRegion();
    if (pair.region != NULL){
        //深拷贝
        for (size_t i = 0; i< region->arrayPointRun.size(); i++)
        {
            VGPointRun pointRun = region->arrayPointRun.at(i);
            vgRegion->arrayPointRun.push_back(VGPointRun(pointRun.x,pointRun.y,pointRun.length));
        }
        vgRegion->frameHeight = pair.region->frameHeight;
        vgRegion->frameWidth = pair.region->frameWidth;
    }
    pair.region = vgRegion;

    m_vecRegionPair.push_back(pair);

    this->update();
}

void VisionRegion::clearRegion()
{
    //清空Region数组的内存
    for (size_t i = 0; i< m_vecRegionPair.size(); i++)
    {
        VGRegionPair pair = m_vecRegionPair.at(i);
        pair.region->arrayPointRun.clear();
        delete pair.region;
    }
    m_vecRegionPair.clear();

    if(m_region != nullptr){
        m_region->arrayPointRun.clear();
        delete m_region;
    }
    m_vecLines.clear();
}

void VisionRegion::setCoordinate_rela(Coordinate_Struct stru)
{
//    QVector<QLineF> vecLines;
//    if(m_vecLines.size() > 0){
//        for(int i=0;i<m_vecLines.size();i++){
//            QLineF lineF = QLineF(this->mapFromScene(m_vecLines.at(i).p1()),this->mapFromScene(m_vecLines.at(i).p2()));
//            vecLines.append(lineF);
//        }
//    }


//    vector<VGPointRun> vec_point;
//    if(m_vecRegionPair.size() > 0){
//        for(int i=0;i<m_vecRegionPair.size();i++){
//            vec_point.clear();
//            vec_point = m_vecRegionPair.at(i).region->arrayPointRun;
//            VGPointRun pointRun;
//            for(int i=0;i<vec_point.size();i++){
//                pointRun = vec_point.at(i);
//                painter->drawLine(this->mapFromScene(QPointF(pointRun.x,pointRun.y).toPoint()),
//                                 this->mapFromScene(QPointF(pointRun.x+pointRun.length,pointRun.y).toPoint()));
//            }
//        }
//    }

    VisionItem::setCoordinate_rela(stru);

//    this->scene()->update();
}

void VisionRegion::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

//    QTime time;
//    time.start();
    painter->setPen(QPen(QColor(0,0,0,0),0));
    painter->setBrush(m_regionColor);
//    QVector<QLineF> vecLines;
    QVector<QRectF> vecRects;
    vecRects.clear();
    if(m_vecLines.size() > 0){
        for(int i=0;i<m_vecLines.size();i++){
//            QLineF lineF = QLineF(this->mapFromScene(m_vecLines.at(i).p1()),this->mapFromScene(m_vecLines.at(i).p2()));
//            vecLines.append(lineF);
//            painter->drawLine(lineF);
            QRectF rf = QRectF(this->mapFromScene(m_vecLines.at(i).p1()),
                               this->mapFromScene(QPointF(m_vecLines.at(i).p2().x()+1,m_vecLines.at(i).p2().y()+1)));
            vecRects.append(rf);
        }
//        painter->drawLines(vecLines);
        painter->drawRects(vecRects);
    }


    vector<VGPointRun> vec_point;
    if(m_vecRegionPair.size() > 0){
        for(unsigned int i=0;i<m_vecRegionPair.size();i++){
            vec_point.clear();
            VGRegionPair pair = m_vecRegionPair.at(i);
            vec_point = pair.region->arrayPointRun;
            painter->setPen(QPen(QColor(0,0,0,0),0));
            painter->setBrush(pair.color);
            VGPointRun pointRun;
            QVector<QRectF> vecRects;
            vecRects.clear();
            for(unsigned int i=0;i<vec_point.size();i++){
                pointRun = vec_point.at(i);
//                painter->drawLine(this->mapFromScene(QPointF(pointRun.x,pointRun.y).toPoint()),
//                                 this->mapFromScene(QPointF(pointRun.x+pointRun.length,pointRun.y).toPoint()));
                QRectF rf = QRectF(this->mapFromScene(QPointF(pointRun.x,pointRun.y).toPoint()),
                                   this->mapFromScene(QPointF(pointRun.x+pointRun.length+1,pointRun.y+1).toPoint()));
                vecRects.append(rf);
            }
            painter->drawRects(vecRects);

            if(pair.bShowIndex){
                //显示编号，位置为区域中心点
                painter->setPen(QPen(pair.color_index,0));
                painter->drawText(this->mapFromScene(QPointF(this->pos().x()+pair.centerPos.x(),
                                                             this->pos().y()+pair.centerPos.y()).toPoint()),QString::number(pair.value));
            }
        }
    }
//    qDebug()<<"111111111111:"<<time.elapsed();
}

QRectF VisionRegion::boundingRect() const
{
    QRectF rf = QRectF(0,0,m_w,m_h);
    return rf;
}

