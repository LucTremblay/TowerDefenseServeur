#ifndef TDPARTIE_H
#define TDPARTIE_H

#include <QObject>
#include "QTimer"
#include <QStringList>

class TDPartie : public QObject
{
    Q_OBJECT
public:
    explicit TDPartie(int indexPartie, int idJoueurDroit, QString nomJoueurDroit, QString nomPartie,
                      int mntArgent, int qteVie, QString nomMap);
    QString m_nomPartie;

signals:
    void siTick(int indexPartie, int temps);
    void siFrame(int indexPartie);
    void siWave(int indexPartie, int monstreType1, int monstreType2);
    
public slots:
    bool slJoindrePartie(int idJoueurGauche, QString nomJoueurGauche);
    int slObtenirAutreJoueur(int idJoueur);

private slots:
    void slTick();
    void slFrame();

private:
    int m_indexPartie;
    int m_mntArgent;
    int m_qteVie;
    QString m_nomMap;
    int m_temps;
    int m_indexWave;
    QStringList m_waves;

    QString m_nomJoueurDroit;
    int m_idJoueurDroit;
    QString m_nomJoueurGauche;
    int m_idJoueurGauche;

    QTimer *m_chrono;
    QTimer *m_frameRate;
};

#endif // TDPARTIE_H
