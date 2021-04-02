#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void setPoly(int n, int m);
    //void process(ptsValue pts, int n, int m);
    void setAngleXVal(int value);
    void setAngleYVal(int value);
    void setSlider(int value);

    void on_pushButton_2_pressed();

private:
    Ui::MainWindow *ui;
    polySize *polysize = new polySize(this);
    polySet *polyset = new polySet(this);
    option *opt = new option(this);
};

#endif // MAINWINDOW_H
