#include "mainwindow.h"
#include <QApplication>
#include "logwidget.h"
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    //qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv);

    QPixmap pixmap(QApplication::applicationDirPath()+"/ico/SED.bmp");//创建QPixmap对象，设置启动图片
    QSplashScreen splash(pixmap);//利用QPixmap对象创建一个QSplashScreen对象
    splash.show();//显示此启动图像
    a.processEvents();//使程序在显示启动画面时仍能响应鼠标等其他事件
    MainWindow w;
    w.show();
    splash.finish(&w);//表示在主窗体对象初始化完成后,结束启动画面
    return a.exec();
}

