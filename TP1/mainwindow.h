#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myopenglwidget.h"
#include "polysize.h"
#include "polyset.h"
#include "ptsvalue.h"
#include "option.h"
#include <unistd.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_3_pressed();
    void newOpenGLWidget();
    Point pointSample(float x, float y, float z);
    void setPoly(int n, int m);
    //void process(ptsValue pts, int n, int m);
    void setMode(QString arg);
    void setAngleXVal(int value);
    void setAngleYVal(int value);
    void setSlider(int value);
    void process(Point points[],int N,int M);


    void on_pushButton_2_pressed();

    void on_pushButton_pressed();

private:
    Ui::MainWindow *ui;
    myOpenGLWidget *myopenglwidget;
    polySet *polyset;
    polySize *polysize = new polySize(this);
    option *opt = new option(this);

    Point points[60];
    int n = 2;
    int m = 3;
    int step;
    QString mode = "triangles";
};

#endif // MAINWINDOW_H
