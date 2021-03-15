#ifndef COURBEPARAMETRIQUE_H
#define COURBEPARAMETRIQUE_H
#include "QList"
#include "point.h"
#include "objet2d.h"

class CourbeParametrique : public Objet2D
{
public:
    CourbeParametrique(): Objet2D(){}
    virtual Point getPoint(float p);
    void addPassage(Point point);
private:
    float bernstein(int i, int n, float t);
    long factoriel(int n);
};

#endif // COURBEPARAMETRIQUE_H
