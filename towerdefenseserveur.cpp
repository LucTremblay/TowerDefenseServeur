#include "towerdefenseserveur.h"
#include "ui_towerdefenseserveur.h"
#include  <QtNetwork/QTcpServer>

TowerDefenseServeur::TowerDefenseServeur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TowerDefenseServeur)
{
    ui->setupUi(this);
}

TowerDefenseServeur::~TowerDefenseServeur()
{
    delete ui;
}
