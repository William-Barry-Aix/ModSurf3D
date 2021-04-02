#include "polysize.h"
#include <QtDebug>

polySize::polySize(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
}


void polySize::on_buttonBox_accepted()
{
    qDebug() << __FUNCTION__;
    emit polySizeConfirmed(lineEdit->text().toInt(), lineEdit_2->text().toInt());
}

