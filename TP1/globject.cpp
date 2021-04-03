#include "globject.h"

GLObject::GLObject(QVector<Point> points, QList<Point> controlPts){
    this->points = points;
    this->controlPts = controlPts;
    this->mode = "";
}

GLObject::GLObject(QVector<Point> points, QList<Point> controlPts, QString mode){
    this->points = points;
    this->controlPts = controlPts;
    this->mode = mode;
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
        qDebug() << "idVBO = "<< points.at(i).id;
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
    //glFuncs->glDrawArrays(GL_POINTS, 0, points.length()-controlPts.length());
    if (mode.compare("triangles") == 0)
        glFuncs->glDrawArrays(GL_LINES, 0, points.length()-controlPts.length());
    else if (mode.compare("filaire") == 0)
        glFuncs->glDrawArrays(GL_LINES, 0, points.length()-controlPts.length());
    else if (mode.compare("pleine") == 0)
        glFuncs->glDrawArrays(GL_TRIANGLES, 0, points.length()-controlPts.length());

    glFuncs->glDrawArrays(GL_POINTS, points.length()-controlPts.length(), controlPts.length());


    m_program->disableAttributeArray("posAttr");
    m_program->disableAttributeArray("colAttr");

    m_vbo.release();
    qDebug() << "displayed";
}

void GLObject::exportOBJ(){
    qDebug() << __FUNCTION__ ;
   ofstream myfile;
     myfile.open ("exported_mesh.obj");
   for(int i = 0; i < points.length()-controlPts.length(); i++){
       myfile << "v " << points.at(i).getX() << ' ' << points.at(i).getY() << ' ' << points.at(i).getZ()<< endl;
   }
   for(int i = 0; i < (points.length()-controlPts.length())/3; i++){
       myfile << "f " << i+1 << ' ' << i+2 << ' ' << i+3 << endl;
   }
   myfile.close();
   qDebug()<< "fin de l'exportation";
}
