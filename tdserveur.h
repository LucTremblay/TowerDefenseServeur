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
    void siPartieJoint(int idClient, bool partiePleine);
    void siTickClient(int indexPartie, int temps);
    void siFrameClient(int indexPartie);
    void siAviserViePerdu(int idClient);
    void siAviserTourCreee(int idClient, int caseX, int caseY, int typeTour);

public slots:

private slots:
    void incomingConnection(int socketDescriptor);
    void slCreerPartie(int idClient, QString nomClient, QString nomPartie,
                       int mntArgent, int qteVie, QString nomMap);
    void slObtenirParties(int idClient);
    void slJoindrePartie(int idJoueur, QString nomJoueur, int indexPartie);
    void slTickPartie(int indexPartie, int temps);
    void slFramePartie(int indexPartie);
    void slViePerdu(int idClient, int indexPartie);
    void slTourCreee(int idClient, int indexPartie, int caseX, int caseY, int typeTour);


private:
    int m_idClienGen;
    int m_idPartieGen;
    QList<TDPartie*> m_parties;
};

#endif // TDSERVEUR_H
