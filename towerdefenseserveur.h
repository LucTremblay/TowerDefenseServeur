#ifndef TOWERDEFENSESERVEUR_H
#define TOWERDEFENSESERVEUR_H

#include <QMainWindow>

namespace Ui {
class TowerDefenseServeur;
}

class TowerDefenseServeur : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TowerDefenseServeur(QWidget *parent = 0);
    ~TowerDefenseServeur();
    
private:
    Ui::TowerDefenseServeur *ui;
};

#endif // TOWERDEFENSESERVEUR_H
