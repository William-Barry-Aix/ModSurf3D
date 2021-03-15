#ifndef OBJET2D_H
#define OBJET2D_H
#include "QList"
#include "point.h"

class Objet2D
{
public:
    Objet2D();
    ~Objet2D();
    Point getN(unsigned) const;
    void setN(unsigned, const Point&);
    virtual Point getPoint(float p) = 0;
    Objet2D& operator= (const Objet2D &o);
protected:
    QList<Point> * pointList;
};

#endif // OBJET2D_H
