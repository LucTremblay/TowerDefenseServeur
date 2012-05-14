#ifndef TDSERVEUR_H
#define TDSERVEUR_H

#include <QTcpServer>
#include "tdpartie.h"

class TDServeur : public QTcpServer
{
Q_OBJECT
public:
    explicit TDServeur();

signals:
    void siPartieCreee(int idClient);
    void siListeParties(int idClient, QString parties);
    void siTickClient(int indexPartie);

public slots:

private slots:
    void incomingConnection(int socketDescriptor);
    void slCreerPartie(int idClient, QString nomClient, QString nomPartie,
                       int mntArgent, int qteVie, QString nomMap);
    void slObtenirParties(int idClient);
    void slTickPartie(int indexPartie);


private:
    int m_idClienGen;
    int m_idPartieGen;
    QList<TDPartie*> m_parties;
};

#endif // TDSERVEUR_H
