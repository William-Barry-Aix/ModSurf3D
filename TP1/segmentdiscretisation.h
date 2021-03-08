#ifndef SEGMENTDISCRETISATION_H
#define SEGMENTDISCRETISATION_H
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QVector>
#include "segment.h"

class SegmentDiscretisation
{
public:
    Segment *segment;
    SegmentDiscretisation(Segment *segment);
    ~SegmentDiscretisation();
    Segment* getSegment();
    void initPts();
    void genVBO();
    void draw(QOpenGLShaderProgram* m_program, QOpenGLFunctions *glFuncs);
    QVector<Point> getPoints();


    QOpenGLBuffer m_vbo;
    QVector<GLfloat> vertData;

};

#endif // SEGMENTDISCRETISATION_H
