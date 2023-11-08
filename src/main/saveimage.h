#ifndef SAVEIMAGE_H
#define SAVEIMAGE_H

#include <QObject>
#include <QRunnable>
#include <QImage>
#include <QDir>
#include <QTime>
#include <QDebug>
#include <QThread>


class SaveImage : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit SaveImage(QObject *parent = nullptr);

    void init(QImage qImage, QString savePath);

protected:

    //void run();


private:
    QImage qImage;
    QString savePath;


};

#endif // SAVEIMAGE_H
