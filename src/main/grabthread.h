#ifndef GRABTHREAD_H
#define GRABTHREAD_H
#include <QThread>
#include <QImage>

class grabThread : public QThread
{
    Q_OBJECT
public:
    grabThread();
    void run();

    void quit();

    bool isQuit;

signals:

    void sendImage(QImage img);

private:

    QVector<QRgb> grayColourTable;

    QVector<QRgb> ColourTable;



};

#endif // GRABTHREAD_H
