#ifndef TDPARTIE_H
#define TDPARTIE_H

#include <QObject>
#include "QTimer"

class TDPartie : public QObject
{
    Q_OBJECT
public:
    explicit TDPartie(int indexPartie, QString nomJoueurDroit, QString nomPartie,
                      int mntArgent, int qteVie, QString nomMap);
    QString m_nomPartie;

signals:
    void siTick(int indexPartie);
    
public slots:

private slots:
    void slTick();
    void slJoindrePartie(QString nomJoueurGauche);

private:
    int m_indexPartie;
    int m_mntArgent;
    int m_qteVie;
    QString m_nomMap;

    QString m_nomJoueurDroit;

    QString m_nomJoueurGauche;

    QTimer *m_chrono;
};

#endif // TDPARTIE_H
