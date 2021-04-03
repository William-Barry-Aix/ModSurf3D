#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QObject>
#include <QWidget>

#include <QKeyEvent>
#include <QTimer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include "segment.h"
#include "discretisation.h"
#include "discretisation3d.h"
#include "courbeparametrique.h"
#include "careauparametrique.h"
#include "globject.h"
#include <QString>

class myOpenGLWidget : public QOpenGLWidget,
			   protected QOpenGLFunctions
{
	Q_OBJECT

public:
    myOpenGLWidget(QWidget *parent = nullptr, int step = 10, QString mode = nullptr);
	~myOpenGLWidget();
    CarreauParametrique *carreau;
    void setAngleXVal(int value);
    void setAngleYVal(int value);
    void setSlider(float value);
    Point m_points;
    int m_step;
    QString m_mode;
    CarreauParametrique* sampleCarreau();

signals:  // On ne les implémente pas, elles seront générées par MOC ;
		  // les paramètres seront passés aux slots connectés.

protected slots:
	void onTimeout();

protected:
	void initializeGL() override;
	void doProjection();
	void resizeGL(int w, int h) override;
	void paintGL() override;
	void keyPressEvent(QKeyEvent *ev) override;
	void keyReleaseEvent(QKeyEvent *ev) override;
	void mousePressEvent(QMouseEvent *ev) override;
	void mouseReleaseEvent(QMouseEvent *ev) override;
	void mouseMoveEvent(QMouseEvent *ev) override;

private:
	double m_angleY = 0;
    double m_angleX = 0;
	QTimer *m_timer = nullptr;
	double m_ratio = 1;

	//RR matrices utiles
	QMatrix4x4 m_modelView;
	QMatrix4x4 m_projection;
	QMatrix4x4 m_model;

    QOpenGLShaderProgram *m_program;
    QOpenGLBuffer m_vbo;
    GLObject *segDiscr;

	void makeGLObjects();
	void tearGLObjects();
};


#endif // MYOPENGLWIDGET_H
