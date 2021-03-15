#include <cmath>

#include "segment.h"
#include <QDebug>


Segment::Segment(const Segment & s): Objet2D()
{
	for (unsigned i=0; i<2; ++i)
        pointList->replace(i, s.pointList->at(i));

}

Point Segment::getPoint(float p){
    Point res;
    //p *= p;
    res = getStart()*(1-p)+getEnd()*p;
    return res;
}
void Segment::setStart(const Point & p)
{
    if (pointList->length()!=0){
       setN(0, p);
    }else
        pointList->append(p);
}

void Segment::setEnd(const Point & p)
{
    if (pointList->length()!=1){
        setN(1, p);
    }else
        pointList->append(p);
}


Point Segment::getStart() const
{
	return getN(0);
}


Point Segment::getEnd() const
{
	return getN(1);
}

float Segment::length() const
{
    Point start = getStart(), end = getEnd();
    float res = (start.getX()*end.getX()) + (start.getY()*end.getY());
	return sqrt(res);
}

std::ostream& operator<<(std::ostream& out, const Segment& s)
{
    return out << s.getStart() << " -- " << s.getEnd();
}
