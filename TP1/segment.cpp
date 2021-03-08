#include <cmath>

#include "segment.h"
#include <QDebug>

Segment::Segment()
{
    pointList = new Point[2];
}

Segment::~Segment()
{
	delete [] pointList;
    pointList = nullptr;
}


Segment::Segment(const Segment & s)
{
	pointList = new Point[2];

	for (unsigned i=0; i<2; ++i)
		pointList[i] = s.pointList[i];

}

Point Segment::getPoint(float p){
    // A B ratio = 1
    // p = pourcentage
    Point P = Point();
    p = p;
    float x = getStart().getX();
    float y = getStart().getY();
    x += p*(getStart().getX()+getEnd().getX());
    y += p*(getStart().getY()+getEnd().getY());
    P.setX(length()* x);
    P.setY(length()* y*y);
    P.setZ(0);
    return P;
}
void Segment::setStart(const Point & p)
{
	pointList[0] = p;
}

void Segment::setEnd(const Point & p)
{
	pointList[1] = p;
}

void Segment::setN(unsigned r, const Point & p)
{
	if (r>1)
		r=1;
	pointList[r] = p;
}

Point Segment::getN(unsigned r) const
{
	if (r>1)
		r=1;

	return pointList[r];
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
	float res=0.0f;

	for (unsigned i=0; i<3; ++i)
		res += pow((pointList[1]).getN(i) - (pointList[0]).getN(i), 2.0f);

	return sqrt(res);
}

Segment& Segment::operator= (const Segment &s)
{
	for (unsigned i=0; i<2; ++i)
		pointList[i] = s.pointList[i];

return *this;
}

std::ostream& operator<<(std::ostream& out, const Segment& s)
{
	return out << s.pointList[0] << " -- " << s.pointList[1];
}
