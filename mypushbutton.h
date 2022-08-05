#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);
    //normaImg正常显示的图标,pressImg变化的实现
    MyPushButton(QString normalrIamge,QString presImage="");
    QString normalImagePath;
    QString pressIamgePath;
    static bool Error;
    //向下弹起
    void zoom1();
    //向上弹起
    void zoom2();

    //鼠标按下
    void mousePressEvent(QMouseEvent *);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent *);
signals:
};
#endif // MYPUSHBUTTON_H
