#include "mycoin.h"
#include <QDebug>
#include <QTimer>

//MyCoin::MyCoin(QWidget *parent)
//    : QWidget{parent}
//{

//}
MyCoin::MyCoin(QString image)
{
    QPixmap pix;
    bool ret=pix.load(image);
    if(!ret)
    {
        qDebug()<<"图片加载失败"<<image;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器
    timer1=new QTimer(this);
    timer2=new QTimer(this);

    //监听两个定时器的timeout信号
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1").arg(this->min++);
        bool ret=pix.load(str);
        if(!ret)
        {
            qDebug()<<"图片加载失败"<<image;
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));\
        if(this->min>this->max)
        {
            //还原最小值的值
            this->min=1;
            //改为做动画
            this->isAnimation=false;
            timer1->stop();
        }

    });
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1").arg(this->max--);
        bool ret=pix.load(str);
        if(!ret)
        {
            qDebug()<<"图片加载失败"<<image;
            return;
        }
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));\
        if(this->max<this->min)
        {
            //还原最大值的值
            this->max=8;
            this->isAnimation=false;
            timer2->stop();
        }

    });

}
void MyCoin::changeFlag()
{

    //如果金币标识改银币
    if(this->flag)
    {
        timer1->start(30);
        this->isAnimation=true;
        this->flag=false;
    }
    //银币改金币
    else
    {
        timer2->start(30);
        this->isAnimation=true;
        this->flag=true;
    }
}
void MyCoin::mousePressEvent(QMouseEvent *e)
{
    //如果做动画那么不相应
    if(this->isAnimation||this->isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
