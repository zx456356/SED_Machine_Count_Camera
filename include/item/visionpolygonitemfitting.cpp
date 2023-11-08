#include "visionpolygonitemfitting.h"

#include <QDebug>
#include "../control/color.h"

#define Pi 3.1415926


VisionPolygonItemFitting::VisionPolygonItemFitting(bool close, bool edit, qreal length, bool color_enable, QColor borderColor, QColor selectedColor, QColor brushColor, VisionItem *parent) : VisionItem(parent)
{
    if(color_enable){
        m_borderColor = borderColor;
    }else{
        m_borderColor = borderColor;
    }
    m_brushColor = brushColor;
    m_selectedColor = selectedColor;

    m_bFitting = true;
    m_length = length;

    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    m_type = ItemType::Paint_Poly;
    m_bEdit = edit;
    if(m_bEdit){
        setSelectedStatus(true);
    }else{
        setSelectedStatus(false);
    }
    m_bClose = close;
}

VisionPolygonItemFitting::~VisionPolygonItemFitting()
{

}

void VisionPolygonItemFitting::setPointFs(QVector<QPointF> pointFs, bool bFinished)
{
    m_vecPointFs = pointFs;

//    //转换数据
//    Coordinate_Struct stru;
//    stru.angle = 0;
//    stru.dx = 0;
//    stru.dy = 0;
//    stru.scale = 1;

//    m_vecPointFs.clear();
//    for(int i=0;i<pointFs.size();i++){
//        QPointF point = pointFs.at(i);
//        point = convert_coordinate(stru,m_itemCoordinate,point);
//        m_vecPointFs.push_back(point);
//    }

    m_polygonF.clear();
    m_polygonF.append(m_vecPointFs);

    //获取item的pos位置，boundingRect的topLeft

    QPointF orignPointF = m_polygonF.boundingRect().topLeft();
    m_x = orignPointF.x();
    m_y = orignPointF.y();

    if(m_length > 0){
        updateLength(m_length);
    }

//    this->setPos(m_x,m_y);

    if(bFinished){
        initMiniRect();
    }
}


bool VisionPolygonItemFitting::getPosInArea(qreal x, qreal y)
{
    if(m_length <= 0){
        if(m_polygonF.containsPoint(this->mapFromScene(QPointF(x,y)),Qt::OddEvenFill)){
            return true;
        }else{
            return false;
        }
    }else{
        if(m_polygonF_Fitting.containsPoint(this->mapFromScene(QPointF(x,y)),Qt::OddEvenFill)){
            return true;
        }else{
            return false;
        }
    }
}

VGPathFittingField VisionPolygonItemFitting::getData(){
    //转换数据
    Coordinate_Struct stru;
    stru.angle = 0;
    stru.dx = 0;
    stru.dy = 0;
    stru.scale = 1;

    vector<QPointF> v_p;
    for(int i=0;i<m_vecPointFs.size();i++){
        QPointF point = m_vecPointFs.at(i);
        point = convert_coordinate(m_itemCoordinate,stru,point);
        v_p.push_back(point);
    }

    VGPathFittingField vgPathFitting;

    VGPath vgPath;
    vector<VGPoint2D> vec_p;
    vec_p.clear();
    for(unsigned int i=0;i<v_p.size();i++){
        VGPoint2D point2D;
        point2D.x = v_p.at(i).x();
        point2D.y = v_p.at(i).y();
        vec_p.push_back(point2D);
    }
    vgPath.arrayPoint2D = vec_p;
    vgPath.closed = m_bClose;

    vgPathFitting.optional = VG_ENABLE;
    vgPathFitting.axis = vgPath;
    vgPathFitting.width = m_length;
    return vgPathFitting;
}

void VisionPolygonItemFitting::setCoordinate_rela(Coordinate_Struct stru)
{
    for(int i=0;i<m_vecPointFs.count();i++) {
        QPointF pointF = m_vecPointFs.at(i);
        pointF = convert_coordinate(m_itemCoordinate,stru,pointF);
        m_vecPointFs.replace(i,pointF);
    }

    VisionItem::setCoordinate_rela(stru);

    m_polygonF.clear();
    m_polygonF.append(m_vecPointFs);

    if(m_length > 0){
        updateLength(m_length);
    }
    updateMiniRect();
    this->scene()->update();
}


void VisionPolygonItemFitting::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setRenderHint(QPainter::Antialiasing, true);

    if(option->state & QStyle::State_Selected){

        painter->setPen(QPen(QBrush(m_selectedColor),0));

        if(m_bEdit){
            for(int i=0;i<m_lstRect.count();i++){
                m_lstRect[i]->show();
            }
        }

        emit selectedChanged(true,this,ItemType::Paint_Poly,m_vecPointFs);

        m_bSelected = true;
        setSelectedStatus(m_bSelected);

    }else{
        painter->setPen(QPen(QBrush(m_borderColor),0));

        for(int i=0;i<m_lstRect.count();i++){
            m_lstRect[i]->hide();
        }

        //通知view将该item转换为区域 ---
        //由选中状态变为非选中状态，由于，构造函数默认为选中状态，故当item为未选中状态，则必定是由选中状态变为未选中状态，直接传输信号通知
        //前提是item是可编辑的
        if(m_bEdit){
            emit selectedChanged(false,this,ItemType::Paint_Poly,m_vecPointFs);
        }
        m_bSelected = false;
        setSelectedStatus(m_bSelected);
    }

    if(m_bClose){
//        painter->setBrush(m_brushColor);
        painter->drawPolygon(m_polygonF);
    }else{
        painter->drawPolyline(m_polygonF);
    }

    painter->setBrush(m_brushColor);

//    for(int i=0;i<m_lstPoly.count();i++){
//        painter->drawPolygon(m_lstPoly[i]);
//    }
    painter->drawPolygon(m_polygonF_Fitting);

    if(m_bSelected){
        QPainterPath path;
        path.addPolygon(m_polygonF);
        emit signal_painterInfo(ItemType::Paint_Poly,path);
    }

}

QRectF VisionPolygonItemFitting::boundingRect() const
{
    QRectF rf;
    rf = QRectF(m_polygonF.boundingRect().x()-m_length-5,m_polygonF.boundingRect().y()-m_length-5,
                      m_polygonF.boundingRect().width()+2*m_length+10,m_polygonF.boundingRect().height()+2*m_length+10);
    return rf;
}

void VisionPolygonItemFitting::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_bFitting = false;

    if(!m_bEdit)
        return;

    QGraphicsItem::mousePressEvent(event);

    m_lastPointF = event->scenePos();

    //鼠标属于非正常状态--拖动小矩形框，当鼠标在编辑框状态，不处理按下事件，此时只需要处理moveEvent事件即可
    if(m_iIndex != -1)
        return;

    if(m_polygonF_Fitting.containsPoint(event->scenePos(),Qt::OddEvenFill)){
//        qDebug()<<" mouse press Event : true";
        setSelectedStatus(true);
    }else{
        setSelectedStatus(false);
//        qDebug()<<" mouse press Event false";
    }
    this->scene()->update();
}

void VisionPolygonItemFitting::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;

    if(m_iIndex != -1)
        return;

    if(!m_polygonF_Fitting.containsPoint(event->scenePos(),Qt::OddEvenFill)){
        emit signal_clicked(this,true,false,event->scenePos().x(),event->scenePos().y());
        return;
    }
    emit signal_clicked(this,true,true,event->scenePos().x(),event->scenePos().y());
    QGraphicsItem::mouseReleaseEvent(event);

}

void VisionPolygonItemFitting::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!m_bEdit)
        return;
    if(!m_bSelected)
        return;
    //在执行QGraphicsItem的时候。会自动的进行pos的重新设置
//    QGraphicsItem::mouseMoveEvent(event);

    QPointF disPointF = event->scenePos() - m_lastPointF;
    m_lastPointF = event->scenePos();

    if(m_vecPointFs.count() > m_iIndex && m_iIndex != -1){
        m_vecPointFs.replace(m_iIndex,event->scenePos());
    }else{
        //拖动的时候。m_vecPointFs是不变化的，变化的事this->pos()
        for(int i=0;i<m_vecPointFs.count();i++){
            m_vecPointFs.replace(i,m_vecPointFs.at(i)+disPointF);
        }
        m_x = m_x + disPointF.x();m_y = m_y + disPointF.y();
    }
    m_polygonF.clear();
    m_polygonF.append(m_vecPointFs);

    updateMiniRect();
//    this->setPos(m_x,m_y);

    updateData();
    emit signalChanged(this);
    this->scene()->update();
}

void VisionPolygonItemFitting::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(m_bFitting){
        m_length = getMinDistance(m_vecPointFs,m_bClose,event->scenePos());

        m_polygonF_Fitting.clear();
        m_polygonF_Fitting = getPolygonLineFitting(m_vecPointFs,m_bClose,m_length);
        this->scene()->update();
    }else{
        //TODO 此处需要添加编辑length功能
    }
}

void VisionPolygonItemFitting::updateLength(qreal length)
{
    m_length = length;

    m_polygonF_Fitting.clear();
    m_polygonF_Fitting = getPolygonLineFitting(m_vecPointFs,m_bClose,m_length);
}

void VisionPolygonItemFitting::initMiniRect()
{
    m_lstRect.clear();
    for(int i=0;i<m_vecPointFs.count();i++){
        MiniRect* miniRect = new MiniRect(m_vecPointFs.at(i).x()-5,m_vecPointFs.at(i).y()-5,10,10,m_borderColor,m_selectedColor,m_brushColor,this);
        miniRect->setGlobleData(g_scale,g_penWidth);
        miniRect->setIndex(i);
        connect(miniRect,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));
        miniRect->hide();
        m_lstRect.append(miniRect);
    }
}

void VisionPolygonItemFitting::updateMiniRect()
{
    for(int i=0;i<m_vecPointFs.count();i++){
        m_lstRect[i]->setPos(m_vecPointFs.at(i).x()-5,m_vecPointFs.at(i).y()-5);
    }
}

qreal VisionPolygonItemFitting::getMinDistance(QVector<QPointF> vec_p, bool close, QPointF p)
{
    qreal l = 1000;
    for(int i=0;i<vec_p.count()-1;i++){
        qreal l1 = getDistance(vec_p[i],vec_p[i+1],p);
        if(l1 < l){
            l = l1;
        }
    }
    if(close){
        qreal l1 = getDistance(vec_p.last(),vec_p.first(),p);
        if(l1 < l){
            l = l1;
        }
    }
    return l;
}

qreal VisionPolygonItemFitting::getDistance(QPointF p1, QPointF p2, QPointF p)
{
    qreal A = p2.y() - p1.y();
    qreal B = p1.x() - p2.x();
    qreal C = p2.x()*p1.y() - p1.x()*p2.y();
    qreal l = fabs(A*p.x() + B*p.y() + C)/sqrt(A*A+B*B);
    return l;
}

QPolygonF VisionPolygonItemFitting::getPolygonLineFitting(QVector<QPointF> vec_p, bool close, qreal length)
{
    QVector<QPointF> vecP;
    vecP.clear();
    QList<QPolygonF> lstPoly;
    lstPoly.clear();

    QPolygonF poly;
    poly.clear();

    //todo  绘制一个点的时候，该类没有任何意义----一个圆
    if(vec_p.count() <= 1)
        return poly;


    if(!close){
        //非封闭的图形
        //n个点--  n-1直线 -- n-2圆弧
        for(int i=0;i<vec_p.count()-1;i++){
            lstPoly.append(getLineFitting(vec_p.at(i),vec_p.at(i+1),length));
            lstPoly.append(getCircle(vec_p.at(i),length));
        }
        //处理最后一个点
        lstPoly.append(getCircle(vec_p.last(),length));

    }else{
        //封闭的图形
        //n个点--  n直线 -- n圆弧
        for(int i=0;i<vec_p.count()-1;i++){
            lstPoly.append(getLineFitting(vec_p.at(i),vec_p.at(i+1),length));
            lstPoly.append(getCircle(vec_p.at(i),length));
        }
        //最后一个点，需要首尾相连
        lstPoly.append(getLineFitting(vec_p.last(),vec_p.first(),length));
        lstPoly.append(getCircle(vec_p.last(),length));
    }

    for(int i=0;i<lstPoly.count();i++){
        poly = poly.united(lstPoly.at(i));
    }

    return poly;
}

QPolygonF VisionPolygonItemFitting::getLineFitting(QPointF p1, QPointF p2, qreal length)
{
    //获取  过点P1和点P2两条和P1P2线垂直的两条直线，分别和与线P1P2平行并且垂直距离为length的交点
    // P1 P2得到直线l   l为长度，且为中轴，形成一个矩形，矩形的宽度为2*length
    qreal A = p2.y() - p1.y();
    qreal B = p1.x() - p2.x();
    qreal C = p2.x()*p1.y() - p1.x()*p2.y();
    Q_UNUSED(C)

    //直线l，获取以两点为圆心，将l平移length后，和两点为圆心的圆相切的点的坐标
    //l1: Ax+By+C11=0  (C11:+- √(length*length *(A*A+B*B)) -(Ax1+By1);  lo:Bx-Ay+C1=0;(C1:Ay1-Bx1)--x1,y1点p1的坐标。  l1和lo的交点即为切点
    //l1和l0可以得到两个交点   Ax+By+C=0  Bx-Ay+C1=0   x=-(A*C+B*C1)/(A*A+B*B)  y=-(B*C-A*C1)/(A*A+B*B)
    qreal C11 = -sqrt(length*length *(A*A+B*B)) -(A*p1.x()+B*p1.y());
    qreal C12 = sqrt(length*length *(A*A+B*B)) -(A*p1.x()+B*p1.y());
    qreal C1 = A*p1.y()-B*p1.x();
    QPointF tempP1 = QPointF(-(A*C11+B*C1)/(A*A+B*B),-(B*C11-A*C1)/(A*A+B*B));
    QPointF tempP2 = QPointF(-(A*C12+B*C1)/(A*A+B*B),-(B*C12-A*C1)/(A*A+B*B));

    qreal C21 = -sqrt(length*length *(A*A+B*B)) -(A*p2.x()+B*p2.y());
    qreal C22 = sqrt(length*length *(A*A+B*B)) -(A*p2.x()+B*p2.y());
    qreal C2 = A*p2.y()-B*p2.x();
    QPointF tempP3 = QPointF(-(A*C21+B*C2)/(A*A+B*B),-(B*C21-A*C2)/(A*A+B*B));
    QPointF tempP4 = QPointF(-(A*C22+B*C2)/(A*A+B*B),-(B*C22-A*C2)/(A*A+B*B));
//    qDebug()<<QPolygonF({tempP1,tempP2,tempP4,tempP3});

    //定位p1,p2和p3,p4分别的对应的点
    //2-3和1-4两条线相交的话，则 1,3;2,4;  -- 此处已经确认分组是没问题的，
    //谁在前，谁在后

    return QPolygonF({tempP1,tempP2,tempP4,tempP3});
}

QPolygonF VisionPolygonItemFitting::getCircle(QPointF p, qreal r)
{
    QPainterPath path;
    path.addEllipse(p,r,r);

    return path.toFillPolygon();
}

void VisionPolygonItemFitting::updateData()
{
    m_polygonF_Fitting.clear();
    m_polygonF_Fitting = getPolygonLineFitting(m_vecPointFs,m_bClose,m_length);
}

void VisionPolygonItemFitting::slotIndex(int index)
{
    m_iIndex = index;
    QGraphicsView *view = this->scene()->views().at(0);

    if(m_iIndex == -1){
        view->setCursor(viewCursor);
    }else{
        QCursor cursor = QCursor(QPixmap(iconPath+"cursor-sizeall.png"));
        view->setCursor(cursor);
    }
}
