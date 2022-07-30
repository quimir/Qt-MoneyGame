#include "chooselevelscene.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QSoundEffect>

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    :QMainWindow(parent)
{

    //设置音效
    QSoundEffect *chooseSound=new QSoundEffect(this);
    chooseSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    QSoundEffect *backSound=new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));

    //设置任务栏
    QMenuBar *bar=menuBar();
    QMenu *startMenu=bar->addMenu("开始");
    QAction *quitAction=startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=]()
    {
        this->close();
    });
    this->setWindowTitle("选择关卡");
    this->setFixedSize(320,588);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //返回按钮
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&MyPushButton::clicked,[=]()
    {
        backSound->play();
        //延时发送信号
        QTimer::singleShot(350,this,[=]()
        {
            emit this->chooseSceneBack();
        });
    });
    playgame=nullptr;
    for(int i=0;i<20;i++)
    {

        //设置选择关卡按钮
        MyPushButton *menuBtn=new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+(i%4)*70,130+(i/4)*70);
        connect(menuBtn,&MyPushButton::clicked,[=]()
        {
            //            qDebug()<<"你选着的是第"<<i+1<<"关";
            chooseSound->play();
            playgame=new PlayGame(i+1);
            this->hide();
            this->playgame->setGeometry(this->geometry());
            this->playgame->show();
            //监听游戏场景中发生的自定义信号
            connect(playgame,&PlayGame::backUp,[=]()
            {
                this->setGeometry(this->playgame->geometry());
                delete this->playgame;
                this->playgame=nullptr;
                this->show();
            });
        });
        ChooseLevelScene::textLabel(menuBtn,i);
    }
}
void ChooseLevelScene::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPixmap pix;
    //加载图片
    pix.load(":/res/OtherSceneBg.png");
    //放置图片
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载上面的图片
    pix.load(":/res/Title.png");
    //放置图片
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);
}
void ChooseLevelScene::textLabel(MyPushButton *menuBtn,int i)
{
    //创建显示具体关卡号的label
    QLabel *label=new QLabel;
    //设置关卡号的颜色
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    label->setPalette(pe);
    label->setParent(this);
    //设置关卡号的大小
    label->setFixedSize(menuBtn->width(),menuBtn->height());
    label->setText(QString::number(i+1));
    label->move(25+(i%4)*70,130+(i/4)*70);
    //设置居中
    label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    //设置鼠标穿透事件  51号    鼠标穿透
    label->setAttribute(Qt::WA_TransparentForMouseEvents);
}
