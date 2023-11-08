/******************************************************************************
 * Copyright 2020-xxxx xxx Co., Ltd.
 * All right reserved. See COPYRIGHT for detailed Information.
 *
 * @file       viewwidget.h
 * @brief      �鿴ͼƬ Function
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
    //�ļ�ȡͼ
    void fileFetch();
    //ǰһ��
    void on_preImgButton_clicked();
    //��һ��
    void on_nextImgButton_clicked();
    //ѡ���ļ���
    void on_chooseButton_clicked();
    //��һ��
    void on_firstImgButton_clicked();
    //���һ��
    void on_finalImgButton_clicked();

public:

    Ui::ViewWidget *ui;
    VisionGraph *vgView;

    QFileInfoList infolist;          // �ļ�·���б�
    QFileInfo info;                   // �洢�ļ�·��
    QTextCodec *code;           // �ַ�ת��
    QString FilePath;

    bool nextImg;
    int imgNum;
};

#endif // VIEWWIDGET_H
