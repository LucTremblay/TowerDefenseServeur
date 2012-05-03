#include "tdclient.h"
#include <QStringList>

TDClient::TDClient(int socketDescriptor,int idClient)
{
    //Initialisation du socketdescriptor dans le cconstructeur
    m_socket.setSocketDescriptor(socketDescriptor);
    m_idClient = idClient;
}
//
void TDClient::run()
{
    QByteArray bChaine;

    while (m_socket.state() == QTcpSocket::ConnectedState)
    {
        m_socket.waitForReadyRead();
        bChaine = m_socket.read(m_socket.bytesAvailable());

        if (bChaine.length() >= 2)
        {
            QStringList parametre = QString(bChaine.mid(1, bChaine.length() - 1)).split("/");
            m_nomClient = parametre.at(0);

            if (bChaine.left(1) == "1")
            {
                //Création d'une nouvelle partie
                emit(siCreerPartie(m_idClient, m_nomClient, parametre.at(1)));
            }
            else
            {
                if (bChaine.left(1) == "2")
                {
                    //Obtenir la liste des parties créées une partie
                    emit(siObtenirParties(m_idClient));
                }
            }
        }
    }
}

void TDClient::slPartieCreee(int idClient)
{
    if (idClient == m_idClient)
    {
        m_socket.write("partie créée");
    }
}

void TDClient::slListePartie(int idClient, QString parties)
{
    parties = parties.remove(parties.length() - 1);
    if (idClient == m_idClient)
    {
        m_socket.write(parties.toAscii());
    }
}
