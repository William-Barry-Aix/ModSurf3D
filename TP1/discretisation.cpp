#include "discretisation.h"

Discretisation::Discretisation(Objet2D *objet)
{    
    this->objet = objet;
}

void Discretisation::genVBO(){
    initPts();

    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));
    m_vbo.release();
}

Discretisation::~Discretisation(){
    m_vbo.destroy();
}

Objet2D* Discretisation::getObjet(){
    return this->objet;
}

void Discretisation::initPts(){
    //1 Traduction en tableaux de floats

    QVector<Point> points = getPoints();
    GLfloat * vertices = new GLfloat[points.length()*3]; //2 sommets
    GLfloat * colors = new GLfloat[points.length()*3]; //1 couleur (RBG) par sommet

    for (int i= 0; i < points.length(); i++){
        vertices[i*3] = points.at(i).getX();
        vertices[i*3+1] = points.at(i).getY();
        vertices[i*3+2] = points.at(i).getZ();
    }

    //couleur0 = rouge
    colors[0] = 1.0;
    colors[1] = 0.0;
    colors[2] = 0.0;

    //2 spécialisation OpenGL
    for (int i = 0; i < points.length(); ++i) { //2 sommets
        // coordonnées sommets
        for (int j = 0; j < 3; j++) //3 coords par sommet
            vertData.append(vertices[i*3+j]);
        // couleurs sommets
        for (int j = 0; j < 3; j++) //1 RGB par sommet
            vertData.append(colors[j]);
    }

    //destruction des éléments de la phase 2
    delete [] vertices;
    delete [] colors;
}
QVector<Point> Discretisation::getPoints(){
    QVector<Point> points = QVector<Point>();
    for (float i = 0; i <= 1; i+=0.1){
        Point point = objet->getPoint(i);
        //point.setX(point.getX()*point.getX());
        points.append(point);
    }
    return points;
}


void Discretisation::draw(QOpenGLShaderProgram* m_program, QOpenGLFunctions *glFuncs){
    m_vbo.bind();

    m_program->setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
    m_program->setAttributeBuffer("colAttr", GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));
    m_program->enableAttributeArray("posAttr");
    m_program->enableAttributeArray("colAttr");

    glPointSize (3.0f);
    glFuncs->glDrawArrays(GL_POINTS, 0, getPoints().length());

    m_program->disableAttributeArray("posAttr");
    m_program->disableAttributeArray("colAttr");

    m_vbo.release();
    qDebug() << "displayed";
}
