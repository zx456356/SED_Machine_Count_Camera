#include "visiontext.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>

VisionText::VisionText(VisionItem *parent) : VisionItem(parent)
{
//    m_type = ItemType::Paint_Text;
    setFlag(QGraphicsItem::ItemIsMovable,false);
    setFlag(QGraphicsItem::ItemIsSelectable,false);
}

void VisionText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen = QPen(m_color_text,g_penWidth*(1/this->scene()->views().at(0)->matrix().m22()));
    painter->setPen(pen);

    QFont font;
    font.setPixelSize(m_textPiexl);
    painter->setFont(font);
    //TODO 此处得到的rect在中文下完美适应，但是在英文和数字会出现多余的部分，后续优化
    painter->drawText(QRectF(0,0,m_strText.size()*m_textPiexl,m_textPiexl),m_strText);

}

void VisionText::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

void VisionText::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

void VisionText::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
}

void VisionText::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    VisionItem::hoverEnterEvent(event);
    event->ignore();
}

void VisionText::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    VisionItem::hoverLeaveEvent(event);
    event->ignore();
}

QRectF VisionText::boundingRect() const
{
    return QRectF(0,0,m_strText.size()*m_textPiexl,m_textPiexl);
}

