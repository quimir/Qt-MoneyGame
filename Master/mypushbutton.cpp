#include "mypushbutton.h"
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include <QPropertyAnimation>
#include <QApplication>

MyPushButton::MyPushButton(QWidget *parent)
    : QPushButton{parent}
{
}
bool MyPushButton::Error=true;
MyPushButton::MyPushButton(QString normalrImage,QString presImage)
{
    this->normalImagePath=normalrImage;
    this->pressIamgePath=presImage;
    //QPixmap加载图片
    QPixmap pix;
    bool ret=pix.load(normalImagePath);
    if(!ret)
    {
        QMessageBox *messagebox=new QMessageBox();
        QString str=QString("图片加载失败%1").arg(normalrImage);
        messagebox->critical(this,"严重错误","本图片无法加载即将退出程序",QMessageBox::StandardButton::Close);
        qDebug()<<str;
        MyPushButton::Error=false;
        return;
    }
    //设置图片大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不透明风格
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}
void MyPushButton::zoom1()
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置弹起效果
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //让动画执行
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
void MyPushButton::zoom2()
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹起效果
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //让动画执行
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    //如果按下图片路径不为空代表需要切换图片
    if(this->pressIamgePath!="")
    {
        QPixmap pix;
        bool ret=pix.load(pressIamgePath);
        if(!ret)
        {
            QString str=QString("图片加载失败%1").arg(pressIamgePath);
            qDebug()<<str;
            MyPushButton::Error=false;
            return;
        }
        //设置图片大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不透明风格
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //点击的响应事件抛给父类
    QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressIamgePath!="")
    {
        QPixmap pix;
        bool ret=pix.load(this->normalImagePath);
        if(!ret)
        {
            QString str=QString("图片加载失败%1").arg(normalImagePath);
            //            qDebug()<<str;
            MyPushButton::Error=false;
            return;
        }
        //设置图片大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不透明风格
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //点击的响应事件抛给父类
    QPushButton::mouseReleaseEvent(e);
}
