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

public slots:

private slots:
    void incomingConnection(int socketDescriptor);
    void slCreerPartie(int idClient, QString nomClient, QString nomPartie);
    void slObtenirParties(int idClient);

private:
    int m_idClienGen;
    int m_idPartieGen;
    QList<TDPartie*> m_parties;
};

#endif // TDSERVEUR_H
