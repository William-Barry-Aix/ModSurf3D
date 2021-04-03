#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myopenglwidget.h"
#include "polysize.h"
#include "polyset.h"
#include "ptsvalue.h"
#include "option.h"

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
    void setPoly(int n, int m);
    //void process(ptsValue pts, int n, int m);
    void setMode(QString arg);
    void setAngleXVal(int value);
    void setAngleYVal(int value);
    void setSlider(int value);
    void process(Point points[],int N,int M);


    void on_pushButton_2_pressed();

private:
    Ui::MainWindow *ui;
    myOpenGLWidget *myopenglwidget;
    polySet *polyset;
    polySize *polysize = new polySize(this);
    option *opt = new option(this);

    int step;
    QString mode = "triangles";
};

#endif // MAINWINDOW_H
