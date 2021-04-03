#include "polyset.h"


polySet::polySet(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
}

void polySet::generateGrid(int n, int m){
    while(!verticalLayout->isEmpty()) {
      delete verticalLayout->takeAt(0);
    }

    //init
    N = n;
    M = m;
    int pos;
    for (int i = 0; i < n; i++) {
        hbox[i] = new QHBoxLayout;
        verticalLayout->addLayout(hbox[i]);
        for (int j = 0; j < m; j++) {
            pos = i*n+j;
            pts[pos] = new ptsValue(this);
            pts[pos]->initName(pos);
            hbox[i]->addWidget(pts[pos]);
        }
    }
}

void polySet::on_buttonBox_accepted()
{
    qDebug() << __FUNCTION__;
    Point points[N*M];
    int pos;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            pos = i*N+j;
            points[pos] = pts[pos]->getPoint();
        }
    }
    emit polySetConfirmed(points, N, M);
}
