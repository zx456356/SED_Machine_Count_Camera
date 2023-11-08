#ifndef UNITSPAINBOX_H
#define UNITSPAINBOX_H
#include <QSpinBox>
#include <QPushButton>

class UnitSpainBox : public QSpinBox
{
    Q_OBJECT
public:
    UnitSpainBox(QWidget* parent = Q_NULLPTR);
    ~UnitSpainBox();
    //获取编辑框单位
    QString UnitText()const;

    //设置编辑框单位
    void SetUnitText(const QString& unitText,int FontSize);

private:
    QPushButton* m_unitButton = nullptr;//单位文本按钮
};

#endif // UNITSPAINBOX_H
