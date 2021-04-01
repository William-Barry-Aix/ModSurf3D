#ifndef GLOBJECT_H
#define GLOBJECT_H
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector>
#include "point.h"


class GLObject
{
public:
    GLObject(QVector<Point> points, QList<Point> controlPts);
    void initPts();
    void genVBO();
    void draw(QOpenGLShaderProgram* m_program, QOpenGLFunctions *glFuncs);

    QVector<Point> points = QVector<Point>();
    QList<Point> controlPts;
    QOpenGLBuffer m_vbo;
    QVector<GLfloat> vertData;
};

#endif // GLOBJECT_H
