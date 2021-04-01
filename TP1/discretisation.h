#ifndef DISCRETISATION_H
#define DISCRETISATION_H
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector>
#include "segment.h"

class Discretisation
{
public:
    Objet2D *objet;
    Discretisation(Objet2D *segment);
    ~Discretisation();
    Objet2D* getObjet();
    //void initPts();
    //void genVBO();
    //void draw(QOpenGLShaderProgram* m_program, QOpenGLFunctions *glFuncs);
    QVector<Point> getPoints();


    //QOpenGLBuffer m_vbo;
    //QVector<GLfloat> vertData;

    QVector3D tengente(float t, float e);

};

#endif // DISCRETISATION_H
