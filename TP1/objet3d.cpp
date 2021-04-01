#include "objet3d.h"

Objet3D::Objet3D()
{
    pointList = new QList<QList<Point>*>();
}

Objet3D::~Objet3D()
{
    delete pointList;
}

Point Objet3D::getN(unsigned u, unsigned v) const
{
    return pointList->at(u)->at(v);
}

Objet3D& Objet3D::operator= (const Objet3D &o)
{
    for (unsigned i=0; i<3; ++i)
        for (unsigned j=0; j<3; ++i)
            setN(i, j, o.getN(i, j));

    return *this;
}

void Objet3D::setN(unsigned u, unsigned v, const Point & p)
{
    if (u>1)
        u=1;
    if (v>1)
        v=1;
    pointList->at(v)->replace(u, p);
}

QList<Point> Objet3D::getPointList(){
    QList<Point> list = QList<Point>();
    for (int i = 0; i < pointList->length(); i++){
        for (int j = 0; j < pointList->at(i)->length(); j++){
            list.append(pointList->at(i)->at(j));
        }
    }
    return list;
}
