/****************************************************************************
** @brief       文本控件
** @note        显示文本，
** @author      xiaodongLi
** @date        create:2019-07-20
** @example
****************************************************************************/

#ifndef VISIONTEXT_H
#define VISIONTEXT_H

#include "../control/visionitem.h"
#include "../control/color.h"

class VISIONGRAPHSHARED_EXPORT VisionText : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionText(VisionItem *parent = 0);


    /**
     * @brief       设置文本区域的背景色
     */
    void setBackgroundColor(QColor bgColor)
    {
        m_bgColor = bgColor;
    }

    /**
     * @brief       设置文本的颜色
     */
    void setTextColor(QColor color)
    {
        m_color_text = color;
    }


    /**
     * @brief       设置数据
     */
    void setData_Text(QString text=""){
        m_strText = text;
    }

    QString data_Text()
    {
        return m_strText;
    }

    void setText_Pos(QPointF p){
        m_pos = p;
        this->setPos(p);
    }

    QString getTextName(){
        return m_strText;
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

    //目前是根据字体进行适应的rect，此api暂时无效
    void setTextWidth_Height(qreal w,qreal h){
        m_textHeight = h;
        m_textWidth = w;
    }

    void setTextPiexl(qreal piexl){
        m_textPiexl = piexl;
    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
//    void mouseMoveEvent(QGraphicsSceneHoverEvent *event);

    QRectF boundingRect() const;

signals:
    void signal_RightClicked(VisionItem *item);
    void signal_DoubleClicked(VisionItem *item);

//    void signalChanged(VisionItem *item);
private:
    QColor m_bgColor = QColor(Qt::transparent);
    QColor m_color_text = QColor(Qt::black);

    QPointF m_pos;
    QString m_strText;  //显示的字的文本


    qreal m_textPiexl = 18;
    qreal m_textWidth = 30;  //此数值跟随字体变化
    qreal m_textHeight = 30;  //此数值需要建议跟随region变化

    bool m_bEnter = false;

public slots:
};

#endif // VISIONTEXT_H
