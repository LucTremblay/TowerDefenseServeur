#ifndef TDCLIENT_H
#define TDCLIENT_H

#include <QThread>
#include <QtNetwork/QTcpSocket>

class TDClient : public QThread
{
Q_OBJECT
public:
    explicit TDClient(int socketDescriptor, int idClient);

signals:
    void siCreerPartie(int idClient, QString nomClient, QString nomPartie,
                       int mntArgent, int qteVie, QString nomMap);
    void siObtenirParties(int idClient);
    void siJoindrePartie(int idClient, QString nomClient, int indexPartie);
    void siViePerdu(int idClient, int indexPartie);
    void siTourCreee(int idClient, int indexPartie, int caseX, int caseY, int typeTour);

public slots:
    void run();

private slots:
    void slPartieCreee(int idClient);
    void slListePartie(int idClient, QString parties);
    void slPartieJoint(int idClient, bool partiePleine);
    void slTickClient(int indexPartie, int temps);
    void slFrameClient(int indexPartie);
    void slAviserViePerdu(int idClient);
    void slAviserTourCreee(int idClient, int caseX, int caseY, int typeTour);

private:
    int m_idClient;
    QString m_nomClient;
    QTcpSocket m_socket;
    int m_indexPartie;
};

#endif // TDCLIENT_H
