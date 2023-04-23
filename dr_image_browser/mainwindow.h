#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <cmath>
#include <QFileDialog>
#include <QFileInfo>
#include <QStack>
#include "state.h"

#define PI 3.14

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    void openRaw();
    uchar window(ushort p);
    uchar windowg(int p);
    ~MainWindow();
    uchar binterp(double src_x, double src_y, QImage ima, int ori_w, int ori_h);
    QImage rgb2gray(QImage rgbim);
    QImage rotation(QImage im, double angle);
    QImage scale(QImage im, double wrate, double hrate);
    QImage mirror(QImage im, int mirror);
    bool inImage(int w, int h, double x, double y);
    QImage laplacian(QImage im, double rate);
    uchar* laplacian(ushort* src, double rate, int w, int h);
    void setState(State &st);
    void getState(State &st);
    void set();
    void get();
    void init();
    QImage equalize(QImage im);
    QImage invert(QImage);
signals:
    void drawSignal();

private slots:
    void on_select_clicked();
    void draw();
    void on_select_2_clicked();

    void on_pushButton_clicked();

    void on_return_2_clicked();

private:
    Ui::MainWindow *ui;
    ushort lowerbound=0;//窗宽
    ushort upperbound=4096;//窗位
    QImage im;//图像
    QString fname;//文件路径
    double angle=0;//选择角度
    double hrate=1.0;//竖直缩放倍数
    double wrate=1.0;//水平缩放倍数
    double srate=1.0;//锐化系数
    int mirrortype=0;//翻转类型
    bool iss=0;//标识是否锐化
    bool isr=0;//标识是否选择
    bool ish=0;//标识是否竖直缩放
    bool isw=0;//标识是否水平缩放
    bool isi=0;//标识是否灰度反转
    bool ise=0;//标识是否直方图均衡化
    QStack<State> sta;//用于存储历史图像及其参数的栈
};
#endif // MAINWINDOW_H
