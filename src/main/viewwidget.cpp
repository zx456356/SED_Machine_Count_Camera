#include "viewwidget.h"
#include "ui_viewwidget.h"

ViewWidget::ViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewWidget)
{
    ui->setupUi(this);

    vgView = new VisionGraph(GraphType::graph_Info);
    vgView->setGraphType(GraphType::graph_Info,item_NO);
    ui->gridLayout->addWidget(vgView);
    vgView->setViewInfo_Visible(true);
    vgView->setViewInfo_Pos(Corner::topLeft);
    vgView->setViewInfo_Size(300, 100);

}

ViewWidget::~ViewWidget()
{
    delete ui;
}

void ViewWidget::fileFetch()
{
    FilePath = ui->imgPathEdit->text();
    QDir dir(FilePath);
    infolist = dir.entryInfoList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);

    if(FilePath.isEmpty() == false && infolist.count() > 0)
    {
        info = infolist.at(imgNum);
        QString subDir = info.absoluteFilePath();
        //std::string str = code->fromUnicode(subDir).data();
        QImage qimg;

        if(nextImg == true && info.isFile())
        {
            qimg.load(subDir);
            vgView->clearPainter();
            vgView->setBkImg(qimg);
            vgView->addText(QString::number(imgNum+1) + "/" + QString::number(infolist.count()),
                            18, QPointF(0, 0), QColor(255, 0, 0));


            nextImg = false;
        }
    }
}

void ViewWidget::on_chooseButton_clicked()
{
    FilePath = QFileDialog::getExistingDirectory();
    if(FilePath.isEmpty() == false)     // 判断是否选择文件夹
    {
        QDir dir(FilePath);
        infolist = dir.entryInfoList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot);
    }
    else
    {
        infolist.clear();   // 清除列表
    }
    ui->imgPathEdit->setText(FilePath);

    imgNum = 0;
    nextImg = true;
    fileFetch();
    vgView->setViewSize_Fit();

}

void ViewWidget::on_preImgButton_clicked()
{
    nextImg = true;
    imgNum--;
    if(imgNum < 0)
    {
        imgNum = infolist.count() - 1;
    }
    fileFetch();
}

void ViewWidget::on_nextImgButton_clicked()
{
    nextImg = true;
    imgNum++;
    if(imgNum > infolist.count() - 1)
    {
        imgNum = 0;
    }
    fileFetch();
}

void ViewWidget::on_firstImgButton_clicked()
{
    nextImg = true;
    imgNum = 0;
    fileFetch();

}

void ViewWidget::on_finalImgButton_clicked()
{
    nextImg = true;
    imgNum = infolist.count()-1;
    fileFetch();
}




