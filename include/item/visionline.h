/****************************************************************************
** @brief       基于VisionItem类封装的直线--大数量直线的控件
** @note        该类主要是用于绘制大数量的直线的控件，只作为显示，主要是为了解决大数量直线单独绘制的耗时问题
** @author      xiaodongLi
** @date        create:2019-02-20
** @example     /as VisionPoint
****************************************************************************/

#ifndef VISIONLINE_H
#define VISIONLINE_H

#include <QObject>
#include <QPainter>
#include "../control/visionitem.h"

class VISIONGRAPHSHARED_EXPORT VisionLine : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionLine(bool color_enable = false,QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160),
                        VisionItem *parent = 0);

    void setLine(QLineF lineF);
    void setLines(QList<QLineF> lstLineF);


    /**
     * @brief       获取每个顶点
     * @param       point vec
     */
    QVector<QPointF> getPoints();

    bool getPosInArea(qreal x,qreal y);

    vector<VGLine2D> getData();

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    enum Style{
        SINGLE,
        MULTI
    };

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
//    void signalChanged(VisionItem* item);

private:
    QLineF m_lineF;
    QList<QLineF> m_lstLineF;

    Style m_style = SINGLE;

//    QColor m_borderColor;
//    QColor m_brushColor;
//    QColor m_selectedColor;

    QRectF m_rect = QRectF(0,0,0,0); //计算有效区域

    //计算多条线段的有效区域
    QRectF detailRect(QList<QLineF> lst);

public slots:
};

#endif // VISIONLINE_H
