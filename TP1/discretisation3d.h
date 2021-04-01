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
    QVector<Point> getPoints();

};

#endif // DISCRETISATION3D_H
