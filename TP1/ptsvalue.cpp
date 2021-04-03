#include "ptsvalue.h"
#include <QString>
#include <QLayoutItem>

ptsValue::ptsValue(QWidget *parent) :
    QGroupBox(parent)
{
    setupUi(this);
}

void ptsValue::initName(int pos){
    name->setText(QString::number(pos));
}

Point ptsValue::getPoint(){
    Point *point = new Point;
    point->setX(textX->text().toFloat());
    point->setY(textX->text().toFloat());
    point->setZ(textX->text().toFloat());
    return *point;
}
