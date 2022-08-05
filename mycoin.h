#ifndef MYCOIN_H
#define MYCOIN_H

#include <QTimer>
#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);
    //默认显示图片
    MyCoin(QString image);

    //x坐标
    int posX;

    //y坐标
    int poxY;

    //正反标志
    bool flag;

    //该表标志
    void changeFlag();
    //正面翻反面的定时器
    QTimer *timer1;
    //反面翻正面的定时器
    QTimer *timer2;
    //最小图片
    int min=1;
    //最大图片
    int max=8;

    //做动画标志
    bool isAnimation=false;

    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *);

    //是否胜利的状态
    bool isWin=false;


signals:

};

#endif // MYCOIN_H
