#include <QtGui/QApplication>
#include "towerdefenseserveur.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TowerDefenseServeur w;
    w.show();
    
    return a.exec();
}
