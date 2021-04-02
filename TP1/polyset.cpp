#include "polyset.h"


polySet::polySet(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
}

void polySet::generateGrid(int n, int m){
    //init
    int size = n*m;
    N = n;
    M = m;
    //pts = (ptsValue*) malloc(size * sizeof (ptsValue));
    ptsValue *pts[size];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pts[size] = new ptsValue(this);
            pts[size]->initName(i * n + j);
            gridLayout->addWidget(pts[size],i,j);
        }
    }
}

void polySet::on_buttonBox_accepted()
{
    qDebug() << __FUNCTION__;
    //emit polySetConfirmed(pts, N, M);
}
