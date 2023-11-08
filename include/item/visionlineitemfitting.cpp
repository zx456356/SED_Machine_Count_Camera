#include "visionlineitemfitting.h"

#include <QDebug>
#include <QPainterPath>

#include "../control/color.h"

VisionLineItemFitting::VisionLineItemFitting(bool bEdit,qreal penWidth, bool color_enable,
                                             QColor borderColor, QColor selectedColor,
                                             QColor brushColor, VisionItem *parent) : VisionItem(parent)
{
    this->setAcceptHoverEvents(true);
    if(color_enable){
        m_borderColor = borderColor;
    }else{
        m_borderColor = borderColor;
    }
    m_brushColor = brushColor;
    m_selectedColor = selectedColor;

    m_penColor = borderColor;
    m_penWidth = penWidth;
    m_bEdit = bEdit;
    m_type = ItemType::Paint_LineFitting;

    if(m_bEdit){
        setSelectedStatus(true);
        m_bFitting = true;
    }else{
        setSelectedStatus(false);
        m_bFitting = false;
    }

}

void VisionLineItemFitting::setLineFitting(QPointF p1, QPointF p2,qreal length)
{
    m_pointF1 = p1;
    m_pointF2 = p2;
    m_length = length;

//    //转换数据
//    Coordinate_Struct stru;
//    stru.angle = 0;
//    stru.dx = 0;
//    stru.dy = 0;
//    stru.scale = 1;

//    QPointF pointF1 = m_pointF1;
//    pointF1 = convert_coordinate(stru,m_itemCoordinate,pointF1);
//    QPointF pointF2 = m_pointF2;
//    pointF2 = convert_coordinate(stru,m_itemCoordinate,pointF2);

    initMiniRect();
//    m_polygonF.clear();
//    m_polygonF.append({m_pointF1,m_pointF2});
//    updateRect(m_polygonF);
}

void VisionLineItemFitting::setPenWidth(qreal penWidth)
{
    m_penWidth = penWidth;
}

void VisionLineItemFitting::setPenColor(QColor color)
{
    m_penColor = color;
}

bool VisionLineItemFitting::getPosInArea(qreal x, qreal y)
{
    if(m_polygonF.containsPoint(QPointF(x,y),Qt::OddEvenFill)){
        return true;
    }else{
        return false;
    }
}

QVector<QPointF> VisionLineItemFitting::getPoints(){
    QVector<QPointF> vec_p;
    vec_p.append(m_pointF1);
    vec_p.append(m_pointF2);
    return vec_p;
}

VGSegmentFittingField VisionLineItemFitting::getData(){
    //转换数据
    Coordinate_Struct stru;
    stru.angle = 0;
    stru.dx = 0;
    stru.dy = 0;
    stru.scale = 1;

    QPointF pointF1 = m_pointF1;
    pointF1 = convert_coordinate(m_itemCoordinate,stru,pointF1);
    QPointF pointF2 = m_pointF2;
    pointF2 = convert_coordinate(m_itemCoordinate,stru,pointF2);

    VGSegmentFittingField segFittingField;

    VGSegment2D segment2D;
    segment2D.optional = VG_ENABLE;
    VGPoint2D p1,p2;
    p1.x = pointF1.x();
    p1.y = pointF1.y();
    p2.x = pointF2.x();
    p2.y = pointF2.y();
    segment2D.point1 = p1;
    segment2D.point2 = p2;

    segFittingField.axis = segment2D;
    segFittingField.optional = VG_ENABLE;
    segFittingField.width = m_length;

    return segFittingField;
}

void VisionLineItemFitting::setFitting(bool bFitting)
{
    m_bFitting = bFitting;
}

void VisionLineItemFitting::setCoordinate_rela(Coordinate_Struct stru)
{
    m_pointF1 = convert_coordinate(m_itemCoordinate,stru,m_pointF1);
    m_pointF2 = convert_coordinate(m_itemCoordinate,stru,m_pointF2);

    VisionItem::setCoordinate_rela(stru);

    m_miniRect1->setPos(m_pointF1.x()-5,m_pointF1.y()-5);
    m_miniRect2->setPos(m_pointF2.x()-5,m_pointF2.y()-5);

    updatePolygon();

    this->scene()->update();
}

QRectF VisionLineItemFitting::boundingRect() const
{
    return QRectF(m_polygonF.boundingRect().x()-50,m_polygonF.boundingRect().y()-50,
                  m_polygonF.boundingRect().width()+100,m_polygonF.boundingRect().height()+100);
}

void VisionLineItemFitting::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    if(option->state & QStyle::State_Selected){
        painter->setPen(QPen(QBrush(m_selectedColor),0));

    }else{
        painter->setPen(QPen(QBrush(m_borderColor),0));

    }
//    painter->drawRect(boundingRect());

    painter->drawLine(m_pointF1,m_pointF2);

    painter->setBrush(m_brushColor);
    painter->drawPolygon(m_polygonF);

    //绘制箭头
    qreal alph = atan2(m_pointF2.y()-m_pointF1.y(), m_pointF2.x()-m_pointF1.x());
    painter->translate(m_pointF2);

    qreal angle = (alph*180)/3.14159;
    qreal len = 2*(1/this->scene()->views().at(0)->matrix().m22());
//    qDebug()<<angle;
    painter->rotate(angle);
    painter->drawLine(QPointF(-(2*len),-len),QPointF(0,0));
    painter->drawLine(QPointF(-(2*len),+len),QPointF(0,0));

    if(!m_bEdit)
        return;

    //绘制编辑框
    if(option->state & QStyle::State_Selected){
        m_miniRect1->show();
        m_miniRect2->show();
        m_bSelected = true;
        setSelectedStatus(m_bSelected);
    }else{
        m_miniRect1->hide();
        m_miniRect2->hide();
        m_bSelected = false;
        setSelectedStatus(m_bSelected);
    }
}

void VisionLineItemFitting::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    m_bFitting = false;
    setSelectedStatus(true);
}

void VisionLineItemFitting::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    if(!m_bSelected)
        return;

//    QGraphicsItem::mouseMoveEvent(event);
    QPointF disPointF = event->scenePos()-m_lastPointF;
    m_lastPointF = event->scenePos();
    if(m_iIndex == 1){
        m_pointF1 = event->scenePos();
    }else if(m_iIndex == 2){
        m_pointF2 = event->scenePos();
    }else if(m_iIndex == 3){
        //边框拖动只改变m_length
        qreal A = m_pointF2.y() - m_pointF1.y();
        qreal B = m_pointF1.x() - m_pointF2.x();
        qreal C = m_pointF2.x()*m_pointF1.y() - m_pointF1.x()*m_pointF2.y();
        qreal l = fabs(A*event->scenePos().x() + B*event->scenePos().y() + C)/sqrt(A*A+B*B);
        m_length = l;
    }else{
        //移动整体
        m_pointF1 = m_pointF1 + disPointF;
        m_pointF2 = m_pointF2 + disPointF;
    }

    m_miniRect1->setPos(m_pointF1.x()-5,m_pointF1.y()-5);
    m_miniRect2->setPos(m_pointF2.x()-5,m_pointF2.y()-5);

    updatePolygon();

    emit signalChanged(this);
    this->scene()->update();
}

void VisionLineItemFitting::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    if(!m_polygonF.containsPoint(event->scenePos(),Qt::OddEvenFill)){
        emit signal_clicked(this,true,false,event->scenePos().x(),event->scenePos().y());
        return;
    }
    emit signal_clicked(this,true,true,event->scenePos().x(),event->scenePos().y());
    QGraphicsItem::mouseReleaseEvent(event);
}

void VisionLineItemFitting::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(m_bFitting){
        //记录length，并且刷新绘制的区域   length 为鼠标的位置到线的距离
        qreal A = m_pointF2.y() - m_pointF1.y();
        qreal B = m_pointF1.x() - m_pointF2.x();
        qreal C = m_pointF2.x()*m_pointF1.y() - m_pointF1.x()*m_pointF2.y();
        m_lastPointF = event->scenePos();
        qreal l = fabs(A*event->scenePos().x() + B*event->scenePos().y() + C)/sqrt(A*A+B*B);
        m_length = l;
        //更新数据
        //获得垂直线数据
        //Bx-Ay+C1=0;
        qreal C1 = -event->scenePos().x()*B+event->scenePos().y()*A;
        //Ax+By+C=0  Bx-Ay+C1=0   x=-(A*C+B*C1)/(A*A+B*B)  y=-(B*C-A*C1)/(A*A+B*B)
        QPointF crossPoint = QPointF(-(A*C+B*C1)/(A*A+B*B),-(B*C-A*C1)/(A*A+B*B));
        QPointF disPointF = event->scenePos() - crossPoint;
        m_polygonF.clear();
        m_polygonF.append({m_pointF1 - disPointF,m_pointF2 - disPointF,m_pointF2 + disPointF, m_pointF1 +disPointF});
//        qDebug()<<m_polygonF<<m_polygonF.boundingRect();
        updateRect(m_polygonF);
        this->scene()->update();
    }else{
        //获取边框的状态；
        qreal A = m_pointF2.y() - m_pointF1.y();
        qreal B = m_pointF1.x() - m_pointF2.x();
        qreal C = m_pointF2.x()*m_pointF1.y() - m_pointF1.x()*m_pointF2.y();
        m_lastPointF = event->scenePos();
        qreal l = fabs(A*event->scenePos().x() + B*event->scenePos().y() + C)/sqrt(A*A+B*B);
        if(l<m_length+3 && l > m_length-3){
            m_iIndex = 3;
            this->scene()->views().at(0)->setCursor(Qt::SizeVerCursor);
        }else{
            //恢复正常
            m_iIndex = -1;
            this->scene()->views().at(0)->setCursor(viewCursor);
        }
    }
}

void VisionLineItemFitting::initMiniRect()
{
    if(m_miniRect1 == NULL){
        m_miniRect1 = new MiniRect(m_pointF1.x()-5,m_pointF1.y()-5,10,10,m_borderColor,m_selectedColor,m_brushColor,this);
        m_miniRect1->setGlobleData(g_scale,g_penWidth);
        m_miniRect1->setIndex(1);
        connect(m_miniRect1,SIGNAL(signalIndex(int)),this,SLOT(slotMiniRectIndex(int)));
        m_miniRect1->hide();
    }else{
        m_miniRect1->setRect(m_pointF1.x()-5,m_pointF1.y()-5,10,10);
    }

    if(m_miniRect2 == NULL){
        m_miniRect2 = new MiniRect(m_pointF2.x()-5,m_pointF2.y()-5,10,10,m_borderColor,m_selectedColor,m_brushColor,this);
        m_miniRect2->setGlobleData(g_scale,g_penWidth);
        m_miniRect2->setIndex(2);
        connect(m_miniRect2,SIGNAL(signalIndex(int)),this,SLOT(slotMiniRectIndex(int)));
        m_miniRect2->hide();
    }else{
        m_miniRect2->setRect(m_pointF2.x()-5,m_pointF2.y()-5,10,10);
    }

    m_polygonF.clear();
    if(m_length <= 0){
        m_polygonF.clear();
        m_polygonF.append({m_pointF1,m_pointF2});
        updateRect(m_polygonF);
    }else{
        updateLength(m_length);
    }
}

void VisionLineItemFitting::updateLength(qreal length)
{
    qreal A = m_pointF2.y() - m_pointF1.y();
    qreal B = m_pointF1.x() - m_pointF2.x();
    qreal C = m_pointF2.x()*m_pointF1.y() - m_pointF1.x()*m_pointF2.y();
    Q_UNUSED(C)
    m_length = length;

    //获取边缘的方程
    //Ax+B(y-mLength)+C=0  //向上平移
    //Ax+B(y+mLength)+C=0  //向xia平移
    qreal C2; //C2
    //m_length = fabs(Ax+By+C)/sqrt(A*A+B*B);
    C2 = m_length*sqrt(A*A+B*B)-A*m_pointF1.x()-B*m_pointF1.y();

    //更新数据
    //获得垂直线数据
    //Bx-Ay+C1=0;
    qreal C1 = -m_pointF1.x()*B+m_pointF1.y()*A;
    //Ax+By+C=0  Bx-Ay+C1=0   x=-(A*C+B*C1)/(A*A+B*B)  y=-(B*C-A*C1)/(A*A+B*B)   // Ax+By+C是向上或者向下的平移的那条直线，得到一个点
    QPointF crossPoint = QPointF(-(A*C2+B*C1)/(A*A+B*B),-(B*C2-A*C1)/(A*A+B*B));
    QPointF disPointF = m_pointF1 - crossPoint;
    m_polygonF.clear();
    m_polygonF.append({m_pointF1 - disPointF,m_pointF2 - disPointF,m_pointF2 + disPointF, m_pointF1 +disPointF});
//        qDebug()<<m_polygonF<<m_polygonF.boundingRect();
    updateRect(m_polygonF);
//    this->scene()->update();
}

void VisionLineItemFitting::updateRect(QPolygonF polygonF)
{
    m_x = polygonF.boundingRect().x();
    m_y = polygonF.boundingRect().y();
    m_width = polygonF.boundingRect().width();
    m_height = polygonF.boundingRect().height();
}

void VisionLineItemFitting::updatePolygon()
{
    qreal A = m_pointF2.y() - m_pointF1.y();
    qreal B = m_pointF1.x() - m_pointF2.x();
    qreal C = m_pointF2.x()*m_pointF1.y() - m_pointF1.x()*m_pointF2.y();
    Q_UNUSED(C)

    //直线的cos值  cosφ=A1A2+B1B2/[√(A1^2+B1^2)√(A2^2+B2^2)]  // A2=0 B2=1;  cosφ=B1/√(A1^2+B1^2)
    m_polygonF.clear();
    QPointF disPointF;
    //P1和P2起点不一致，对应的AB的值是不一致的，存在方向性，cosφ的值是根据向量计算出来的，实际的ABC是动态的，也要考虑到方向
    if(m_pointF1.x() < m_pointF2.x()){
        disPointF = QPoint((-A/sqrt(A*A+B*B))*m_length,m_length*sin(acos(-A/sqrt(A*A+B*B))));
    }else{
        disPointF = QPoint((A/sqrt(A*A+B*B))*m_length,m_length*sin(acos(A/sqrt(A*A+B*B))));
    }
    m_polygonF.append({m_pointF1 - disPointF,m_pointF2 - disPointF,m_pointF2 + disPointF, m_pointF1 + disPointF});
    updateRect(m_polygonF);
    this->scene()->update();
}

void VisionLineItemFitting::slotMiniRectIndex(int index)
{
    if(index == 1){
        //移动点1
        m_iIndex = 1;
        this->scene()->views().at(0)->setCursor(Qt::SizeAllCursor);
    }else if(index == 2){
        //移动点2
        m_iIndex = 2;
        this->scene()->views().at(0)->setCursor(Qt::SizeAllCursor);
    }else{
        //恢复正常
        m_iIndex = -1;
        this->scene()->views().at(0)->setCursor(viewCursor);
    }
}
