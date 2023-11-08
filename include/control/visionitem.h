/****************************************************************************
** @brief       自定控件的基类
** @note
** @author      xiaodongLi
** @date        create:2018-09-28
** @example
****************************************************************************/

#ifndef VISIONITEM_H
#define VISIONITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QVector>
#include "VGBase.h"
#include "../visiongraph_global.h"

#include <QFlags>


/**
 * @brief       枚举类型，item类型或者鼠标控制的类型（鼠标事件执行的对应的类型）-- 主要是绘图的view的状态的标记，包含了鼠标事件和绘制的item的记录等
 * @param       鼠标触发事件的所要执行的操作
 */
enum ItemType{
    No,   //选择状态
    Drag,  //拖动
    Zoom, //缩放状态

    Paint_LineFitting,
//    Paint_Text,
//    Paint_Multi,

    Paint_Rect,  //矩形
    Paint_EllipseItem,  //圆或者椭圆
    Paint_CirCle,   //圆
    Paint_Arc,  //圆弧
    Paint_Poly,  //多边形
    Paint_Region,  //区域 -- 鼠标绘制，自动连接起始和结尾的区域，任意区域
    Paint_Line,  //线
    Paint_polyLine,  //折线
    Paint_Arrow,  //箭头（）
    Paint_Chain,   //链--（线和圆弧混用）
    Paint_CrossPoint,  //单独一个真正意义上的点
    Paint_Point,  //点
    Paint_NoPoint  //擦除item

};

Q_DECLARE_FLAGS(ItemTypes,ItemType)


/**
 * @brief       枚举类型  鼠标的样式方向--对应想要的鼠标事件
 */
enum DirecCursor
{
    normal_rect,
    left_rect,
    top_rect,
    right_rect,
    bottom_rect,  //标记点

    left_Top_rect,
    left_bottom_rect,
    right_top_rect,
    right_bottom_rect,

    arrowsUp
};

struct Coordinate_Struct{
    qreal dx = 0;  //坐标系点x坐标
    qreal dy = 0;  //坐标系点y坐标
    qreal scale = 1;  //坐标系缩放比例 --- 暂时不做处理
    qreal angle = 0;  //坐标系旋转角度
};

QPointF VISIONGRAPHSHARED_EXPORT convert_coordinate(Coordinate_Struct stru_pre,Coordinate_Struct stru,QPointF pointF);

class VISIONGRAPHSHARED_EXPORT VisionItem : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    VisionItem(QGraphicsItem *parent = 0);

    /**
     * @brief       设置图形的类型
     * @param       QString
     */
     void setType(ItemType type){
         m_type = type;
     }

     /**
      * @brief       获取图形的类型
      * @param       QString
      */
    ItemType getType(){
        return m_type;
    }

    /**
     * @brief       设置item的状态
     * @param       bool
     */
    void setSelectedStatus(bool bSelected){
        m_bSelected = bSelected;
        setSelected(bSelected);
    }


    /**
     * @brief       获取item的选中状态
     * @param       bool
     */
    bool getSelectedStatus(){
        return m_bSelected;
    }

    /**
     * @brief       设置item的编辑状态
     * @param       bool
     */
    void setEdit(bool edit){
        m_bEdit = edit;
    }

    /**
     * @brief       获取item的编辑状态
     * @param       bool
     */
    bool getEdit(){
        return m_bEdit;
    }

    /**
     * @brief       设置item的Enable使能
     * @param       bool
     */
    void setItemEnable(bool enable){
        this->setEnabled(enable);
    }

    /**
     * @brief       获取item的Enable使能
     * @param       bool
     */
    bool getItemEnable(){
        return this->isEnabled();
    }

    void setGlobleData(qreal scale,qreal penWid){
        Q_UNUSED(scale)
        Q_UNUSED(penWid)
//        g_scale = scale;
//        g_penWidth = penWid;
    }

    /**
     * @brief       设置VisionItem的相对坐标
     * @param
     */
    void setCoordinate_rela(Coordinate_Struct stru);

    /**
     * @brief       获取VisionItem的相对坐标
     * @param
     */
    Coordinate_Struct getCoordinate_rela()
    {
        return m_itemCoordinate;
    }


    /**
     * @brief       设置属性颜色
     * @param       color
     */
    void setColor(QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160))
    {
        m_borderColor = borderColor;
        m_brushColor = selectedColor;
        m_selectedColor = brushColor;
    }
    /**
     * @brief       设置属性颜色
     * @param       color
     */
    void setBorderColor(QColor borderColor = QColor(255,0,0))
    {
        m_borderColor = borderColor;
    }
    /**
     * @brief       设置属性颜色
     * @param       color
     */
    void setBrushColor(QColor brushColor = QColor(255,0,0))
    {
        m_brushColor = brushColor;
    }
    /**
     * @brief       设置属性颜色
     * @param       color
     */
    void setSelectedColor(QColor selectedColor = QColor(255,0,0))
    {
        m_selectedColor = selectedColor;
    }
public:
    //虚函数
    /**
     * @brief       判断点（x,y）是否在该item内
     * @param       bool
     */
    virtual bool getPosInArea(qreal x,qreal y) = 0;

    /**
     * @brief       获取item的顶点--（圆（椭圆）的顶点为外切矩形）
     * @param       QVector<QPointF>
     */
    virtual QVector<QPointF> getPoints() = 0;


    /**
     * @brief       颜色数据
     * @param       //item在选中或者编辑状态下的小矩形和边框的颜色//绘制的item的边框颜色  未选中或者非编辑的颜色//填充的颜色
     */
//    virtual void setData() = 0;

signals:
    void signal_clicked(VisionItem* item,bool selected,bool bIn = true,qreal x=0,qreal y=0);
    void signal_ctrl(int eventStyle);  //事件类型
    void signal_press();   //用于提示item被点击

    /**
     * @brief       item绘制完成后触发
     * @param       将item的PainterPath传出去提供给其他的进行处理
     */
    void signal_painterInfo(ItemType type,QPainterPath rf);
//    void signal_painterInfo(ItemType type,QRectF rf,qreal angle);

    /**
     * @brief       当item的selected发生变化的事触发
     * @param       bool
     */
    void selectedChanged(bool selected,VisionItem* item,ItemType type, QRectF rf,QPointF left, qreal angle);

    void selectedChanged(bool selected,VisionItem* item,ItemType type, QVector<QPointF> vecPointF);

    /**
     * @brief       当item的boundingRect()发生变化的事触发,主要用于提供数据更新
     * @param
     */
    void signalChanged(VisionItem* item);

    void signal_hoverLeaveEvent(VisionItem* item);
    void signal_hoverEnterEvent(VisionItem* item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

public:
    ItemType m_type;
    bool m_bEdit = false;
    bool m_bSelected = false;

    QPointF origin = QPointF(0,0);
    qreal rela_Angle = 0;
    qreal scale = 1;

    QColor m_borderColor;
    QColor m_brushColor;
    QColor m_selectedColor;

    Coordinate_Struct m_itemCoordinate;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ItemTypes)

#endif // VISIONITEM_H
