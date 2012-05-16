#include "tdpartie.h"
#include <QFile>

TDPartie::TDPartie(int indexPartie, int idJoueurDroit, QString nomJoueurDroit, QString nomPartie,
                   int mntArgent, int qteVie, QString nomMap)
{
    m_indexPartie = indexPartie;
    m_nomPartie = nomPartie;
    m_mntArgent = mntArgent;
    m_qteVie = qteVie;
    m_nomMap = nomMap;

    m_nomJoueurDroit = nomJoueurDroit;
    m_idJoueurDroit = idJoueurDroit;
    m_nomJoueurGauche = "";
    m_idJoueurGauche = -1;

    m_chrono = new QTimer();
    connect(m_chrono,SIGNAL(timeout()),SLOT(slTick()));
    m_frameRate = new QTimer();
    connect(m_frameRate, SIGNAL(timeout()), SLOT(slFrame()));

    QFile fichierWave("image/wave.txt");
    fichierWave.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray contenuFichier = fichierWave.readAll();
    m_waves = QString(contenuFichier).split("\n");
    m_indexWave = 0;
    m_temps = m_waves.at(m_indexWave).split("#").at(0).toInt();
}

void TDPartie::slTick()
{
    if (m_temps > 0)
    {
        emit(siTick(m_indexPartie, m_temps));
        m_temps--;
    }
    else
    {
        QStringList monstre = m_waves.at(m_indexWave).split("#");
        emit(siWave(m_indexPartie, monstre.at(1).toInt(), monstre.at(2).toInt()));
        m_indexWave++;
        m_temps = m_waves.at(m_indexWave).split("#").at(0).toInt();
    }
}

void TDPartie::slFrame()
{
    emit(siFrame(m_indexPartie));
}

bool TDPartie::slJoindrePartie(int idJoueurGauche, QString nomJoueurGauche)
{
    if (m_idJoueurGauche == -1)
    {
        m_nomJoueurGauche = nomJoueurGauche;
        m_idJoueurGauche = idJoueurGauche;
        m_chrono->start(1000);
        m_frameRate->start(40);
        return true;
    }
    else
        return false;
}

int TDPartie::slObtenirAutreJoueur(int idJoueur)
{
    if (idJoueur == m_idJoueurDroit)
        return m_idJoueurGauche;
    else if (idJoueur == m_idJoueurGauche)
        return m_idJoueurDroit;
}
