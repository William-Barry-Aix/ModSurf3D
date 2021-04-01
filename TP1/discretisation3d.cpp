#include "discretisation3d.h"

Discretisation3D::Discretisation3D(Objet3D *objet)
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

    for (float i = 0; i <= 1; i+=0.25){
        for (float j = 0; j <= 1; j+=0.25){
            Point point = objet->getPoint(i, j);
            points.append(point);
        }
    }
    return points;
}
