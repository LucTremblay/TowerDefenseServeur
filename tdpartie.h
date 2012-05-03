#ifndef TDPARTIE_H
#define TDPARTIE_H

#include <QObject>

class TDPartie : public QObject
{
    Q_OBJECT
public:
    explicit TDPartie(int idJoueurDroit, QString nomJoueurDroit, QString nomPartie);
    QString m_nomPartie;
    
signals:
    
public slots:

private:
    int m_idPartie;
    int m_idJoueurDroit;
    int m_idJoueurGauche;
    QString m_nomJoueurDroit;
    QString m_nomJoueurGauche;
};

#endif // TDPARTIE_H
