#ifndef DISCRETISATION3D_H
#define DISCRETISATION3D_H
#include "discretisation.h"
#include "objet3d.h"

class Discretisation3D
{
public:    
    Objet3D *objet;
    Discretisation3D(Objet3D *objet);

    ~Discretisation3D();
    Objet3D* getObjet();
    QVector<Point> getPoints(QString str);

private:
    QVector<Point> getPointsTriangles();
    QVector<Point> getPointsFilaire();
    QVector<Point> getPointsPleine();
    QVector<Point> getPoints();
    QVector<QVector<Point>> getMatPoints();

};

#endif // DISCRETISATION3D_H
