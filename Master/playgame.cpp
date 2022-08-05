#include "playgame.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <mypushbutton.h>
#include <QTimer>
#include <QPainter>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSoundEffect>

PlayGame::PlayGame(int leave)
{
    this->leaveIndex=leave;
    //设置窗口
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币");


    //返回按钮的音效
    QSoundEffect *backSound=new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));

    //点击金币按钮的音效
    QSoundEffect *playGold=new QSoundEffect(this);
    playGold->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));


    //设置获胜音效
    QSoundEffect *playWin=new QSoundEffect(this);
    playWin->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));


    //设置标题栏
    QMenuBar *bar=menuBar();
    this->setMenuBar(bar);
    QMenu *startMenu=bar->addMenu("开始");
    QAction *quitAction=startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=]()
    {
        this->close();
    });
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    connect(backBtn,&MyPushButton::clicked,[=]()
    {
        backSound->play();
        //回到上一个页面
        QTimer::singleShot(350,this,[=]()
        {
            emit this->backUp();
        });
    });

    PlayGame::textLabel();


    //初始化
    dataConfig config;
    //初始化二维数组
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            this->gameArray[i][j]=config.mData[this->leaveIndex][i][j];
    QLabel *winLabel=new QLabel;
    PlayGame::Win(winLabel);


    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {

            //创建金币的背景
            QLabel *lb=new QLabel;
            QPixmap Map;
            Map.load(":/res/BoardNode.png");
            lb->setGeometry(0,0,Map.width(),Map.height());
            lb->setPixmap(Map);
            lb->setParent(this);
            lb->move(57+i*Map.width(),200+j*Map.height());

            QString str;
            if(this->gameArray[i][j])
            {
                str=":/res/Coin0001.png";
            }
            else
            {
                str=":/res/Coin0008.png";
            }
            //创建金币图标
            MyCoin *coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*Map.width(),204+j*Map.height());

            //金币属性赋值
            coin->posX=i;
            coin->poxY=j;
            coin->flag=this->gameArray[i][j];

            //将金币放入二维数组中
            coinBtn[i][j]=coin;

            //监听点击按钮的信号
            connect(coin,&MyCoin::clicked,[=]()
            {
                playGold->play();
                //将所有的按钮都屏蔽
                for(int k=0;k<4;k++)
                {
                    for(int m=0;m<4;m++)
                    {
                        coinBtn[k][m]->isWin=true;
                    }
                }


                coin->changeFlag();

                //同步二维数组，如果以后有保存需求，可以用数组还原
                this->gameArray[i][j]=(this->gameArray[i][j]==1?0:1);

                //延时反转

                QTimer::singleShot(300,this,[=](){
                    //反转周围金币
                    //检查右侧
                    if(coin->posX+1<=3)
                    {
                        coinBtn[coin->posX+1][coin->poxY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->poxY]=(this->gameArray[coin->posX+1][coin->poxY]==1?0:1);
                    }

                    //检查左侧
                    if(coin->posX-1>=0)
                    {
                        coinBtn[coin->posX-1][coin->poxY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->poxY]=(this->gameArray[coin->posX-1][coin->poxY]==1?0:1);
                    }
                    //检测下侧金币是否可以反转
                    if(coin->poxY+1<=3)
                    {
                        coinBtn[coin->posX][coin->poxY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->poxY+1]=(this->gameArray[coin->posX][coin->poxY+1]==1?0:1);
                    }
                    //检测上侧金币是否可以反转
                    if(coin->poxY-1>=0)
                    {
                        coinBtn[coin->posX][coin->poxY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->poxY-1]=(this->gameArray[coin->posX][coin->poxY-1]==1?0:1);
                    }



                    //检测是否胜利

                    //开启可以让金币点击的状态
                    for(int k=0;k<4;k++)
                    {
                        for(int m=0;m<4;m++)
                            coinBtn[k][m]->isWin=false;
                    }
                    isWin=true;
                    for(int k=0;k<4;k++)
                    {
                        for(int m=0;m<4;m++)
                        {
                            //如果有一个是银币，那么就是false
                            if(coinBtn[k][m]->flag==false)
                            {
                                isWin=false;
                                break;
                            }
                        }
                    }
                    if(isWin)
                    {
                        playWin->play();
                        for(int k=0;k<4;k++)
                            for(int m=0;m<4;m++)
                            {
                                coinBtn[k][m]->isWin=true;
                            }
                        PlayGame::down(winLabel);
                    }
                });
            });
        }
    }
}


void PlayGame::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}

void PlayGame::down(QLabel *winLabel)
{
    //将胜利的图片做动画
    QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
    animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
void PlayGame::Win(QLabel *winLabel)
{
    //初始化胜利图片
    QPixmap temppix;
    temppix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,temppix.width(),temppix.height());
    winLabel->setPixmap(temppix);
    winLabel->setParent(this);
    winLabel->move((this->width()-temppix.width())*0.5,-temppix.height());
}
void PlayGame::textLabel()
{
    //创建具体用户选择标签
    QLabel *label=new QLabel();
    label->setParent(this);
    QString str=QString("leavel:%1").arg(this->leaveIndex);
    label->setText(str);
    //设置字体和字号
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    //设置位置和大小
    label->setGeometry(QRect(30,this->height()-50,120,50));
}
