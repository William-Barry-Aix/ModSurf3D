//R. Raffin, M1 Informatique, "Surfaces 3D"
//tiré de CC-BY Edouard.Thiel@univ-amu.fr - 22/01/2019

#include "myopenglwidget.h"
#include <QDebug>
#include <QSurfaceFormat>
#include <QMatrix4x4>

#include <iostream>

#include "segment.h"

static const QString vertexShaderFile   = ":/basic.vsh";
static const QString fragmentShaderFile = ":/basic.fsh";


myOpenGLWidget::myOpenGLWidget(QWidget *parent) :
	QOpenGLWidget(parent)
{
    qDebug() << "init myOpenGLWidget" ;
	QSurfaceFormat sf;
	sf.setDepthBufferSize(24);
	sf.setSamples(16);  // nb de sample par pixels : suréchantillonnage por l'antialiasing, en décalant à chaque fois le sommet
						// cf https://www.khronos.org/opengl/wiki/Multisampling et https://stackoverflow.com/a/14474260
	setFormat(sf);

	setEnabled(true);  // événements clavier et souris
	setFocusPolicy(Qt::StrongFocus); // accepte focus
	setFocus();                      // donne le focus

	m_timer = new QTimer(this);
	m_timer->setInterval(50);  // msec
	connect (m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

myOpenGLWidget::~myOpenGLWidget()
{
	qDebug() << "destroy GLArea";

	delete m_timer;

	// Contrairement aux méthodes virtuelles initializeGL, resizeGL et repaintGL,
	// dans le destructeur le contexte GL n'est pas automatiquement rendu courant.
	makeCurrent();
	tearGLObjects();
	doneCurrent();
}


void myOpenGLWidget::initializeGL()
{
	qDebug() << __FUNCTION__ ;
	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST);

	makeGLObjects();

	//shaders
	m_program = new QOpenGLShaderProgram(this);
	m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderFile);  // compile
	m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderFile);

	if (! m_program->link()) {  // édition de lien des shaders dans le shader program
		qWarning("Failed to compile and link shader program:");
		qWarning() << m_program->log();
	}
}

void myOpenGLWidget::doProjection()
{
	//m_mod.setToIdentity();
	//modelMatrix.ortho( -aratio, aratio, -1.0f, 1.0f, -1.0f, 1.0f );
}


void myOpenGLWidget::makeGLObjects()
{

	//1 Nos objets géométriques
    Point A, B, C, D, E, F;
	float * coord = new float[3];

    coord[0] = -1.0f;
	coord[1] = 0.0f;
	coord[2] = 0.0f;

    A.set(coord);


    coord[0] = 1.0f;
    coord[1] = 0.0f;
    coord[2] = 0.0f;

    B.set(coord);

    coord[0] = 0.0f;
    coord[1] = 1.0f;
	coord[2] = 0.0f;

    C.set(coord);

    coord[0] = 1.0f;
    coord[1] = -1.0f;
    coord[2] = 0.0f;

    D.set(coord);
    //délégation dans le constructeur de l'objet

    Segment *seg = new Segment();
    seg->setStart(A);
    seg->setEnd(B);


    CourbeParametrique *cou = new CourbeParametrique();
    cou->addPassage(A);
    cou->addPassage(B);
    cou->addPassage(C);
    cou->addPassage(D);

    CareauParametrique *careau = new CareauParametrique();
    A.setX(-1);
    A.setY(0);
    A.setZ(0);

    B.setX(1);
    B.setY(0);
    B.setZ(0);

    C.setX(-1);
    C.setY(1);
    C.setZ(0.25);

    D.setX(1);
    D.setY(1);
    D.setZ(0.25);

    E.setX(-1.5);
    E.setY(0);
    E.setZ(0.25);

    F.setX(1.5);
    F.setY(0);
    F.setZ(0.25);

    careau->addPassage(0, A);
    careau->addPassage(0, B);
    careau->addPassage(1, E);
    careau->addPassage(1, F);
    careau->addPassage(2, C);
    careau->addPassage(2, D);


    QList<Point> list = careau->getPointList();
    for (int i = 0; i < list.length(); i++){
        Point p = list.at(i);
        qDebug() << p.getX() << p.getY() << p.getZ();
    }

    delete [] coord;
    //Discretisation disc = Discretisation(cou);
    Discretisation3D disc = Discretisation3D(careau);

    //QString mode = "triangles";
    //QString mode = "filaire";
    QString mode = "pleine";
    segDiscr = new GLObject(disc.getPoints(mode), disc.getObjet()->getPointList(), mode);

    segDiscr->genVBO();
    segDiscr->exportOBJ();
}


void myOpenGLWidget::tearGLObjects()
{
    delete segDiscr;
}


void myOpenGLWidget::resizeGL(int w, int h)
{
	qDebug() << __FUNCTION__ << w << h;

	//C'est fait par défaut
	glViewport(0, 0, w, h);

	m_ratio = (double) w / h;
	//doProjection();
}

void myOpenGLWidget::paintGL()
{
	qDebug() << __FUNCTION__ ;
    QOpenGLFunctions *glFuncs = context()->functions();  // cf initializeGL

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_program->bind(); // active le shader program


	/// Ajout RR pour gérer les 3 matrices utiles
	/// à mettre dans doProjection() pour clarifier
	/// -----------------------------------------
		m_modelView.setToIdentity();
		m_modelView.lookAt(QVector3D(0.0f, 0.0f, 3.0f),    // Camera Position
						 QVector3D(0.0f, 0.0f, 0.0f),    // Point camera looks towards
						 QVector3D(0.0f, 1.0f, 0.0f));   // Up vector

		m_projection.setToIdentity ();
		m_projection.perspective(70.0, width() / height(), 0.1, 100.0); //ou m_ratio

		//m_model.translate(0, 0, -3.0);

		// Rotation de la scène pour l'animation
        m_model.rotate(m_angleY, 0, 1, 0);  //rotation de la scène sur l'axe y
        m_model.rotate(m_angleX, 1, 0, 0);  //rotation de la scène sur l'axe x

		QMatrix4x4 m = m_projection * m_modelView * m_model;
	///----------------------------

	m_program->setUniformValue("matrix", m);
    segDiscr->draw(m_program, glFuncs);
    /*
	m_program->setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
	m_program->setAttributeBuffer("colAttr", GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));
	m_program->enableAttributeArray("posAttr");
	m_program->enableAttributeArray("colAttr");

    glPointSize (5.0f);
	glDrawArrays(GL_POINTS, 0, 2);

	m_program->disableAttributeArray("posAttr");
	m_program->disableAttributeArray("colAttr");
    */
	m_program->release();
}

void myOpenGLWidget::keyPressEvent(QKeyEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->text();

	switch(ev->key()) {
		case Qt::Key_Z :
            m_angleY += 1;
            if (m_angleY >= 360) m_angleY -= 360;
			update();
			break;
		case Qt::Key_A :
			if (m_timer->isActive())
				m_timer->stop();
			else m_timer->start();
			break;
		case Qt::Key_R :
			break;
	}
}

void myOpenGLWidget::keyReleaseEvent(QKeyEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->text();
}

void myOpenGLWidget::mousePressEvent(QMouseEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->x() << ev->y() << ev->button();
}

void myOpenGLWidget::mouseReleaseEvent(QMouseEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->x() << ev->y() << ev->button();
}

void myOpenGLWidget::mouseMoveEvent(QMouseEvent *ev)
{
	qDebug() << __FUNCTION__ << ev->x() << ev->y();
}

void myOpenGLWidget::onTimeout()
{
	qDebug() << __FUNCTION__ ;

	update();
}

void myOpenGLWidget::setAngleXVal(int value){
    m_angleX = value;
    qDebug() << "La valeur de l'angle de vue en x est maintenant : " << m_angleX;
    update();
}

void myOpenGLWidget::setAngleYVal(int value){
    m_angleY = value;
    qDebug() << "La valeur de l'angle de vue en y est maintenant : " << m_angleY;
    update();
}

void myOpenGLWidget::setSlider(float value){
    //pas = value;
    qDebug() << "La valeur de l'angle de vue en y est maintenant : " << m_angleY;
    update();
}





