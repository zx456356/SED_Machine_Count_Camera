#ifndef VISIONARCITEMFITTING_H
#define VISIONARCITEMFITTING_H

#include <QObject>

#include <QPainter>
#include "../control/color.h"
#include "../control/visionitem.h"
#include "../control/minirect.h"

class VISIONGRAPHSHARED_EXPORT VisionArcItemFitting : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionArcItemFitting(bool bEdit = false, qreal length = 0, bool color_enable = false,
                                  QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160), VisionItem *parent = 0);

    void setPointFs(QPointF sP = QPointF(0,0),QPointF mP = QPointF(0,0),QPointF fP = QPointF(0,0));
    void setArc(QPointF center,qreal r,qreal angle,qreal spanAngle);

    QVector<QPointF> getPoints();
    bool getPosInArea(qreal x, qreal y);

    VGArcFittingField getData();

    void setFitting(bool bFitting)
    {
        m_bFitting = bFitting;
    }

    void setCoordinate_rela(Coordinate_Struct stru);

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

signals:
//    void signalChanged(VisionItem *item);

private:
    QPointF m_p1;
    QPointF m_p2;
    QPointF m_p3;

    qreal m_x;
    qreal m_y;
    qreal m_width;
    qreal m_height;

    QPointF m_center;
    double m_r;
    double m_angle;
    double m_spanAngle;


    MiniRect *m_sMiniRect = NULL;
    MiniRect *m_mMiniRect = NULL;
    MiniRect *m_fMiniRect = NULL;
    int m_iIndex = -1;

    QPointF m_lastPoint_Press;

//    QColor m_borderColor;
//    QColor m_brushColor;
//    QColor m_selectedColor;

    qreal m_length = 0;
    bool m_bFitting = true;
    QPainterPath m_path; //由于圆弧的fitting部分需要规则的几个组合形成

    QPolygonF m_polygonF;
    QPolygonF m_polygonF1;
    QPolygonF m_polygonF2;

private:

    void updateLength(qreal length);

    void initMiniRect();
    //三点计算对应的圆心和直径，以及圆弧在圆中的角度范围
    bool detailData(QPointF sP,QPointF mP,QPointF fP);
    bool detailData(QPointF sP, QPointF mP, QPointF fP, QPointF center);

    void updateData();  //当圆弧变化时，Fitting进行刷新

public slots:
    void slotMiniRectIndex(int index);
};
#endif // VISIONARCITEMFITTING_H
