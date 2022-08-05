#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chooselevelscene.h"
#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //利用绘图事件
    void paintEvent(QPaintEvent *);
    //选择关卡场景
    ChooseLevelScene *chooseScene;

    QPushButton *tipsText;


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
