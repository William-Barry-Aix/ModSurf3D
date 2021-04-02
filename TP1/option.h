#ifndef OPTION_H
#define OPTION_H

#include "ui_option.h"
#include <QString>
#include <QtDebug>

class option : public QDialog, private Ui::option
{
    Q_OBJECT

public:
    explicit option(QWidget *parent = nullptr);
    void setValue(int angleX, int angleY, float pas);

signals:
    void comboBoxChanged(const QString arg1);
    void angleXsliderChanged(int position);
    void angleYsliderChanged(int position);
    void pasSliderChanged(int position);

private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_angleXslider_sliderMoved(int position);
    void on_angleYslider_sliderMoved(int position);
    void on_pasSlider_sliderMoved(int position);
};

#endif // OPTION_H
