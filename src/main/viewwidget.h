/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       viewwidget.h
 * @brief      查看图片 Function
 *
 * @author     yyf
 * @date       2022/08/18
 * @history
 *****************************************************************************/

#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QTextCodec>
#include <QFileInfoList>
#include <QFileInfo>
#include <QDebug>

#include "VGBase.h"
#include "visiongraph.h"

namespace Ui {
class ViewWidget;
}

class ViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ViewWidget(QWidget *parent = nullptr);
    ~ViewWidget();

public slots:
    //文件取图
    void fileFetch();
    //前一张
    void on_preImgButton_clicked();
    //后一张
    void on_nextImgButton_clicked();
    //选择文件夹
    void on_chooseButton_clicked();
    //第一张
    void on_firstImgButton_clicked();
    //最后一张
    void on_finalImgButton_clicked();

public:

    Ui::ViewWidget *ui;
    VisionGraph *vgView;

    QFileInfoList infolist;          // 文件路径列表
    QFileInfo info;                   // 存储文件路径
    QTextCodec *code;           // 字符转码
    QString FilePath;

    bool nextImg;
    int imgNum;
};

#endif // VIEWWIDGET_H
