#include "discretisation.h"
#include <tgmath.h>
Discretisation::Discretisation(Objet2D *objet)
{    
    this->objet = objet;
}

Discretisation::~Discretisation(){
    delete objet;
}

Objet2D* Discretisation::getObjet(){
    return this->objet;
}
QVector<Point> Discretisation::getPoints(){
    QVector<Point> points = QVector<Point>();
    float deltaT = 0.05;
    float seuilHaut = 3;
    float seuilBas = 0.1;
    float i = 0;
    QVector3D t0, t01;
    while(i <= 1){
        t0 = tengente(i, 0.0001);
        t01 = tengente(i+deltaT, 0.0001);
        float angle = acos(QVector3D::dotProduct(t0, t01));
        if (angle > seuilHaut){
            deltaT = deltaT/2;
        }else {
            if (angle < seuilBas){
                deltaT = deltaT + deltaT/2;
            }else {
                Point point = objet->getPoint(i+deltaT);
                points.append(point);
                i = i+deltaT;
            }
        }
    }
    return points;
}

QVector3D Discretisation::tengente(float t, float e){
    Point t0 = objet->getPoint(t+e);
    Point t1 = objet->getPoint(t-e);
    t0 = (t0-t1)*0.5;

    QVector3D vec;
    vec.setX(t0.getX());
    vec.setY(t0.getY());
    vec.setZ(t0.getX());

    return vec;
}
