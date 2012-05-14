#include "tdpartie.h"

TDPartie::TDPartie(int indexPartie, QString nomJoueurDroit, QString nomPartie,
                   int mntArgent, int qteVie, QString nomMap)
{
    m_indexPartie = indexPartie;
    m_nomPartie = nomPartie;
    m_mntArgent = mntArgent;
    m_qteVie = qteVie;
    m_nomMap = nomMap;

    m_nomJoueurDroit = nomJoueurDroit;

    m_chrono = new QTimer();
    connect(m_chrono,SIGNAL(timeout()),SLOT(slTick()));
}

void TDPartie::slTick()
{
    emit(siTick(m_indexPartie));
}

void TDPartie::slJoindrePartie(QString nomJoueurGauche)
{
    m_nomJoueurGauche = nomJoueurGauche;
}
