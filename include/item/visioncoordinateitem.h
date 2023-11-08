#ifndef VISIONCOORDINATEITEM_H
#define VISIONCOORDINATEITEM_H

#include <QObject>
#include "../control/visionitem.h"

#include <QPainter>

class VisionCoordinateItem : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionCoordinateItem(bool bEdit = false, bool color_enable = false,
                                  QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160),
                                  VisionItem *parent = 0);

    void setPointF(QPointF pointF)
    {
        this->setPos(pointF);
        m_pointF = pointF;
    }

    void setCoordinateLength(int iLength = 50)
    {
        m_iLength = iLength;
    }

    void setAngle(qreal angle){
        m_angle = angle;
//        this->setRotation(angle);
    }

    void setColor(QColor color)
    {
        m_borderColor = color;
    }

    QPointF getP(){
        return m_pointF;
    }

    VGCoordinateSystem2D getData();

        /**
     * @brief       判断点（x,y）是否在该item内
     * @param       bool
     */
    bool getPosInArea(qreal x,qreal y){
        Q_UNUSED(x)
        Q_UNUSED(y)
        return false;
    }

    /**
     * @brief       获取item的顶点--（圆（椭圆）的顶点为外切矩形）
     * @param       QVector<QPointF>
     */
    QVector<QPointF> getPoints(){
        QVector<QPointF> vec;
        vec.append(m_pointF);
        return vec;
    }

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
//    void signalChanged(VisionItem* item);

private:
    QPointF m_pointF;
    int m_iLength = 50;
    qreal m_angle = 0;  //旋转角度--坐标系

    bool m_bEdit = false;

//    QColor m_borderColor;
//    QColor m_brushColor;
//    QColor m_selectedColor;


};

#endif // VISIONCOORDINATEITEM_H
