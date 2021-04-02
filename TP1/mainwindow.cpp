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
    polyset->setWindowTitle("Coordonné du Polyedre");
    opt->setWindowTitle("Réglages");

    polysize->hide();
    polyset->hide();
    opt->hide();

    connect(polysize, SIGNAL(polySizeConfirmed(int,int)),this, SLOT(setPoly(int, int)));
    //connect(polyset, SIGNAL(polySetConfirmed(ptsValue,int,int)),this, SLOT(process(ptsValue,int,int)));

    connect(opt, SIGNAL(on_comboBox_currentIndexChanged(const QString)),this, SLOT());
    connect(opt, SIGNAL(on_angleXslider_sliderMoved(int)),this, SLOT(setAngleXVal(int)));
    connect(opt, SIGNAL(on_angleYslider_sliderMoved(int)),this, SLOT(setAngleYVal(int)));
    connect(opt, SIGNAL(on_pasSlider_sliderMoved(int)),this, SLOT(setSlider(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_pressed()
{
    polysize->show();
}

void MainWindow::setPoly(int n, int m)
{
    qDebug() << __FUNCTION__;
    polyset->generateGrid(n, m);
    polyset->show();
}

void MainWindow::setAngleXVal(int value){
    ui->openGLWidget->setAngleYVal(value);
}

void MainWindow::setAngleYVal(int value){
    ui->openGLWidget->setAngleYVal(value);
}

void MainWindow::setSlider(int value){
    ui->openGLWidget->setSlider(value);
}



void MainWindow::on_pushButton_2_pressed()
{
    opt->show();
}
