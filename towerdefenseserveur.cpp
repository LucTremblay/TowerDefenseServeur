#include "towerdefenseserveur.h"
#include "ui_towerdefenseserveur.h"


TowerDefenseServeur::TowerDefenseServeur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TowerDefenseServeur)
{
    ui->setupUi(this);

    Serveur = new TDServeur;
    if (!Serveur->listen(QHostAddress::Any, 87878))
        QMessageBox::information(this, "ERREUR","ERREUR LISTEN");
}

TowerDefenseServeur::~TowerDefenseServeur()
{
    delete ui;
}
