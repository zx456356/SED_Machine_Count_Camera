/****************************************************************************
** @brief       VisionGraph,绘制模块的widget
** @note        会生成一个widget来进行展示绘制模块，综合了region和item两种版本
** @author      xiaodongLi
** @date        create:2018-10-24
** @example
****************************************************************************/

#ifndef VISIONGRAPH_H
#define VISIONGRAPH_H

#include <QWidget>
#include <QWheelEvent>

#include "visiongraph_global.h"
#include "visiongraphtool.h"
#include "visiongraph_.h"

class VISIONGRAPHSHARED_EXPORT VisionGraph : public QWidget
{
    Q_OBJECT
public:
    VisionGraph(GraphType type = GraphType::graph_Info, ToolButtonDirection toolButtonDirect = ToolButtonDirection::topDirection, QWidget *parent = 0);

    /*
     * 测试用，接口不开放
     * 测试visionGraph窗口的边框的数值，即merge
     * */
    void setBorderValue(int left=0, int top=0, int right=0, int bottom=0);

    ~VisionGraph();

    /**
     * @brief       设置sceneWidget的大小
     * @param
     */
    void setSceneWidgetSize(QSize size);
    void setSceneWidgetSize(qreal w,qreal h);

    /**
     * @brief       设置GraphType，VisionGraph的版本，
     * @param       //此接口作废---使用此接口和设置工具栏Direction，会导致工具栏出问题（内部调用）
     * @param       此接口在构造VisionGraph后不可更改
     */
    void setGraphType(GraphType type, ItemModes mode);

    /**
     * @brief       主题颜色设置
     * @param       设置对应的矩形，椭圆，区域等边框颜色、填充颜色等
     */
    void setThemeColor(ThemeColor theme);

    /**
     * @brief       添加rectangle  可旋转的矩形
     * @param       bEdit 表示编辑
     */
    VisionRectItem *addRect(QRectF rf,qreal angle = 0, bool bEdit = true,bool bRotation = true,bool color_enable = false,
                            QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       _addRect()等带下划线的api，为非编辑控件，且不同于addRect()生成的非编辑控件。
     * @note        带下划线的均无法通过clearPainter()函数进行清除，只能通过scene的clear进行清空（释放），
     * @note        或者通过外部接收返回值进行释放内存，而addRect()生成的非编辑控件在clearPainter()函数进行清除，会释放掉内存占用
     */
    QGraphicsRectItem* _addRect(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());

    QGraphicsPolygonItem* _addPolygon(const QPolygonF &polygon, const QPen &pen = QPen(), const QBrush &brush = QBrush());

    QGraphicsLineItem* _addLine(const QLineF &line, const QPen &pen = QPen());

    QGraphicsEllipseItem* _addEllipse(const QRectF &rect, const QPen &pen = QPen(), const QBrush &brush = QBrush());

    VisionCrossPointItem* _addPoint(QPointF pointF, bool edit = false, qreal length = 5,
                                    bool color_enable = false,QColor color = QColor(255,0,0));

    VisionArrow *_addArrow(QPointF pointF, bool bEdit = false, bool color_enable = false,QColor color = QColor(255,0,0 ));

    VisionChainItem* _addChain(QList<QPointF> lstP, bool bClosed = false, bool bEdit = false,
                               bool color_enable = false,QColor color = QColor(255,0,0));

    VisionCoordinateItem *_addCoordinate(QPointF p,qreal angle = 0,qreal length = 50,bool bEdit = true,
                                        bool color_enable = false,QColor color = QColor(255,0,0));

    /**
     * @brief       添加椭圆
     * @param       默认是可编辑的
     */
    VisionEllipseItem* addEllipse(QRectF rf,qreal angle = 0,bool bEdit = true, bool bRotation = true,bool color_enable = false,
                                  QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加圆
     * @param       默认是可编辑的
     */
    VisionCircleItem* addCircle(QRectF rf, bool bEdit = true,bool color_enable = false,
                                QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加圆弧
     * @param       默认是可编辑的
     */
    VisionArcItem *addArc(QPointF sP,QPointF mP,QPointF fP, bool bEdit = true,
                          bool color_enable = false,
                          QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));
    VisionArcItem *addArc(QPointF center,qreal r,qreal angle,qreal spanAngle, bool bEdit = true,
                          bool color_enable = false,
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
    VisionLine* addLines(QList<QLineF> lstLineF,bool color_enable = false, QColor color = QColor(255,0,0));


    /**
     * @brief       添加多边形 ,close为false，为折线
     * @param       点的集合，点的集合一次连接
     * @note        polygon等价path。addPath()或者addPaths()
     */
    VisionPolygon* addPolygon(QVector<QPointF> vecPointF, bool bClose = true, bool bEdit = false,
                              bool color_enable = false,
                              QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加一个点
     * @param
     */
    VisionCrossPointItem* addPoint(QPointF pointF, bool bEdit = false, qreal length = 5,
                                   bool color_enable = false,
                                   QColor borderColor = QColor(255,0,0),QColor selectedColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160));

    /**
     * @brief       添加点 -- 不限数量
     * @param       当point数量达到一定的程度的时候，addPoint()会非常耗时。
     * @note        addPointFs()在绘制大数量的point的时候，会节省很多时间
     */
    VisionPoint *addPointFs(QList<QPointF> lstP, bool color_enable = false,QColor color = QColor(255,0,0));

    /**
     * @brief       添加一个链
     * @param       链--多个点集合形成的一个空间，每两个点之间的连线存在方向（箭头），和path以及polygon类似
     */
    VisionChainItem *addChain(QList<QPointF> lstP, bool close = false,bool edit = true,
                              bool color_enable = false,
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
     * @brief       获取当前绘制在view的区域  region版本
     * @param       XVRegion
     */
    XVRegion *getRegion();

    /**
     * @brief       获取当前view中的所有的item
     * @param       VisionItem*
     */
    QList<VisionItem*> getItems();


    /**
     * @brief       添加坐标系
     * @param       默认是不可编辑.当前不支持编辑坐标系（拖动，旋转等操作）
     * @note        该api生成的坐标系会在调用clearPaint()函数被清除（要想一直保持坐标系存在，调用_addCoordinate().）
     */
    VisionCoordinateItem *addCoordinate(QPointF p,qreal angle = 0,qreal length = 50,bool bEdit = true,
                                        bool color_enable = false,QColor color = QColor(255,0,0));


    /**
     * @brief       添加文本控件
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

    /**
     * @brief       添加区域(多区域)
     * @param       默认是不可编辑.当前不支持编辑（拖动，旋转等操作）
     */
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
     * @brief       设置VisionGraph的背景，区分版本
     */
    void setBkImg(QImage image);

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
     * @brief      设置颜色(选中)
     * @param       设置所有的item
     */
    void setSelectedColor(QColor color);


    /**
     * @brief      设置颜色(边框)
     * @param       设置所有的item
     */
    void setBorderColor(QColor color);


    /**
     * @brief      设置颜色(填充)
     * @param       设置所有的item
     */
    void setBrushColor(QColor color);


    /**
     * @brief      显示VisionGraph
     * @param       重载widget的show()
     */
    void show();


    /**
     * @brief       获取view
     * @param       在某些情况下，需要visionGraph的view指针
     */
    VisionGraphView* getView();


    /**
     * @brief       修改绘制的item时候触发
     * @param       在使用鼠标移动进行绘制任意区域的时候，鼠标本身的大小作为绘制要素之一
     * @param       绘制不同的item，有不同的鼠标样式
     */
    void setPainterCursorR(qreal qR);

    /**
     * @brief       设置记录当前所要绘制的item
     */
    void setItemType(ItemType type);


    /**
     * @brief       view的缩放比例
     */
    void zoom(float scaleFactor);


    /**
     * @brief       撤销区域生成
     * @note        绘制区域的撤销操作--和恢复操作对应
     */
    void back_region();


    /**
     * @brief       恢复区域生成
     * @note        绘制区域的恢复操作--和撤销操作对应
     */
    void front_region();


    /**
     * @brief       清除view的绘制数据
     * @note        清除view中绘制的所有的item，并释放所有的item的内存（不包含_add*函数调用生成的item）
     */
    void clearPainter();

    /**
     * @brief       设置View信息框的显示或者隐藏
     * @note        信息框包含，当前鼠标的坐标位置、rgb、灰度值、自定义文本等
     */
    void setViewInfo_Visible(bool bVisible);

    /**
     * @brief       设置View信息框的位置（四个拐角）
     * @note        信息框在view中的显示位置
     */
    void setViewInfo_Pos(Corner corner);

    /**
     * @brief       设置View信息框的位置（任意位置）
     * @note        信息框在view中的显示位置
     */
    void setViewInfo_Pos(qreal x,qreal y);

    /**
     * @brief       设置View信息框的大小
     */
    void setViewInfo_Size(QSize size);

    /**
     * @brief       设置View信息框的大小
     */
    void setViewInfo_Size(qreal w,qreal h);


    /**
     * @brief       设置View信息框的文本
     * @note        信息框可显示自定义文本
     */
    void setViewInfo_text(QString text);

    /**
     * @brief       设置View信息框的颜色
     * @note        （背景颜色和文本颜色）目前暂未实现该功能
     */
    void setViewInfo_Color(QColor backgroundColor, QColor textColor);

    /**
     * @brief       设置工具栏ToolButton的icon的路径
     */
    void setIconPath(QString iconpath);


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
     * @note        view中的算法区域的w和h，缩放比例，鼠标的直径。
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
     * @brief       在工具栏添加frame布局
     * @param        todo,未实现
     */
    void addToolFrame();

    /**
     * @brief       设置View的算法区域的大小
     * @note        即算法中的有效区域
     */
    void setViewRegion_Size(qreal w,qreal h);


    /**
     * @brief       设置View的算法区域的Visible
     */
    void setViewRegion_Visible(bool bVisible);

    /**
     * @brief       设置View的算法区域的color
     * @note        主要是区域的边框颜色
     */
    void setViewRegion_Color(const QColor &color);

    //补充工具栏的相关api和信息获取
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
     * @brief       设置view Scene的位置
     * @param       rf是scene在view的相对位置，通过，view->scene()->sceneRect()获取
     */
    void setSceneRect_View(QRectF rf);

    /**
     * @brief       获取view Scene的位置
     * @param       和setSceneRect_View是相对的
     */
    QRectF getSceneRect_View();


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
     * @param
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
     * @brief       获取VisionGraph的样式表
     * @param
     */
    void setGraphStyleSheet(QString strStyleSheet);

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

    //region主要是brushColor有效
    void setRegionColor(QColor borderColor = QColor(255,0,0),QColor selectColor = QColor(255,0,0),QColor brushColor = QColor(255,0,0,160),
                        QColor brushColor_unEdit = QColor(255,0,0,200));

    /**
     * @brief       获取上下文菜单的某一菜单选项
     * @param       注意strText的编码格式， 当确认存在的时候，但是返回值确实NULL，很可能是由于strText乱码、或者未支持多语言
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
     * @brief       设置上下文菜单是否显示
     * @param       目前上下文菜单显示的前提条件是：
     * @note        上文菜单实例存在（内部），拖动或者选择模式（根据鼠标状态），visionGraph是显示模式或者强制开启上下文菜单（外部设置）--- 三者是&&关系
     * @note        visionGraph在graph_Info模式下默认是开启（暂时不可关闭），在其他模式可通过该函数setContextMenu_Visible进行显示或者关闭
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


    /**
      * @brief      设置鼠标样式是否生效
      * @note       主要用于显示数据的时候，鼠标样式切换过于影响美观(仅仅在GraphType==graph_Info有效，其他禁止使用，使用也无效)
      * @param      enable为true--正常变换鼠标样式（选择模式，拖动模式等），false--鼠标样式默认不做改变，但是此时的mouseMove一定是拖动，只是鼠标上面不能直观的看到
      * @note       默认是true，仅仅在GraphType==graph_Info有效，其他禁止使用，使用也无效。
      * @note       该接口内部会调用setItemType(ItemType::Drag)
      * */
    void setMouseStyleEnable(bool enable = true);


    /**
     * @brief       获取VisionGraph的工具栏的对象指针
     */
    QToolBar *getToolBar();


    //内部测试使用
    VisionGraph_* getVisionGraph(){
        return m_graphWidget;
    }

signals:
    void signal_PaintFinishedChanged(VisionItem*);
    void signal_Changed(VisionItem* item);

    void signal_RegionChanged();
    void signal_MousePress(QMouseEvent *event);
    void signal_MouseRelease(QMouseEvent *event);

    void signal_ViewFit();  //通知外部用户使用了自适应
protected:
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    VisionGraph_ *m_graphWidget = nullptr;
    GraphType m_graphType = GraphType::graphItem_unSelf;
    QVBoxLayout *mainLayout = NULL;

    QColor selectedColor = QColor(255,0,0);
    QColor borderColor = QColor(0,0,0);
    QColor brushColor = QColor(255,0,0,50);
    QColor regionColor = QColor(255,0,0);  //暂时和brushColor合并

    //暂时未用，
    QColor viewMouseInfo_TextColor = QColor(255,255,255);
    QColor viewMouseInfo_BackgroundColor = QColor(255,255,255);


    QString iconPath = "./ico/graph/";

//    QCursor viewCursor;
};

#endif // VISIONGRAPH_H
