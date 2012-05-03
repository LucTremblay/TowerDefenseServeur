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
    void siCreerPartie(int idClient, QString nomClient, QString nomPartie);
    void siPartieCreee(int idClient);
    void siObtenirParties(int idClient);
    void siListeParties(int idClient, QString parties);

public slots:
    void run();

private slots:
    void slPartieCreee(int idClient);
    void slListePartie(int idClient, QString parties);

private:
    int m_idClient;
    QString m_nomClient;
    QTcpSocket m_socket;
    int m_indexPartie;
};

#endif // TDCLIENT_H
