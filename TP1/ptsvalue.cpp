#include "ptsvalue.h"
#include <QString>

ptsValue::ptsValue(QWidget *parent) :
    QGroupBox(parent)
{
    setupUi(this);
}

void ptsValue::initName(int pos){
    name->setText(QString::number(pos));
}
