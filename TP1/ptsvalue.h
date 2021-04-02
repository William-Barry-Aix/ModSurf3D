#ifndef PTSVALUE_H
#define PTSVALUE_H

#include "ui_ptsvalue.h"

class ptsValue : public QGroupBox, private Ui::ptsValue
{
    Q_OBJECT

public:
    explicit ptsValue(QWidget *parent = nullptr);
    void initName(int pos);
};

#endif // PTSVALUE_H
