/* R. Raffin
 * M1 Informatique, Aix-Marseille Université
 * Fenêtre principale
 * Au cas où, l'UI contient une barre de menu, une barre de status, une barre d'outils (cf QMainWindow).
 * Une zone est laissée libre à droite du Widget OpenGL pour mettre de futurs contrôles ou informations.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    polysize->setWindowTitle("Taille du Polyedre");
    opt->setWindowTitle("Réglages");

    polysize->hide();
    opt->hide();

    connect(polysize, SIGNAL(polySizeConfirmed(int,int)),this, SLOT(setPoly(int, int)));

    connect(opt, SIGNAL(comboBoxChanged(QString)),this, SLOT(setMode(QString)));
    connect(opt, SIGNAL(angleXsliderChanged(int)),this, SLOT(setAngleXVal(int)));
    connect(opt, SIGNAL(angleYsliderChanged(int)),this, SLOT(setAngleYVal(int)));
    connect(opt, SIGNAL(pasSliderChanged(int)),this, SLOT(setSlider(int)));

    step = 10;

    myopenglwidget = new myOpenGLWidget(this, step, mode);
    ui->verticalLayout->addWidget(myopenglwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_pressed()
{
    polysize->show();
}

void MainWindow::newOpenGLWidget(){
    myopenglwidget = new myOpenGLWidget(this, step, mode);
    ui->verticalLayout->addWidget(myopenglwidget);
    delete ui->verticalLayout->takeAt(1);
}

void MainWindow::setPoly(int n, int m)
{
    qDebug() << __FUNCTION__;
    polyset = new polySet(this);
    polyset->generateGrid(n, m);
    polyset->setWindowTitle("Coordonné du Polyedre");
    connect(polyset, SIGNAL(polySetConfirmed(Point,int,int)),this, SLOT(process(Point,int,int)));

    polyset->show();
}

void MainWindow::setMode(QString arg){
    qDebug() << __FUNCTION__ ;
    mode = arg;
    newOpenGLWidget();
}

void MainWindow::setAngleXVal(int value){
    qDebug() << __FUNCTION__ ;
    myopenglwidget->setAngleYVal(value);
    myopenglwidget->update();
}

void MainWindow::setAngleYVal(int value){
    qDebug() << __FUNCTION__ ;
    myopenglwidget->setAngleYVal(value);
    myopenglwidget->update();
}

void MainWindow::setSlider(int value){
    qDebug() << __FUNCTION__ ;
    step = value;
    newOpenGLWidget();
}

void MainWindow::process(Point points[],int N,int M){
    qDebug() << __FUNCTION__ ;
    //ui->openGLWidget->newGlObject(points,N,M);
}

void MainWindow::on_pushButton_2_pressed()
{
    opt->show();
}
