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
    void siJoindrePartie(int idClient, QString indexPartie);

public slots:
    void run();

private slots:
    void slPartieCreee(int idClient);
    void slListePartie(int idClient, QString parties);
    void slTickClient(int idJoueurDroit, int idJoueurGauche);

private:
    int m_idClient;
    QString m_nomClient;
    QTcpSocket m_socket;
    int m_indexPartie;
};

#endif // TDCLIENT_H
