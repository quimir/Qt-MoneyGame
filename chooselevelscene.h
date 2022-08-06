#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "mypushbutton.h"
#include "playgame.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //重写绘图事件
    void paintEvent(QPaintEvent*);
    PlayGame *playgame;

    //创建显示关卡的标签
    void textLabel(MyPushButton *menuBtn, int i);

signals:
//点击返回按钮后抛出自定义信号
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
