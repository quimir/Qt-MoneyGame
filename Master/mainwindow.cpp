#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include "mypushbutton.h"
#include <QApplication>
#include <QDebug>
#include <QTimer>
#include <QCloseEvent>
#include <QMessageBox>
#include "playgame.h"
#include <QMessageBox>
#include <QSoundEffect>
#include <QPushButton>
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //主场景的基本配置
    //设置标题
    this->setWindowTitle("翻金币主场景");
    //设置窗口
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //点击退出
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //开始音效的准备
    QSoundEffect *startSound=new QSoundEffect(this);
    startSound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));


    //文本提示框
    tipsText=new QPushButton(this);
    tipsText->setText("查看游戏帮助");
    tipsText->move(QPoint((this->width()-tipsText->width())/2,(this->height()-tipsText->height())/2));
    // 设置按钮样式及悬浮、按下时的状态
    tipsText->setStyleSheet("QPushButton{background-color: rgb(225, 225, 225);border:2px groove gray;border-radius:50px;padding:2px 4px;border-style: outset;}"
                            "QPushButton:hover{background-color:rgb(229, 241, 251); color: black;}"
                            "QPushButton:pressed{background-color:rgb(204, 228, 247);border-style: inset;}");

    connect(tipsText,&QPushButton::clicked,[=](){
        QMessageBox messageBox;
        QString s("本游戏的规则是翻动一个金币或者银币就会将四周翻开，当翻开的全部都是金币的时候游戏就通过本关卡否则游戏不通过"
                  "\nby--QuiMir");
        messageBox.information(this,"游戏帮助",s,QMessageBox::StandardButton::Ok|QMessageBox::StandardButton::Close);
    });




    //选择关卡场景
    chooseScene=new ChooseLevelScene;
    //开始按钮
    MyPushButton *startBtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
    startBtn->setParent(this);
    //监听选择管卡场景中的返回按钮自定义信号和场景互换
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
        chooseScene->hide();//自身隐藏
        //设置位置
        this->setGeometry(chooseScene->geometry());

        this->show();//主页面显示
    });
    connect(startBtn,&QPushButton::clicked,[=]()
    {

        //播放音效
        startSound->play();

        //循环播放操作，如果是-1则无限循环
        //        startSound->setLoopCount(5);

        //        qDebug()<<"点击信号";
        startBtn->zoom1();
        startBtn->zoom2();
        //延时进入到选择关卡场景
        QTimer::singleShot(350,this,[=]()
        {
            //自身隐藏
            chooseScene->setGeometry(this->geometry());
            this->hide();
            chooseScene->show();
        });
    });
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix(":/res/PlayLevelSceneBg.png");
    //加载主图片
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //加载标题
    pix.load(":/res/Title.png");
    //加载图片
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}
MainWindow::~MainWindow()
{
    delete ui;
}

