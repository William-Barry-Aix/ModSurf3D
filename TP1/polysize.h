#ifndef POLYSIZE_H
#define POLYSIZE_H

#include "ui_polysize.h"

class polySize : public QDialog, private Ui::polySize
{
    Q_OBJECT

public:
    explicit polySize(QWidget *parent = nullptr);

private slots:
    void on_buttonBox_accepted();

signals :
    void polySizeConfirmed(int n, int m);
};

#endif // POLYSIZE_H
