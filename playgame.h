#ifndef PLAYGAME_H
#define PLAYGAME_H

#include <QMainWindow>
#include <QObject>
#include "dataconfig.h"
#include "mycoin.h"
#include <QLabel>

class PlayGame : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayGame(QWidget *parent = nullptr);
    PlayGame(int leaveIndex);
    //具体选择的关卡号
    int leaveIndex;
    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //记录当前关卡的二维数组
    int gameArray[4][4];

    //放置金币的二维数组
    MyCoin *coinBtn[5][5];


    //胜利标志
    bool isWin=true;


    //初始化二维数组
    void chushi(dataConfig e);


    //设置动画下降
    void down(QLabel *);

    //初始化胜利图片
    void Win(QLabel *winLabel);

    //用户选择标签
    void textLabel();


signals:
    void backUp();
};

#endif // PLAYGAME_H
