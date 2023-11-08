#include "visionitem.h"
#include <QDebug>
//#include "../visiongraphview.h"



#include <QtMath>
const qreal Deg2rad = qreal(0.017453292519943295769);        // pi/180
#define Pi 3.1415926

QPointF convert_coordinate(Coordinate_Struct stru_pre,Coordinate_Struct stru,QPointF pointF)
{
    double pre_dx = stru_pre.dx;
    double pre_dy = stru_pre.dy;
    double pre_angle = stru_pre.angle;

    qreal dx0 = stru.dx - pre_dx;
    qreal dy0 = stru.dy - pre_dy;
    Q_UNUSED(dx0)
    Q_UNUSED(dy0)

    //dx dy 表示坐标系原点，

    //平移 -- 先计算出点在新的坐标系中的点的坐标  点当前的坐标是之前的坐标系中的点，需要转换为新的坐标系的点
    pointF = QPointF(pointF.x()+(stru.dx-pre_dx),pointF.y()+(stru.dy-pre_dy));

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
//        qreal b = Deg2rad*a;                        // convert to radians
//        sina = qSin(b);               // fast and convenient
//        cosa = qCos(b);
//    }

    //相对坐标的旋转基于上一次的坐标
    double a = stru.angle - pre_angle;  //永远基于初始角度（0）的旋转
    double len = hypot((pointF.x()-stru.dx),(pointF.y()-stru.dy));
    if(len == 0){
        //原点切换--旋转则没必要
        return pointF;
    }
    double b = acos((double)(pointF.x()-stru.dx)/len);
    if((pointF.y()-stru.dy) < 0)
        b = 2*Pi - b;

    b = b / Deg2rad;
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
        qreal c = Deg2rad*a;                        // convert to radians
        sina = qSin(c);               // fast and convenient
        cosa = qCos(c);
    }
    qreal dx = len*cosa;
    qreal dy = len*sina;
    //上述求到的是基于点(stru.x,stru.y)，旋转角度为stru.angle的点坐标系，但是我们显示的是需要显示到基于(0,0)的坐标中的

    pointF = QPointF(dx+stru.dx,dy+stru.dy);

    return pointF;
}

VisionItem::VisionItem(QGraphicsItem *parent):QGraphicsItem(parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
}

void VisionItem::setCoordinate_rela(Coordinate_Struct stru)
{
    /*
        m_itemCoordinate.dx = stru.dx + m_itemCoordinate.dx;
        m_itemCoordinate.dy = stru.dy + m_itemCoordinate.dy;
        m_itemCoordinate.angle = stru.angle + m_itemCoordinate.angle;

        QTransform form;
        form.translate(m_itemCoordinate.dx,m_itemCoordinate.dy);
        form.rotate(m_itemCoordinate.angle);
        form.scale(m_itemCoordinate.scale,m_itemCoordinate.scale);
//        this->setTransform(transform().translate(stru.dx,stru.dy));
//        this->setRotation(stru.angle);
//        this->setScale(stru.scale);
        this->setTransform(form);
        */
    //设置坐标系后，对每个item内部数据进行转换处理，得到的基于原始坐标系的相对坐标系数据，
    //此时只是修改数据，实际坐标系还是原始坐标系，但是数据以及变成了相对坐标系
    //需要注意 的是，获取数据给予的数据是基于原始坐标系的数据

//    QVector<QPointF> vec_p = this->getPoints();
//    foreach (QPointF point, vec_p) {
//        convert_coordinate(m_itemCoordinate,stru,point);
//    }
    m_itemCoordinate = stru;

}

void VisionItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    //    qDebug()<<"visionItem mousePressEvent";
    if(!m_bEdit)
        return;

    setSelectedStatus(true);
}

void VisionItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit signal_hoverLeaveEvent(this);
    QGraphicsItem::hoverLeaveEvent(event);
    event->ignore();   //sceneEvent是拦截事件，调用ignore和accept都是无效的
}

void VisionItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit signal_hoverEnterEvent(this);
    QGraphicsItem::hoverEnterEvent(event);
    event->ignore();   //sceneEvent是拦截事件，调用ignore和accept都是无效的
}

