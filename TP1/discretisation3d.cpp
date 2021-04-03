#include "discretisation3d.h"

Discretisation3D::Discretisation3D(Objet3D *objet, float m_step):
    step(m_step)
{
    this->objet = objet;
}

Discretisation3D::~Discretisation3D(){
    delete objet;
}

Objet3D* Discretisation3D::getObjet(){
    return this->objet;
}

QVector<Point> Discretisation3D::getPoints(){
    QVector<Point> points = QVector<Point>();
    int ptsCount = 0;

    for (float i = 0; i <= 1; i+=step){
        for (float j = 0; j <= 1; j+=step){
            Point point = objet->getPoint(i, j);
            point.setId(ptsCount);
            points.append(point);
            ptsCount++;
        }
    }
    return points;
}

QVector<Point> Discretisation3D::getPointsPleine(){
    QVector<Point> points = QVector<Point>();
    QVector<QVector<Point>> ptsMat = getMatPoints();

    int n , m;
    n = ptsMat.length();
    m = ptsMat.at(0).length();
    for (int i = 0; i < n-1; i++){
        for (int j = 0; j < m-1; j++){
            // Triangle Bas-Gauche
            points.append(ptsMat.at(i).at(j));
            points.append(ptsMat.at(i).at(j+1));
            points.append(ptsMat.at(i+1).at(j));
            // Triangle Bas-Gauche
            points.append(ptsMat.at(i+1).at(j+1));
            points.append(ptsMat.at(i+1).at(j));
            points.append(ptsMat.at(i).at(j+1));
        }
    }
    return points;
}

QVector<Point> Discretisation3D::getPointsFilaire(){
    QVector<Point> points = QVector<Point>();
    QVector<QVector<Point>> ptsMat = getMatPoints();

    int n , m;
    n = ptsMat.length();
    m = ptsMat.at(0).length();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m-1; j++){
            points.append(ptsMat.at(i).at(j));
            points.append(ptsMat.at(i).at(j+1));
        }
    }

    for (int i = 0; i < n-1; i++){
        for (int j = 0; j < m; j++){
            points.append(ptsMat.at(i).at(j));
            points.append(ptsMat.at(i+1).at(j));
        }
    }

    return points;
}

QVector<Point> Discretisation3D::getPointsTriangles(){
    QVector<Point> points = getPointsFilaire();
    QVector<QVector<Point>> ptsMat = getMatPoints();

    int n , m;
    n = ptsMat.length();
    m = ptsMat.at(0).length();
    for (int i = 0; i < n-1; i++){
        for (int j = 0; j < m-1; j++){
            points.append(ptsMat.at(i).at(j+1));
            points.append(ptsMat.at(i+1).at(j));
        }
    }
    return points;
}

QVector<Point> Discretisation3D::getPoints(QString str){
    QVector<Point> points;

    if (str.compare("triangles") == 0)
        points = getPointsTriangles();
    else if (str.compare("filaire") == 0)
        points = getPointsFilaire();
    else if (str.compare("pleine") == 0)
        points = getPointsPleine();
    else
        points = getPoints();

    return points;
}

QVector<QVector<Point>> Discretisation3D::getMatPoints(){
    qDebug() << __FUNCTION__ ;
    QVector<QVector<Point>> ptsMat = QVector<QVector<Point>>();
    QVector<Point> ptsTmp;

    for (float i = 0; i <= 1; i+=step){
        ptsTmp = QVector<Point>();
        for (float j = 0; j <= 1; j+=step){
            Point point = objet->getPoint(i, j);
            //point.setId(ptsCount);
            qDebug() <<" id :" << point.id;
            ptsTmp.append(point);
        }
        ptsMat.append(ptsTmp);
    }

    double ptsCount = 0;
    for (int i = 0; i < ptsMat.length(); i++){
        for(int j = 0; j < ptsMat.at(i).length(); j++){

            QVector<Point> vpx = ptsMat.at(i);
            Point px = vpx.at(j);
            px.setId(ptsCount);
            ptsCount++;
            vpx.replace(j,px);
            ptsMat.replace(i,vpx);
            qDebug() << ptsCount << " ptsmatID ="<<ptsMat.at(i).at(j).id;
        }
    }
    return ptsMat;
}
