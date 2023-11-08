/****************************************************************************
** @brief       VisionGraph,绘制模块的widget
** @note        会生成一个widget来进行展示绘制模块---主要是优化region和item版本
** @note        不同版本合并为一个类，通过构造的参数来区分版本，方便后续拓展
** @author      xiaodongLi
** @date        create:2019-1-9
** @example
****************************************************************************/


#ifndef VISIONGRAPH__H
#define VISIONGRAPH__H

#include <QFrame>
#include <QWidget>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QToolButton>
#include <QIntValidator>
#include <QMenu>

#include <QLabel>
#include <QComboBox>
#include <QLayout>
#include <QAction>
#include <QToolBar>
#include <QSpinBox>
#include <QLineEdit>
#include "visiongraphwidget.h"
#include "visiongraphtool.h"

class VISIONGRAPHSHARED_EXPORT VisionGraph_ : public QFrame
{
    Q_OBJECT
public:
    explicit VisionGraph_(GraphType type = GraphType::graph_Info,ToolButtonDirection toolButtonDirect = ToolButtonDirection::topDirection
            ,QWidget *parent = 0);
    ~VisionGraph_();
public:
    /*
     * 测试用，接口不开放
     * 测试visionGraph窗口的边框的数值，即merge
     * */
    void setBorderValue(int i = 0);

    /**
     * @brief       设置GraphType，VisionGraph的版本，
     * @param       //此接口作废---使用此接口和设置工具栏Direction，会导致工具栏出问题（内部调用）
     * @param       此接口在构造VisionGraph后不可更改
     */
    void setGraphType(GraphType type,ItemModes mode);

    /**
     * @brief       设置sceneWidget的大小
     * @param
     */
    void setSceneWidgetSize(QSize size);
    void setSceneWidgetSize(qreal w,qreal h);

    /**
     * @brief       主题颜色设置
     * @param       设置对应的矩形，椭圆，区域等边框颜色、填充颜色等
     */
    void setThemeColor(ThemeColor theme);

    /**
     * @brief       _addRect()等带下划线的api，为非编辑控件，且不同于addRect()生成的非编辑控件。
     * @note        带下划线的均无法通过clearPainter()函数进行清除，只能通过scene的clear进行清空（释放），
     * @note        或者通过外部接收返回值进行释放内存，而addRect()生成的非编辑控件在clearPainter()函数进行清除，会释放掉内存占用
     */
    QGraphicsRectItem* _addRect(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());
    QGraphicsPolygonItem* _addPolygon(const QPolygonF &polygon, const QPen &pen = QPen(), const QBrush &brush = QBrush());
    QGraphicsLineItem* _addLine(const QLineF &line, const QPen &pen = QPen());
    QGraphicsEllipseItem* _addEllipse(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());
    VisionCrossPointItem* _addPoint(QPointF pointF, bool edit = false, qreal length = 5,bool color_enable = false, QColor color = QColor(255,0,0));
    VisionChainItem* _addChain(QList<QPointF> lstP, bool bClosed = false, bool bEdit = false, bool color_enable = false,QColor color = QColor(255,0,0));
    VisionArrow *_addArrow(QPointF pointF,bool bEdit = false,bool color_enable = false,QColor color = QColor(255,0,0));
    VisionCoordinateItem *_addCoordinate(QPointF p,qreal angle = 0,qreal length = 50,bool bEdit = true,
                                        bool color_enable = false,QColor color = QColor(255,0,0));
    /**
     * @brief       添加rectangle  可旋转的矩形
     * @param       bEdit 表示编辑
     */
    VisionRectItem* addRect(QRectF rf,qreal angle = 0,bool bEdit = true, bool bRotation = true,bool color_enable = false,
                            QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加一个arrow
     * @param       不可编辑的坐标系
     */
    VisionArrow *addArrow(QPointF pointF,bool bEdit = false,bool color_enable = false,
                          QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加椭圆
     * @param       默认是可编辑的
     */
    VisionEllipseItem* addEllipse(QRectF rf,qreal angle = 0, bool bEdit = true, bool bRotation = true,bool color_enable = false,
                                  QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加圆
     * @param       默认是可编辑的
     */
    VisionCircleItem* addCircle(QRectF rf, bool bEdit = true, bool color_enable = false,
                                QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加圆弧
     * @param       默认是可编辑的
     */
    VisionArcItem *addArc(QPointF sP,QPointF mP,QPointF fP, bool bEdit = true,bool color_enable = false,
                          QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    VisionArcItem *addArc(QPointF center,qreal r,qreal angle,qreal spanAngle, bool bEdit = true, bool color_enable = false,
                          QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加线
     * @param       默认是可编辑的
     */
    VisionLineItem* addLine(QLine line, bool bEdit = true,bool color_enable = false,
                            QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    VisionLineItem* addLine(QLineF line, bool bEdit = true,bool color_enable = false,
                            QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加线--不限数量
     * @param       当line数量达到一定的程度的时候，addline()会非常耗时。
     * @note        addLines()在绘制大数量的line的时候，会节省很多时间
     */
    VisionLine* addLines(QList<QLineF> lstLineF, bool color_enable = false,
                         QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));


    /**
     * @brief       添加多边形 ,close为false，为折线
     * @param       点的集合，点的集合一次连接
     * @note        polygon等价path。addPath()或者addPaths()
     */
    VisionPolygon* addPolygon(QVector<QPointF> vecPointF, bool bClose = true, bool bEdit = true,bool color_enable = false,
                              QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加一个点
     * @param
     */
    VisionCrossPointItem *addPoint(QPointF pointF, bool bEdit = false, qreal length = 5,bool color_enable = false,
                                   QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加点 -- 不限数量
     * @param       当point数量达到一定的程度的时候，addPoint()会非常耗时。
     * @note        addPointFs()在绘制大数量的point的时候，会节省很多时间
     */
    VisionPoint *addPointFs(QList<QPointF> lstP, bool color_enable = false,
                            QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加一个链
     * @param       链--多个点集合形成的一个空间，每两个点之间的连线存在方向（箭头），和path以及polygon类似
     */
    VisionChainItem *addChain(QList<QPointF> lstP,bool close = false,bool edit = true,bool color_enable = false,
                              QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));


    // Fitting

    /**
     * @brief       添加线Fitting
     * @param       默认是可编辑的，未添加不可编辑
     * @note        线域--以线为基准，进行面的绘制
     */
    VisionLineItemFitting* addLineFitting(QLine line, bool bEdit = true, qreal length = 0,bool color_enable = false,
                                          QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    VisionLineItemFitting* addLineFitting(QLineF lineF, bool bEdit = true, qreal length = 0,bool color_enable = false,
                                          QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加圆弧Fitting
     * @param       默认是可编辑的，未添加不可编辑
     * @note        圆弧域--以圆弧为基准，进行面的绘制
     */
    VisionArcItemFitting *addArcFitting(QPointF sP,QPointF mP,QPointF fP, bool bEdit = true, qreal length = 0,
                                        bool color_enable = false,
                                        QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    VisionArcItemFitting *addArcFitting(QPointF center,qreal r,qreal angle,qreal spanAngle, bool bEdit = true,qreal length = 0,
                                        bool color_enable = false,
                                        QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加圆Fitting
     * @param       默认是可编辑的，未添加不可编辑
     * @note        圆--以圆为基准，进行面的绘制
     */
    VisionCircleItemFitting *addCircleFitting(QRectF rf = QRectF(0,0,0,0), bool bEdit = true, qreal length = 0,
                                              bool color_enable = false,
                                              QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));


    /**
     * @brief       添加折线Fitting
     * @param       默认是可编辑的，未添加不可编辑
     * @note        折线域--以折线为基准，进行面的绘制
     */
    VisionPolygonItemFitting *addPolygonFitting(QVector<QPointF> vecPointF, bool bClose = true,bool bEdit = true, qreal length = 0,
                                                bool color_enable = false,QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));


    /**
     * @brief       添加坐标系
     * @param       默认是不可编辑.当前不支持编辑坐标系（拖动，旋转等操作）
     * @note        该api生成的坐标系会在调用clearPaint()函数被清除（要想一直保持坐标系存在，调用_addCoordinate().）
     */
    VisionCoordinateItem *addCoordinate(QPointF p,qreal angle = 0,qreal length = 50,bool bEdit = true,
                                        bool color_enable = false,
                                        QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加文本控件--特殊文本（区域显示的文本。CRT识别出来的额）
     * @param       默认是不可编辑.当前不支持编辑（拖动，旋转等操作）
     */
    VisionTextItem *addText(VGRegion region, QString name = "?");

    /**
     * @brief       添加文本控件--普通文本
     * @param       默认是不可编辑.当前不支持编辑（拖动，旋转等操作）
     */
    VisionText* addText(QString text="", qreal pixelSize = 18 ,QPointF p=QPointF(0,0), QColor color = QColor(255,0,0));

    /**
     * @brief       添加区域
     * @param       默认是不可编辑.当前不支持编辑（拖动，旋转等操作）
     */
    VisionRegion *addRegion(VGRegion *region, QColor color = QColor(255,0,0,180));
    VisionRegion *addRegion(vector<VGRegionPair> vec_regionPair);

    /**
     * @brief       添加大数量path
     * @param       默认是不可编辑.当前不支持编辑（拖动，旋转等操作）
     */
    VisionPathItem *addPaths(QVector<QVector<QPointF>> vec_vec_p,
                             bool color_enable = false, QColor borderColor = QColor(255,0,0),
                             QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加控件自由组合
     * @param       默认是不可编辑.当前不支持编辑（拖动，旋转等操作）
     */
    VisionMultiItem* addMultiItem(MultiItem_Struct stu);

    /**
     * @brief       设置view的背景图片
     * @param
     */
    int setBkImg(QImage image);

    /**
     * @brief       删除view的背景图片
     * @param
     */
    void removeBkImg();

    /**
     * @brief       设置toolButton的布局
     * @param       工具栏的存放的位置--窗口的left，top，right，bottom
     */
    void setToolButton_Direction(ToolButtonDirection direct);

    /**
     * @brief       获取view
     * @param       在某些情况下，需要visionGraph的view指针
     */
    VisionGraphView* getView(){
        if(view == nullptr)
            return NULL;
        return view;
    }

    /**
     * @brief       修改绘制的item时候触发
     * @param       在使用鼠标移动进行绘制任意区域的时候，鼠标本身的大小作为绘制要素之一
     * @param       绘制不同的item，有不同的鼠标样式
     */
    void setPainterCursorR(qreal qR);

    /**
     * @brief       设置记录当前所要绘制的item
     * @note
     */
    void setItemType(ItemType type){
        view->setItemType(type);
    }

    /**
     * @brief       view的缩放比例
     */
    void zoom(float scaleFactor){
        view->zoom(scaleFactor);
    }

    /**
     * @brief       撤销区域生成
     * @note        绘制区域的撤销操作--和恢复操作对应
     */
    void back_region(){
        view->back_region();
    }


    /**
     * @brief       恢复区域生成
     * @note        绘制区域的恢复操作--和撤销操作对应
     */
    void front_region(){
        view->front_region();
    }


    /**
     * @brief       清除view的绘制数据
     * @note        清除view中绘制的所有的item，并释放所有的item的内存（不包含_add*函数调用生成的item）
     */
    void clearPainter(){
//        view->clearPainter();
        slot_clear_action();
    }

    /**
     * @brief       获取当前绘制在view的区域
     * @param       XVRegion
     */
    XVRegion* getRegion(){
        return view->getRegion();
    }

    /**
     * @brief       获取当前view中绘制的所有的item
     * @param       VisionItem*
     */
    QList<VisionItem*> getItems(){
        return m_lstItem;
    }

    /**
     * @brief       设置View信息框的显示或者隐藏
     * @note        信息框包含，当前鼠标的坐标位置、rgb、灰度值、自定义文本等
     */
    void setViewInfo_Visible(bool bVisible);

    /**
     * @brief       设置View信息框的位置（四个拐角）
     * @note        信息框在view中的显示位置
     */
    void setViewInfo_Pos(Corner corner){
        view->setViewInfo_Pos(corner);
    }

    /**
     * @brief       设置View信息框的位置（任意位置）
     * @note        信息框在view中的显示位置
     */
    void setViewInfo_Pos(qreal x,qreal y){
        view->setViewInfo_Pos(x,y);
    }

    /**
     * @brief       设置View信息框的大小
     */
    void setViewInfo_Size(QSize size){
        view->setViewInfo_Size(size);
    }

    /**
     * @brief       设置View信息框的大小
     */
    void setViewInfo_Size(qreal w,qreal h){
        view->setViewInfo_Size(w,h);
    }


    /**
     * @brief       设置View信息框的文本
     * @note        信息框可显示自定义文本
     */
    void setViewInfo_text(QString text){
        view->setViewInfo_text(text);
    }

    /**
     * @brief       设置View信息框的颜色
     * @note        （背景颜色和文本颜色）目前暂未实现该功能
     */
    void setViewInfo_Color(QColor backgroundColor,QColor textColor){
        view->setViewInfo_Color(backgroundColor,textColor);
    }


    /**
     * @brief       获取ToolButton
     * @note        获取工具栏中的对应的工具按钮，返回其对象指针
     */
    QToolButton* getToolButton(ToolButtonType type);

    /**
     * @brief       删除ToolButton
     * @note        删除工具栏中的对应的工具按钮
     */
    bool removeToolButton(ToolButtonType type);

    /**
     * @brief       添加ToolButton
     * @note        添加的ToolButton只是单纯的添加
     * @note        此ToolButton是不可调用getToolButton()和removeToolButton()
     */
    void addToolButton(QToolButton* btn);

    /**
     * @brief       获取鼠标的直径的slider对象指针
     */
    QSlider *getToolBarMouseSize_slider();

    /**
     * @brief       移除鼠标的直径信息
     */
    void removeToolBarMouseSize();

    /**
     * @brief       不显示toolbar的view的信息
     * @note        view中的算法区域的w和h，缩放比例
     */
    void removeToolBarInfoWidget();

    /**
     * @brief       获取VisionGraph的toolbar的view的信息。removeToolBarInfoWidget()
     */
    QAction *getToolBarInfoWidget();

    /**
     * @brief       获取VisionGraph的toolbar的view的信息。removeToolBarInfoWidget()/getToolBarInfoWidget()
     */
    QToolBar *getToolBarInfoWidgetBar();

    /**
     * @brief       设置View的算法区域的大小
     * @note        即算法中的有效区域
     */
    void setViewRegion_Size(qreal w,qreal h);

    /**
     * @brief       自适应大小并居中，返回缩放的比例（放大或者缩小，1-正常大小）-- 算法区域
     */
    qreal adjustSize(qreal w,qreal h);

    /**
     * @brief       设置View的算法区域的Visible
     */
    void setViewRegion_Visible(bool bVisible);

    /**
     * @brief       设置View的算法区域的color
     * @note        主要是区域的边框颜色
     */
    void setViewRegion_Color(const QColor &color);

    /**
     * @brief       获取背景图片
     */
    QImage getBkgImg();

    /**
     * @brief       保存当前绘图区域的绘制信息，生成图片
     * @param       path==""调用fileDialog进行设置保存
     */
    void saveBkgImg(QString path="");

    /**
     * @brief       删除具体的item
     * @param       item == nullptr 默认删除选中的
     */
    void removeItem(VisionItem* item = nullptr);
    /**
     * @brief       删除具体的item--对于通过_add函数添加
     * @param       item == nullptr 默认直接返回
     */
    void removeItem(QGraphicsItem *item = nullptr);

    /**
     * @brief       设置鼠标绘制的时候，鼠标的大小
     * @note        在GraphType::graphRegion模式下（区域），鼠标绘制区域的时候的直径
     */
    void setMousePaintSize(qreal qi);

    /**
     * @brief       设置view的缩放比例
     * @param       value = 1 表示是标准大小
     */
    void setView_Zoom(qreal qZoom);

    /**
     * @brief       获取view的缩放比例
     * @param       value = 1 表示是标准大小
     */
    qreal getView_Zoom();

    /**
     * @brief       设置view的type
     * @param       view中显示的内容（viewType） -- 单个item，多个item等
     * @note        item在view中显示的模式，具体可看ViewType的介绍
     */
    void setViewType(ViewType type = ViewType::freeItem);

    /**
     * @brief       设置窗口自适应
     * @param       方便处理当图片过大，提供给外部程序调用该函数自动自适应
     */
    void setViewSize_Fit();

    /**
     * @brief       获取窗口适应的比例
     * @param       w1 h1图片比例 ; w2 h2 图片要显示的窗口大小
     * @param       返回的是需要缩放的比例大小
     */
    qreal getViewSize_FitValue(qreal w1,qreal h1,qreal w2,qreal h2);

    /**
     * @brief       获取某一点的像素值
     * @param
     */
    QColor getPixel(qreal x,qreal y);

    /**
     * @brief       控制view的坐标系的显示和隐藏
     * @param       view的坐标系
     */
    void setCoordinateVisible(bool bVisible);

    /**
     * @brief       设置view的坐标系的颜色
     * @param       view的坐标系
     */
    void setCoordinateColor(QColor color);

    /**
     * @brief       获取view中的item数据
     * @param       类似于getItems()，返回值不同
     */
    vector<VisionItem*> getData();

    /**
     * @brief       获取view中的选中的item数据（当有且仅有一个的时候，默认其为当前）
     * @param
     */
    VisionItem *getCurData();

    /**
     * @brief       设置某一类控件（item）的颜色
     * @param       非编辑时的边框颜色，编辑时的边框颜色，填充颜色，非编辑控件的填充颜色
     */
    void setRectColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setEllipseColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setCircleColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setPolyColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setPolyLineColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setArcColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setPointColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    void setLineColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    void setRegionColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160),
                        QColor brushColor_unEdit = QColor(255,0,0,200));

    void setListRegionColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       获取上下文菜单的某一菜单选项
     * @param        注意strText的编码格式， 当确认存在的时候，但是返回值确实NULL，很可能是由于strText乱码、或者未支持多语言
     */
    QAction* getContextMenu_action(QString strText);

    /**
     * @brief       上下文菜单，添加自定义的action
     */
    void addContextMenu_action(QAction *action);

    /**
     * @brief       上下文菜单，移除自定义的action或者自身的action，可通过getContenxtMenu();来获取对应的action，进行移除
     */
    void removeContextMenu_action(QAction *action);

    /**
     * @brief       设置某一类控件（item）的颜色
     * @param       非编辑时的边框颜色，编辑时的边框颜色，填充颜色，非编辑控件的填充颜色
     */
    void setContextMenu_Visible(bool visible);

    /**
     * @brief       获取上下文菜单的对象指针
     */
    QMenu* getContextMenu();


    /**
     * @brief       刷新当前控件，使当前控件自动转换为区域
     * @param       只针对当前item
     */
    void updateItemToRegion();

    void ItemToRegion(VisionItem *item = NULL);

    void setCoordinateItem(Coordinate_Struct coor_stru);

    /**
     * @brief       设置矩形框绘制的类型，0---带旋转的矩形框  1---不带旋转的矩形框
     * @param       用于在绘图界面用户在绘制的时候进行控制
     */
    void setRectStyle(int istyle);


    /**
     * @brief       获取VisionGraph的工具栏的对象指针
     */
    QToolBar *getToolBar();


signals:
    void signal_itemFinished(VisionItem* item);
    void signal_Changed(VisionItem* item);

    void signal_RegionChanged();

    void signal_press(QMouseEvent *event);
    void signal_release(QMouseEvent *event);

    void signal_ViewFit();

    void signal_AddRegion(VGRegion *region, QColor color);
    void signal_AddRegionPair(vector<VGRegionPair> vec_regionPair);

private:
    void initScene();
    void initTool_operation();  //水平的工具栏
    void initToolBar();
    void initLayout(ToolButtonDirection toolButtonDirect);

    bool checkoutItem();

private:
    VisionGraphScene *scene = nullptr;
    VisionGraphView *view = nullptr;

    /*
     * 编辑和非编辑的item均存放在此链表中，方便进行释放内存
     * 若在add函数中创建的item不放入list中，clear会无法释放该item，
     * 提供的_add函数创建的item是不存放在list中，所以调用clear时不会释放item，主要用于在clear的时候不需要删除的 item
     * */
    QList<VisionItem*> m_lstItem;
    QList<VisionItem*> m_lstItemSelected;
    QList<VisionItem*> m_lstItem_unEdit;


    QList<QPointF> m_lstPainterPointF;  //绘制算法提供的直线的点的集合（两两配对）

//    XVCreateRegionIn regionIn;


    QGraphicsPixmapItem *m_bkPixmapItem = nullptr;  //背景图片
    QGraphicsPixmapItem *m_mousePixmap = nullptr;  //调整鼠标的大小的时候，显示在区域中心的图片

    qreal m_zoom = 1;   //图形View的缩放比例

    ToolButtonDirection  m_toolButtonDirection = ToolButtonDirection::topDirection;  //tool按钮的位置
    QToolBar *tool_Widget = NULL;


    int m_rectStyle = 0;

private:

    //左侧工具栏 -- 绘制类（操作类）
    QToolButton *sys_selected_button;
    QToolButton *sys_drag_button;
    QToolButton *sys_zoom_button;  //将拖动的恢复到当前窗口
    QToolButton *sys_fit_button;  //调整比例，适应当前窗口


    QToolButton *sys_mousePainter_button;
    QToolButton *sys_mouseClear_button;

    QToolButton *sys_save_button;

    QToolButton *sys_rect_button;
    QToolButton *sys_ellipse_button;
    QToolButton *sys_circle_button;
    QToolButton *sys_arc_button;
    QToolButton *sys_poly_button;
    QToolButton *sys_poly_elli_button;
    QToolButton *sys_point_button;
    QToolButton *sys_line_button;
    QToolButton *sys_polyLine_button;

    //右侧工具栏 -- 功能类
    QToolButton *sys_open_project_button;  //打开工程
    QToolButton *sys_front_button;  //撤销
    QToolButton *sys_next_button;   //取消撤销
    QToolButton *sys_clear_button;  //清空绘图区域
    QToolButton *sys_remove_item_button;  //删除当前选中的item

    QList<QToolButton*> m_lstToolBtn;
    QList<QToolButton*> m_lstToolBtn_Use;//记录界面在不同模式下的工具按钮

    QList<QAction*> m_lstAction;  //删除ToolButton使用的 ，必须要保证和m_lstToolBtn一致；其他的如，高度等widget，使用单独的删除接口
    QAction* m_insertAction;   //addToolButton,所需要添加的action的位置，是一个空的action（end），

    QSize m_ToolBtnSize = QSize(36,36);
    QSize m_ToolIconSize = QSize(36,36);
    Qt::ToolButtonStyle m_ToolStyle = Qt::ToolButtonIconOnly;//记录工具栏整体的ToolButtonStyle

    //显示的信息 -- 鼠标的移动坐标信息和操作信息
    QLabel *label_Operation = NULL;

    //记录item的类型  ====  同时也作为鼠标的状态标志 --- 鼠标事件发生的时候执行什么操作（绘制，清空，缩放，拖动等）
    ItemType m_itemType = ItemType::No;
    VisionItem* m_curVisionItem = nullptr;

    //鼠标直径相关信息
    QLabel *label_mouseSizeText = NULL;
    QLabel *label_slider = NULL;
    QSlider *pSlider = NULL;
    QAction *label_mouseSizeText_action = NULL;
    QAction *label_slider_action = NULL;
    QAction *pSlider_action = NULL;
    QAction *mouseSize_separator = NULL; //分隔符

    QSpinBox *pSpinBox = NULL;
    QLabel *label_w = NULL;
    QSpinBox *pSpinBox_w = NULL;
    QLabel *label_h = NULL;
    QSpinBox *pSpinBox_h = NULL;
    //缩放的比例显示
    QComboBox *comboBox = NULL;
    QLabel *label_size = NULL;
    QToolBar *tool_infoWidget = NULL;

    QVBoxLayout *mainLayout = NULL;   //主布局
    QHBoxLayout *m_hBoxLayout = NULL;
    QVBoxLayout *m_vBoxLayout = NULL;

    VisionGraphWidget *sceneWidget = NULL;

    QAction *infoWidget_Action;
    QWidget* infoWidget = NULL;

    GraphType m_graphType = GraphType::graphItem_unSelf;   //item的模式，用户交互绘制item？
    ViewType m_viewType = ViewType::freeItem;

    bool m_bWheel = false;   //comboBox值变化的 是否触发对应的槽函数，true，不触发，false 触发（wheel事件导致的缩放，均不触发）

    //记录算法区域 regionSize的原始大小，在背景图为空的时候，进行恢复
    qreal m_qOriginRegionSize_w = 800;
    qreal m_qOriginRegionSize_h = 600;

    QMenu *m_contextMenu = NULL;
    bool m_bContextMenu = false;  //上下文菜单默认关闭(暂时只针对非显示模式)

    Coordinate_Struct m_CoorItem;  //设置坐标系
    VisionCoordinateItem* m_CoorItem_Item = NULL;  //坐标系

private slots:
    //对应Action的槽函数
    void slot_selected_action();
    void slot_drag_action();
    void slot_zoom_action();
    void slot_fit_action();

    void slot_mousePainter_action();
    void slot_mouseClear_action();

    void slot_save_action();

    void slot_rect_action();
    void slot_ellipse_action();
    void slot_circle_action();
    void slot_arc_action();
    void slot_poly_action();
    void slot_poly_elli_action();
    void slot_point_action();
    void slot_line_action();
    void slot_polyLine_action();

    void slot_open_project();
    void slot_front_action();
    void slot_next_action();
    void slot_clear_action();
    void slot_removeItem_action();

    void slot_addItem(ItemType type, QRectF rf);
    void slot_addPoly(QVector<QPointF> vecPointF, ItemType type);
    void slot_addPoint(QPointF pointF);
    void slot_addLine(QLine line);


    //接收view传过来的MouseMoveEvent事件
    void slot_mouseMove(QPointF pointF);

    void slot_addRegion();
    void slot_ItemTypeChange();

private slots:
    void slot_Press(VisionItem *item, bool bSelected, bool bIn, qreal x, qreal y);

    void slot_wheel(qreal delta);
    //调节view的缩放比例
    void slot_SizeChanged(QString currentSize);
    void slot_SizeChanged(qreal w,qreal h);

    //调节鼠标绘制的时候，鼠标的半径
    void slot_valueChanged(int qR);  //绘制鼠标的半径

    void slot_SceneMouseMove(qreal x,qreal y);
    void slot_actionTriggered(QAction* action);

    void slot_SpinBox_ViewRegionSize(int w);

    //当GraphType变化的时候，调用该函数刷新
    void slot_GraphTypeChanged(GraphType type);

    void slotItemFinished(VisionItem* item);

    void slot_addRegionItem(VGRegion *region, QColor color);
    void slot_addRegionPairItem(vector<VGRegionPair> vec_regionPair);

private:
    void init_graph_info();
    void init_graphRegion();
    void init_graphItem_self();
    void init_graphItem_unSelf();
    void init_graphChain();
    void init_graphFitting();
    void init_graph_Item(GraphType type);

    void init_graph_ItemMode(ItemModes mode);

    void createContextMenu();

    void updateItemStatus();
private:
    //    Paint_Rect Paint_EllipseItem Paint_CirCle Paint_Poly Paint_polyLine Paint_Arc point line

    QColor borderColor_Rect,selectedColor_Rect,brushColor_Rect;
    QColor borderColor_Ellipse,selectedColor_Ellipse,brushColor_Ellipse;
    QColor borderColor_Circle,selectedColor_Circle,brushColor_Circle;
    QColor borderColor_Poly,selectedColor_Poly,brushColor_Poly;
    QColor borderColor_PolyLine,selectedColor_PolyLine,brushColor_PolyLine;
    QColor borderColor_Arc,selectedColor_Arc,brushColor_Arc;
    QColor borderColor_Point,selectedColor_Point,brushColor_Point;
    QColor borderColor_Line,selectedColor_Line,brushColor_Line;

    QColor borderColor_Region,selectedColor_Region,brushColor_Region;

protected:
    void paintEvent(QPaintEvent *event);

    void contextMenuEvent(QContextMenuEvent *event) override;//右击即可呼出上下文Menu菜单

public:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

};

#endif // VISIONGRAPH__H
