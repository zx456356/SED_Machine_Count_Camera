/****************************************************************************
** @brief       组合控件
** @note        显示多个控件组合，直接给出对应的数据
** @author      xiaodongLi
** @date        create:2019-07-20
** @example
****************************************************************************/

#ifndef VISIONMULTIITEM_H
#define VISIONMULTIITEM_H

#include "../control/visionitem.h"
#include "../control/color.h"

#include <QPainter>

struct CRectangle2D{
    VGRectangle2D rect;
    QColor color = QColor(255,0,0);
};
struct CCircle2D{
    VGCircle2D circle;
    QColor color = QColor(255,0,0);
};
struct CPoint2D{
    VGPoint2D point;
    QColor color = QColor(255,0,0);
};
struct CArc2D{
    VGArc2D arc;
    QColor color = QColor(255,0,0);
};
struct CSegment2D{
    VGSegment2D segment;
    QColor color = QColor(255,0,0);
};
struct CText{
    QPointF textPoint = QPoint(0,0);
    QColor color = QColor(255,0,0);
    qreal pixel = 18;
    QString text = "";
};

struct MultiItem_Struct{
    bool rect_enable = false;
    QList<CRectangle2D> lst_rect2D; //VisionRectItem

    QList<CCircle2D> lst_circle2D;  //VisionCircleItem
    bool circle2D_enable = false;

    QList<CPoint2D> lst_point2D;  //VisionCrossPointItem
    bool point2D_enable = false;

    QList<CArc2D> lst_arc2D;  //VisionArcItem
    bool arc2D_enable = false;

    QList<CSegment2D> lst_seg2D; //--VisionLineItem
    bool seg2D_enable;

//    VGPath path; //VisionPolygon
    bool path_enable = false;

    //文本机构体暂时不添加到VGBase.h中，后续有需要再添加
    bool text_enable = false;
    QList<CText> lst_text;
};

class VisionMultiItem : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionMultiItem(VisionItem *parent = 0);

    /**
     * @brief       设置数据
     */
    void setData(MultiItem_Struct stu){
        m_strData = stu;
    }

    MultiItem_Struct getData()
    {
        return m_strData;
    }

    bool getPosInArea(qreal x, qreal y){
        Q_UNUSED(x)
        Q_UNUSED(y)
        return false;
    }

    QVector<QPointF> getPoints(){
        QVector<QPointF> vec_point;
        return vec_point;
    }


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    QRectF boundingRect() const;

signals:
    void signal_RightClicked(VisionItem *item);
    void signal_DoubleClicked(VisionItem *item);

private:

    MultiItem_Struct m_strData;  //

public slots:
};

#endif // VISIONMULTIITEM_H
