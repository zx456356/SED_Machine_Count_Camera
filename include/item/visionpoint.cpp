#include "visionpoint.h"
#include "../control/color.h"

#include <QGraphicsScene>
#include <QGraphicsView>

VisionPoint::VisionPoint(bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor, VisionItem *parent) : VisionItem(parent)
{
    m_type = ItemType::Paint_Point;
    if(color_enable){
        m_borderColor = borderColor;
    }else{
        m_borderColor = borderColor;
    }
    m_brushColor = brushColor;
    m_selectedColor = selectedColor;
    setEnabled(false);
    setFlag(QGraphicsItem::ItemIsMovable,false);
    setFlag(QGraphicsItem::ItemIsSelectable,false);
}

void VisionPoint::setPointF(QPointF pointF)
{
    m_style = SINGLE;
    m_pointF = pointF;
}

void VisionPoint::setPointFs(QList<QPointF> lstP)
{
    if(lstP.count() <= 0){
        m_pointF = QPointF(0,0);
        m_style = SINGLE;

    }else if(lstP.count() == 1){
        m_pointF = lstP.first();
        m_style = SINGLE;

    }else{
        m_lstPointF = lstP;
        m_style = MULTI;

    }
}

VGPoint2D VisionPoint::getData(){
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

QVector<QPointF> VisionPoint::getPoints(){
    QVector<QPointF> vec_p;
    if(m_style == MULTI){
        for(int i=0;i<m_lstPointF.count();i++){
            vec_p.append(m_lstPointF[i]);
        }
    }else{
        vec_p.append(m_pointF);
    }
    return vec_p;
}

bool VisionPoint::getPosInArea(qreal x, qreal y)
{
    Q_UNUSED(x)
    Q_UNUSED(y)
    return false;
}

void VisionPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen = QPen(m_borderColor,g_penWidth*(1/this->scene()->views().at(0)->matrix().m22()));
    painter->setPen(pen);
//    painter->setBrush(Qt::red);
//    painter->drawEllipse(m_pointF,1,1);
//    painter->drawEllipse(QPointF(m_pointF.x()+2,m_pointF.y()),1,1);
    if(m_style == SINGLE){
        painter->drawPoint(m_pointF);
    }else{
        painter->drawPoints(m_lstPointF.toVector());
    }
//    painter->drawRect(boundingRect());
}

QRectF VisionPoint::boundingRect() const
{
    if(m_style == SINGLE){
        return QRectF(m_pointF-QPointF(1,1),m_pointF+QPointF(1,1));
    }else{
        QPolygonF polyF;
        polyF.append(m_lstPointF.toVector());
        return polyF.boundingRect();
        return QRectF(m_lstPointF.first()-QPointF(1,1),m_lstPointF.last()+QPointF(1,1));
    }
}

void VisionPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

void VisionPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

void VisionPoint::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}
