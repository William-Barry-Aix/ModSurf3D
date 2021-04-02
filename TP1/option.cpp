#include "option.h"

option::option(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
}

void option::setValue(int angleX, int angleY, float pas){

}
void option::on_comboBox_currentIndexChanged(const QString &arg1)
{
    qDebug() << __FUNCTION__;
    emit comboBoxChanged(arg1);
}

void option::on_angleXslider_sliderMoved(int position)
{
    qDebug() << __FUNCTION__;
    emit angleXsliderChanged(position);
}

void option::on_angleYslider_sliderMoved(int position)
{
    qDebug() << __FUNCTION__;
    emit angleYsliderChanged(position);
}

void option::on_pasSlider_sliderMoved(int position)
{
    qDebug() << __FUNCTION__;
    emit pasSliderChanged(position);
}
