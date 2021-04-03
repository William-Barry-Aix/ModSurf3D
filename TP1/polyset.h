#ifndef POLYSET_H
#define POLYSET_H

#include "ui_polyset.h"
#include <QtDebug>
#include "ptsvalue.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

class polySet : public QDialog, private Ui::polySet
{
    Q_OBJECT

public:
    explicit polySet(QWidget *parent = nullptr);
    void generateGrid(int n, int m);
    //ptsValue *pts;
    int N, M;
    ptsValue *pts[60];
    QHBoxLayout *hbox[];

private slots:
    void on_buttonBox_accepted();

signals :
    void polySetConfirmed(Point points[], int N, int M);
};

#endif // POLYSET_H
