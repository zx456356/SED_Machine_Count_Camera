#include "visioncrosspointitem.h"
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "../control/color.h"

VisionCrossPointItem::VisionCrossPointItem(bool edit, qreal length, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor, VisionItem *parent) : VisionItem(parent)
{
    if(color_enable){
        m_borderColor = borderColor;
    }else{
        m_borderColor = borderColor;
    }
    m_brushColor = brushColor;
    m_selectedColor = selectedColor;
    m_bEdit = edit;
    m_length = length;
    if(m_bEdit){
        setSelectedStatus(true);
    }else{
        setSelectedStatus(false);
    }
    setAcceptHoverEvents(true);
    m_type = ItemType::Paint_CrossPoint;
}

VisionCrossPointItem::VisionCrossPointItem(QPointF pointF, VisionItem *parent) : VisionItem(parent)
{
    m_pointF = pointF;
    setAcceptHoverEvents(true);
    m_type = ItemType::Paint_CrossPoint;
}

VisionCrossPointItem::VisionCrossPointItem(qreal x, qreal y, VisionItem *parent) : VisionItem(parent)
{
    m_pointF = QPointF(x,y);
    setAcceptHoverEvents(true);
    m_type = ItemType::Paint_CrossPoint;
}

void VisionCrossPointItem::setPoint(qreal x, qreal y)
{
    m_pointF = QPointF(x,y);
//    //转换数据
    this->setPos(x,y);
}

void VisionCrossPointItem::setPoint(QPointF pointF)
{
    m_pointF = pointF;
//    //转换数据
    this->setPos(m_pointF);
}

QPointF VisionCrossPointItem::getPoint()
{
    return m_pointF;
}

bool VisionCrossPointItem::getPosInArea(qreal x, qreal y)
{
    if(boundingRect().contains(x,y)){
        return true;
    }else{
        return false;
    }
}

QVector<QPointF> VisionCrossPointItem::getPoints()
{
    QVector<QPointF> vec_p;
    vec_p.append(m_pointF);
    return vec_p;
}

VGPoint2D VisionCrossPointItem::getData(){
    //转换数据
    Coordinate_Struct stru;
    stru.angle = 0;
    stru.dx = 0;
    stru.dy = 0;
    stru.scale = 1;

    QPointF pointF = m_pointF;
    pointF = convert_coordinate(m_itemCoordinate,stru,pointF);


    VGPoint2D point2D;
    point2D.optional = VG_ENABLE;
    point2D.x = pointF.x();
    point2D.y = pointF.y();
    return point2D;
}

#include <QtMath>
const qreal deg2rad = qreal(0.017453292519943295769);        // pi/180
#define Pi 3.1415926
void VisionCrossPointItem::setCoordinate_rela(Coordinate_Struct stru)
{
    double pre_dx = m_itemCoordinate.dx;
    double pre_dy = m_itemCoordinate.dy;
    double pre_angle = m_itemCoordinate.angle;

    qreal dx0 = stru.dx - pre_dx;
    qreal dy0 = stru.dy - pre_dy;
    Q_UNUSED(dx0)
    Q_UNUSED(dy0)


    //dx dy 表示坐标系原点，

    //平移 -- 先计算出点在新的坐标系中的点的坐标  点当前的坐标是之前的坐标系中的点，需要转换为新的坐标系的点
    m_pointF = QPointF(m_pointF.x()+(stru.dx-pre_dx),m_pointF.y()+(stru.dy-pre_dy));

    //Qt的源码计算，求某一个角度的sin和cos值
//    qreal a = stru.angle;
//    qreal sina = 0;
//    qreal cosa = 0;
//    if (a == 90. || a == -270.)
//        sina = 1.;
//    else if (a == 270. || a == -90.)
//        sina = -1.;
//    else if (a == 180.)
//        cosa = -1.;
//    else{
//        qreal b = deg2rad*a;                        // convert to radians
//        sina = qSin(b);               // fast and convenient
//        cosa = qCos(b);
//    }

    //相对坐标的旋转基于上一次的坐标
    double a = stru.angle - pre_angle;  //永远基于初始角度（0）的旋转
    double len = hypot((m_pointF.x()-stru.dx),(m_pointF.y()-stru.dy));

    if(len == 0){
        //原点切换--旋转则没必要
        return;
    }

    double b = acos((double)(m_pointF.x()-stru.dx)/len);
    if((m_pointF.y()-stru.dy) < 0)
        b = 2*Pi - b;

    b = b / deg2rad;
    a = a + b;
    qreal sina = 0;
    qreal cosa = 0;
    if (a == 90. || a == -270.)
        sina = 1.;
    else if (a == 270. || a == -90.)
        sina = -1.;
    else if (a == 180.)
        cosa = -1.;
    else{
        qreal c = deg2rad*a;                        // convert to radians
        sina = qSin(c);               // fast and convenient
        cosa = qCos(c);
    }
    qreal dx = len*cosa;
    qreal dy = len*sina;
    //上述求到的是基于点(stru.x,stru.y)，旋转角度为stru.angle的点坐标系，但是我们显示的是需要显示到基于(0,0)的坐标中的

    m_pointF = QPointF(dx+stru.dx,dy+stru.dy);


    //缩放

    VisionItem::setCoordinate_rela(stru);
    this->setPos(m_pointF);
    this->scene()->update();
}

QRectF VisionCrossPointItem::boundingRect() const
{
    QRectF rf = QRectF(-m_length*(1/this->scene()->views().at(0)->matrix().m22()),-m_length*(1/this->scene()->views().at(0)->matrix().m22()),2*m_length*(1/this->scene()->views().at(0)->matrix().m22()),2*m_length*(1/this->scene()->views().at(0)->matrix().m22()));
    return rf;
}

void VisionCrossPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    if(option->state & QStyle::State_Selected){
        painter->setPen(QPen(QBrush(m_selectedColor),g_penWidth*(1/this->scene()->views().at(0)->matrix().m22())));
        setSelectedStatus(true);
    }else{
        painter->setPen(QPen(QBrush(m_borderColor),g_penWidth*(1/this->scene()->views().at(0)->matrix().m22())));
        setSelectedStatus(false);
    }

//    painter->setPen(QPen(QBrush(QColor(255,0,0)),0));
    painter->drawLine(QPointF(0,-m_length*(1/this->scene()->views().at(0)->matrix().m22())),QPointF(0,0+m_length*(1/this->scene()->views().at(0)->matrix().m22())));
    painter->drawLine(QPointF(-m_length*(1/this->scene()->views().at(0)->matrix().m22()),0),QPointF(m_length*(1/this->scene()->views().at(0)->matrix().m22()),0));

}

void VisionCrossPointItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    if(boundingRect().contains(event->scenePos())){
//        qDebug()<<"in area";
        setSelectedStatus(true);
    }else{
//        qDebug()<<"out area";
        setSelectedStatus(false);
    }

    this->scene()->update();
}

void VisionCrossPointItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    this->setPoint(event->scenePos());
    this->scene()->update();
}

void VisionCrossPointItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    if(!boundingRect().contains(QPointF(event->scenePos().x(),event->scenePos().y()))){
        emit signal_clicked(this,true,true,event->scenePos().x(),event->scenePos().y());
        return;
    }
    emit signal_clicked(this,true,false,event->scenePos().x(),event->scenePos().y());
    QGraphicsItem::mouseReleaseEvent(event);

}
