#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QElapsedTimer>
#include <QDebug>
#include <QSettings>
#include <QTextBrowser>
#include <QMutex>
#include <QFile>
#include <QDir>
#include <QTreeWidgetItem>
#include <QLine>
#include <QDate>
#include <QScrollArea>
#include <QThread>
#include <QThreadPool>
#include <QDockWidget>


#include <QChartView>
#include <QChart>



QT_CHARTS_USE_NAMESPACE

#include <QLineSeries>
#include <QAbstractAxis>
//#include <QtCharts/QValueAxis>

#include "viewwidget.h"
#include "CountGrain.h"



#include "../include/xvlog.h"
#include "../include/xvlogwidget.h"

#include "login.h"
#include "ui_login.h"
#include "settingwidget.h"
#include "viewwidget.h"
#include "ui_viewwidget.h"
#include "tinyxml2.h"

#pragma execution_character_set("utf-8")

using namespace  XVL;
using namespace HalconCpp;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SaveImage : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit SaveImage(QObject *parent = nullptr){}
    ~SaveImage(){}

    void init(QImage qImage, QString savePath, QString currentMode, int minAreaSet, int maxAreaSet, int minRadiusSet, int maxRadiusSet){
        SaveImage::qImage = qImage;
        SaveImage::savePath = savePath;
        SaveImage::currentMode = currentMode;
        SaveImage::minAreaSet = minAreaSet;
        SaveImage::maxAreaSet = maxAreaSet;
        SaveImage::minRadiusSet = minRadiusSet;
        SaveImage::maxRadiusSet = maxRadiusSet;
        SaveImage::isErrorImage = false;
    }

protected:

    void run();

    QImage drawResultImage(QImage qImage, QString showOrSave);

private:
    QImage  qImage;
    QString savePath;
    QString currentMode;
    bool    isErrorImage;

   // SettingWidget st;

    int     minAreaSet, maxAreaSet, minRadiusSet, maxRadiusSet;
    HObject ho_ObjectSelected3, ho_Rectangle;
    HTuple  hv_Row4, hv_Column4, hv_Row5, hv_Column5;
    HTuple  ho_AreaS, ho_RadiusS;

    QVector<double> wArea, wRadius;

};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;

    login *loginWindow;
    VisionGraph *vg;
    SettingWidget *set;
    ViewWidget *view;
    uint8_t m0[1],m1[1],m354[1],m355[1];
    int    X1,overdoseWarn;
    QChart *chart = new QChart();
    QTimer *LEDFlashTimer;
    bool EStoped;

    void setLED(QLabel* label, int color, int size);
    static MainWindow *mw;
    void ChangeShaker1VText();
    void ChangeShaker2VText();
    void ChangeShaker3VText();
    void HandModeStop();
    void ExitProgram();
    void SingleNumBoxChanged();
    bool workingState;
    void LedFlash();
    int FlashTimes;
    void iniLeftBar();

private:
    //工具栏初始化
    void toolBarInit();
    QImage drawResultImage(QImage qImg, QString showOrSave);
    void saveImageO();
    void setLog(XVLogWidget* Log);
    void dev_open_window_fit_image (HObject ho_Image, HTuple hv_Row, HTuple hv_Column,
    HTuple hv_WidthLimit, HTuple hv_HeightLimit, HTuple *hv_WindowHandle);
    void BkIMgFit();

    //translation
    bool loadXML();
    void loadTranslation(const char*);
    QString findTranslation(const char*);
    void writeCurrToXML(const char*);
    void XVRegionStudy();


signals:
    void signal_showImage(QImage);
private slots:

    //定时刷新显示相关数据
    void Showexec();
    //窗口关闭时间
    void closeEvent(QCloseEvent * event);
    void resizeEvent(QResizeEvent *event);
    //登录点击事件
    void on_login_toggled(bool arg1);
    //开始按钮点击事件
    void on_start_toggled(bool arg1);
    //登录界面确认事件
    void loginBtn();
    //登录界面取消事件
    void loginCancelBtn();
    //登录界面关闭事件
    void loginClose();
    //主界面点击事件
    void on_mainInterfaceAction_triggered();
    //参数设置界面点击事件
    void on_setInterfaceAction_triggered();
    //查看图片界面点击事件
    void on_imageInterfaceAction_triggered();
    //图片定时刷新
    void ShowImage();
    void slot_showImage(QImage);
    void on_clearBtn_clicked();
    void on_saveImgBtn_toggled(bool checked);
    void on_studyBtn_toggled(bool checked);
    //void on_fillBtn_clicked();
    //void on_cancelBtn_clicked();
    //void on_start_triggered();
    void on_FullScreen_toggled(bool arg1);
    void on_Exit_triggered();
    void on_startBtn_released();
    void on_stopBtn_released();
    void on_resetBtn_released();
    void on_startBtn_pressed();
    void on_stopBtn_pressed();
    void on_resetBtn_pressed();
    void on_clearBottleBtn_pressed();
    void on_clearBottleBtn_released();
//    void on_clearBufferBtn_toggled(bool checked);
    void on_beltPowerBtn_toggled(bool checked);
    void on_clearBufferBtn_pressed();
    void on_clearBufferBtn_released();
    void on_shaker1Add_clicked();
    void on_shaker1Dec_clicked();
    void on_shaker2Add_clicked();
    void on_shaker2Dec_clicked();
    void on_shaker3Add_clicked();
    void on_shaker3Dec_clicked();
    void on_singleNumBox_editingFinished();
    void on_Shaker1VBox_editingFinished();
    void on_Shaker2VBox_editingFinished();
    void on_Shaker3VBox_editingFinished();

private:
    QDockWidget * dockLog;  //日志停靠窗口
    QThread * saveImgThread;
    QThreadPool *saveImgPool;

    QLabel *dateLab;
    QLabel *timeLab;

    bool isErrorImage;
    QQueue<QImage> wRImage, wEImage;

    GrainDataLearnIn learnAreaInArea, learnAreaInRadius;
    GrainDataLearnOut learnAreaOut;

    int     percentage;  //progressbar
    tinyxml2::XMLDocument    xmlDoc;
    tinyxml2::XMLError       xmlErr;
    tinyxml2::XMLElement     *xmlEle;

};
#endif // MAINWINDOW_H
