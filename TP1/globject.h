#ifndef GLOBJECT_H
#define GLOBJECT_H
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector>
#include "point.h"
#include <iostream>
#include <fstream>
using namespace std;

class GLObject
{
public:
    GLObject(QVector<Point> points, QList<Point> controlPts);
    GLObject(QVector<Point> points, QList<Point> controlPts, QString mode);
    void initPts();
    void genVBO();
    void draw(QOpenGLShaderProgram* m_program, QOpenGLFunctions *glFuncs);
    void exportOBJ();

    QVector<Point> points = QVector<Point>();
    QList<Point> controlPts;
    QOpenGLBuffer m_vbo;
    QVector<GLfloat> vertData;
    QString mode;
};

#endif // GLOBJECT_H
