#include "globject.h"

GLObject::GLObject(QVector<Point> points, QList<Point> controlPts){
    this->points = points;
    this->controlPts = controlPts;
}

void GLObject::genVBO(){
    initPts();

    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
    m_vbo.release();
}

void GLObject::initPts(){
    //1 Traduction en tableaux de floats
    int nbControlPts = controlPts.length();
    GLfloat * vertices = new GLfloat[points.length()*3 + nbControlPts*3]; //2 sommets
    GLfloat * colorRed = new GLfloat[3]; //1 couleur (RBG) par sommet
    GLfloat * colorBlue = new GLfloat[3]; //1 couleur (RBG) par sommet

    //couleur0 = rouge
    colorRed[0] = 1.0;
    colorRed[1] = 0.0;
    colorRed[2] = 0.0;


    colorBlue[0] = 0.0;
    colorBlue[1] = 0.0;
    colorBlue[2] = 1.0;

    Point p;
    for(int i = 0; i < nbControlPts; i++) {
        p = controlPts.at(i);
        points.append(p);
    }

    for (int i= 0; i < points.length(); i++){
        vertices[i*3] = points.at(i).getX();
        vertices[i*3+1] = points.at(i).getY();
        vertices[i*3+2] = points.at(i).getZ();
    }



    //2 spécialisation OpenGL
    qDebug() << "nbPts" <<points.length();
    for (int i = 0; i < points.length(); ++i) { //2 sommets
        qDebug() << i;
        // coordonnées sommets
        for (int j = 0; j < 3; j++) //3 coords par sommet
            vertData.append(vertices[i*3+j]);
        // couleurs sommets
        for (int j = 0; j < 3; j++){ //1 RGB par sommet
            if (i < points.length()-nbControlPts)
                vertData.append(colorRed[j]);
            else{
                p = points.at(i);
                qDebug() << p.getX() << p.getY() << p.getZ();
                vertData.append(colorBlue[j]);
            }
        }
    }



    //destruction des éléments de la phase 2
    delete [] vertices;
    delete [] colorRed;
    delete [] colorBlue;
}


void GLObject::draw(QOpenGLShaderProgram* m_program, QOpenGLFunctions *glFuncs){
    m_vbo.bind();

    m_program->setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
    m_program->setAttributeBuffer("colAttr", GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));
    m_program->enableAttributeArray("posAttr");
    m_program->enableAttributeArray("colAttr");

    glPointSize (3.0f);
    glFuncs->glDrawArrays(GL_POINTS, 0, vertData.length());

    m_program->disableAttributeArray("posAttr");
    m_program->disableAttributeArray("colAttr");

    m_vbo.release();
    qDebug() << "displayed";
}
