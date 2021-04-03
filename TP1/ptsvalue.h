#ifndef PTSVALUE_H
#define PTSVALUE_H

#include "ui_ptsvalue.h"
#include "point.h"

class ptsValue : public QGroupBox, private Ui::ptsValue
{
    Q_OBJECT

public:
    explicit ptsValue(QWidget *parent = nullptr);
    void initName(int pos);
    Point getPoint();

};

#endif // PTSVALUE_H
