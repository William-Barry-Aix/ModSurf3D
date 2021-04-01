#ifndef CAREAUPARAMETRIQUE_H
#define CAREAUPARAMETRIQUE_H

#include "QList"
#include "point.h"
#include "objet3d.h"

class CareauParametrique : public Objet3D
{
public:
    CareauParametrique(): Objet3D(){}

    virtual Point getPoint(float u, float v);
    void addPassage(int y, Point point);
private:
    float bernstein(int i, int n, float t);
    long factoriel(int n);

};

#endif // CAREAUPARAMETRIQUE_H
