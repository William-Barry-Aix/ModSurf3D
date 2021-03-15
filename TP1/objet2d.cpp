#include "objet2d.h"

Objet2D::Objet2D()
{
    pointList = new QList<Point>();
}
Objet2D::~Objet2D()
{
    delete pointList;
}


Point Objet2D::getN(unsigned r) const
{
    return pointList->at(r);
}

Objet2D& Objet2D::operator= (const Objet2D &o)
{
    for (unsigned i=0; i<2; ++i)
        setN(i, o.getN(i));

    return *this;
}

void Objet2D::setN(unsigned r, const Point & p)
{
    if (r>1)
        r=1;
    pointList->replace(r,p);
}
