#include "careauparametrique.h"
#include <math.h>       /* pow */
#include <QDebug>

Point CarreauParametrique::getPoint(float u, float v){
    int n = pointList->length();
    int m = pointList->at(0)->length();
    Point point;
    Point px;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (i == 0 && j == 0){
                point = getN(0, 0)*bernstein(0, m-1, v)*bernstein(0, n-1, u);
            }else{
                px = getN(i, j)*bernstein(j, m-1, v)*bernstein(i, n-1, u);
                point = point+px;
            }
        }
    }
    return point;
}


void CarreauParametrique::addPassage(int u, Point point){
    if (u > pointList->length()-1)
        pointList->append(new QList<Point>());
    pointList->at(u)->append(point);

}

float CarreauParametrique::bernstein(int i, int n, float t){
    float res = factoriel(n)/(factoriel(i)*factoriel(n-i));
    res = res * pow(t, i);
    res = res * pow(1-t, (n-i));
    return res;
}

long CarreauParametrique::factoriel(int n) {
   return n > 1?(n * factoriel(n-1)):1;
}
