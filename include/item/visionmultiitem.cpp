#include "visionmultiitem.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>

VisionMultiItem::VisionMultiItem(VisionItem *parent) : VisionItem(parent)
{
    //    m_type = ItemType::Paint_Multi;
//    this->setEnabled(false);
    setFlag(QGraphicsItem::ItemIsMovable,false);
    setFlag(QGraphicsItem::ItemIsSelectable,false);
}

void VisionMultiItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen = QPen(QColor(255,0,0),g_penWidth*(1/this->scene()->views().at(0)->matrix().m22()));
    painter->setPen(pen);

    //绘制rect
    if(m_strData.rect_enable){
        foreach (CRectangle2D crect, m_strData.lst_rect2D) {
            pen.setColor(crect.color);
            painter->setPen(pen);
            painter->drawRect(QRectF(crect.rect.origin.x,crect.rect.origin.y,crect.rect.width,crect.rect.height));
        }
    }
    //绘制圆
    if(m_strData.circle2D_enable){
        foreach (CCircle2D ccircle, m_strData.lst_circle2D) {
            pen.setColor(ccircle.color);
            painter->setPen(pen);
            painter->drawEllipse(QRectF(ccircle.circle.center.x-ccircle.circle.radius,
                                        ccircle.circle.center.y-ccircle.circle.radius,
                                        ccircle.circle.radius*2,ccircle.circle.radius*2));
        }
    }
    //绘制点
    if(m_strData.point2D_enable){
        foreach (CPoint2D cpoint, m_strData.lst_point2D) {
            pen.setColor(cpoint.color);
            painter->setPen(pen);
            painter->drawLine(QPointF(cpoint.point.x,
                                      cpoint.point.y-3*(1/this->scene()->views().at(0)->matrix().m22())),
                              QPointF(cpoint.point.x,
                                      cpoint.point.y+3*(1/this->scene()->views().at(0)->matrix().m22())));
            painter->drawLine(QPointF(cpoint.point.x-3*(1/this->scene()->views().at(0)->matrix().m22()),
                                      cpoint.point.y),
                              QPointF(cpoint.point.x+3*(1/this->scene()->views().at(0)->matrix().m22()),
                                      cpoint.point.y));
        }
    }
    //绘制圆弧
    if(m_strData.arc2D_enable){
        foreach (CArc2D carc, m_strData.lst_arc2D) {
            pen.setColor(carc.color);
            painter->setPen(pen);
            painter->drawArc(QRectF(carc.arc.center.x,carc.arc.center.y,
                                    2*carc.arc.radius,2*carc.arc.radius),
                             carc.arc.startAngle*16,carc.arc.sweepAngle*16);
        }
    }
    //绘制线段
    if(m_strData.seg2D_enable){
        foreach (CSegment2D cseg, m_strData.lst_seg2D) {
            pen.setColor(cseg.color);
            painter->setPen(pen);
            painter->drawLine(QPointF(cseg.segment.point1.x,cseg.segment.point1.y),
                              QPointF(cseg.segment.point2.x,cseg.segment.point2.y));
        }
    }
    //绘制路径
    if(m_strData.path_enable){
        //TODO
//        pen.setColor(m_strData.path_color);
//        painter->setPen(pen);
//        painter->drawRect(QRectF(m_strData.rect2D.origin.x,m_strData.rect2D.origin.y,m_strData.rect2D.width,m_strData.rect2D.height));
    }
    //绘制文本
    if(m_strData.text_enable){
        foreach (CText ctext, m_strData.lst_text) {
            pen.setColor(ctext.color);
            painter->setPen(pen);
            QFont font;
            font.setPixelSize(ctext.pixel);
            painter->setFont(font);
            //TODO 此处得到的rect在中文下完美适应，但是在英文和数字会出现多余的部分，后续优化
            painter->drawText(QRectF(ctext.textPoint.x(),ctext.textPoint.y(),
                                     ctext.text.size()*ctext.pixel,ctext.pixel),ctext.text);
        }
    }
}

void VisionMultiItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

void VisionMultiItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

void VisionMultiItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

void VisionMultiItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

void VisionMultiItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    event->ignore();
}

void VisionMultiItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    event->ignore();
}


QRectF VisionMultiItem::boundingRect() const
{
    QRectF rf = this->scene()->views().at(0)->rect();
//    QRectF rf = QRectF(0,0,100,100);
    return rf;
}
