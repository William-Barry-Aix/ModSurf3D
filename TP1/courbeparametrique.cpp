#include "courbeparametrique.h"
#include <math.h>       /* pow */
#include <QDebug>



void CourbeParametrique::addPassage(Point point){
    qDebug() << "oui";
    pointList->append(point);
    for (int i = 0; i < pointList->length(); i++){
    }
}

Point CourbeParametrique::getPoint(float p){
    int n = pointList->length();
    Point point = getN(0)*bernstein(0, n-1, p);

    for (int i = 1; i < n; i++){
        Point px = getN(i)*bernstein(i, n-1, p);
        point = point+px;

    }
    return point;
}

float CourbeParametrique::bernstein(int i, int n, float t){
    float res = factoriel(n)/(factoriel(i)*factoriel(n-i));
    res = res * pow(t, i);
    res = res * pow(1-t, (n-i));
    return res;
}

long CourbeParametrique::factoriel(int n) {
   return n > 1?(n * factoriel(n-1)):1;
}
