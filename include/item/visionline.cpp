#include "visionline.h"
#include "../control/color.h"


#include <QGraphicsScene>
#include <QGraphicsView>


VisionLine::VisionLine(bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor, VisionItem *parent) : VisionItem(parent)
{
    if(color_enable){
        m_borderColor = borderColor;
    }else{
        m_borderColor = borderColor;
    }
    m_borderColor = borderColor;
    m_brushColor = brushColor;
    m_selectedColor = selectedColor;

    setFlag(QGraphicsItem::ItemIsMovable,false);
    setFlag(QGraphicsItem::ItemIsSelectable,false);
}

void VisionLine::setLine(QLineF lineF)
{
    m_lineF = lineF;
    m_style = SINGLE;
}

void VisionLine::setLines(QList<QLineF> lstLineF)
{
    if(lstLineF.count() <= 0){
        m_lineF = QLineF(0,0,0,0);
        m_style = SINGLE;
    }else if(lstLineF.count() == 1){
        m_lineF = lstLineF.first();
        m_style = SINGLE;
        m_rect = QRectF(m_lineF.p1(),m_lineF.p2());
    }else{
        m_lstLineF = lstLineF;
        m_style = MULTI;
        m_rect = detailRect(m_lstLineF);
    }
}

QVector<QPointF> VisionLine::getPoints()
{
    QVector<QPointF> vec_p;
//    if(m_style == MULTI){
//        for(int i=0;i<m_lstLineF.count();i++){
//            vec_p.append(m_lstPointF[i]);
//        }
//    }else{
//        vec_p.append(m_pointF);
//    }
    return vec_p;
}

bool VisionLine::getPosInArea(qreal x, qreal y)
{
    Q_UNUSED(x)
    Q_UNUSED(y)
    return false;
}

vector<VGLine2D> VisionLine::getData(){
    vector<VGLine2D> vec_vgLine;
    vec_vgLine.clear();
    if(m_style == SINGLE){
        VGLine2D line2D;
        //            line2D.optional = VG_ENABLE;
        line2D.a = m_lineF.p2().y() - m_lineF.p1().y();
        line2D.b = m_lineF.p1().x() - m_lineF.p2().x();
        line2D.c = m_lineF.p2().x()*m_lineF.p1().y() - m_lineF.p1().x()*m_lineF.p2().y();
        vec_vgLine.push_back(line2D);
        return vec_vgLine;
    }else{
        for(int i=0;i<m_lstLineF.count();i++){
            VGLine2D line2D;
            //                line2D.optional = VG_ENABLE;
            line2D.a = m_lstLineF.at(i).p2().y() - m_lstLineF.at(i).p1().y();
            line2D.b = m_lstLineF.at(i).p1().x() - m_lstLineF.at(i).p2().x();
            line2D.c = m_lstLineF.at(i).p2().x()*m_lstLineF.at(i).p1().y() - m_lstLineF.at(i).p1().x()*m_lstLineF.at(i).p2().y();
            vec_vgLine.push_back(line2D);
        }
        return vec_vgLine;
    }
}

void VisionLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen = QPen(m_borderColor,g_penWidth*(1/this->scene()->views().at(0)->matrix().m22()));
    painter->setPen(pen);
    //    painter->setBrush(Qt::red);
    if(m_style == SINGLE){
        painter->drawLine(m_lineF);
    }else{
        painter->drawLines(m_lstLineF.toVector());
    }
}

QRectF VisionLine::boundingRect() const
{
    return m_rect;

    if(m_style == SINGLE){
        return QRectF(m_lineF.p1(),m_lineF.p2());
    }else{
        return QRectF(m_lstLineF.first().p1(),m_lstLineF.last().p2());
    }
}

void VisionLine::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

void VisionLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

void VisionLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

QRectF VisionLine::detailRect(QList<QLineF> lst)
{
    if(lst.count()<=0)
        return QRectF(0,0,0,0);

    qreal m_minX = lst.at(0).x1();
    qreal m_minY = lst.at(0).y1();
    qreal m_maxX = lst.at(0).x1();
    qreal m_maxY = lst.at(0).y1();

    foreach (QLineF lineF, lst) {
        if(lineF.x1() < m_minX)
            m_minX = lineF.x1();

        if(lineF.x1() > m_maxX)
            m_maxX = lineF.x1();

        if(lineF.x2() < m_minX)
            m_minX = lineF.x2();

        if(lineF.x2() > m_maxX)
            m_maxX = lineF.x2();

        if(lineF.y1() < m_minY)
            m_minY = lineF.y1();

        if(lineF.y1() > m_maxY)
            m_maxY = lineF.y1();

        if(lineF.y2() < m_minY)
            m_minY = lineF.y2();

        if(lineF.y2() > m_maxY)
            m_maxY = lineF.y2();
    }
    return QRectF(QPointF(m_minX,m_minY),QPointF(m_maxX,m_maxY));
}
