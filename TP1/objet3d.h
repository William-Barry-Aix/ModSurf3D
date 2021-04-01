#ifndef OBJET3D_H
#define OBJET3D_H
#include "QList"
#include "point.h"

class Objet3D
{
public:
    Objet3D();
    ~Objet3D();
    Point getN(unsigned, unsigned) const;
    void setN(unsigned, unsigned, const Point&);
    QList<Point> getPointList();
    virtual Point getPoint(float u, float v) = 0;
    Objet3D& operator= (const Objet3D &o);
    QList<QList<Point>*> * pointList;
};

#endif // OBJET3D_H
