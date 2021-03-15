/* R. Raffin
 * M1 Informatique, Aix-Marseille Université
 * définition d'une classe Segment
 * Comme pour Point, il faudrait mieux utiliser un std::Vector pour stocker les 2 Poins du segment, cela évite de manipuler des pointeurs (et d'en faire allocation et libération.
 * Un Segment n'a par contre que 2 élements Point, le tbaleau est donc de taille fixe
 * Pour aller plus loin, il faut pouvoir évaluer un point sur le segment en fonction d'un paramètre.
 * Ce paramètre doit appartenir à l'intervalle [0,1] et il faudrait donc stocker/vérifier cet intervalle.
 */

#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"
#include "objet2d.h"
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

class Segment : public Objet2D
{
private:
public:
    Segment(): Objet2D(){}
	Segment(const Segment&);
    virtual Point getPoint(float p);

	void setStart(const Point&);
    void setEnd(const Point&);

    Point getStart() const;
    Point getEnd()const ;

	float length() const;
	friend std::ostream& operator<<(std::ostream&, const Segment&);
};

#endif // SEGMENT_H
