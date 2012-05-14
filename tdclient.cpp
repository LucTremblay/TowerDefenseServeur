#include "tdclient.h"
#include <QStringList>

TDClient::TDClient(int socketDescriptor,int idClient)
{

    m_socket.setSocketDescriptor(socketDescriptor);
    m_idClient = idClient;
}
void TDClient::run()
{
    QByteArray bChaine;

    while (m_socket.state() == QTcpSocket::ConnectedState)
    {
        if (m_socket.waitForReadyRead(30000));//30 secondes
        {
            bChaine = m_socket.read(m_socket.bytesAvailable());
            QStringList parametre = QString(bChaine).split("#");//données de trames séparées par des #

            switch (parametre.at(0).toInt())//premier parametre = code de l'instruction
            {
                case 1://Création d'une nouvelle partie
                                                 //   nomJoueur        nomPartie
                    emit(siCreerPartie(m_idClient, parametre.at(1), parametre.at(2),
                                      // montantArgent                 nombreVie
                                       parametre.at(3).toInt(),  parametre.at(4).toInt(),
                                     //     nomMap
                                       parametre.at(5)));
                    break;

                case 2://Obtenir la liste des parties créées

                    emit(siObtenirParties(m_idClient));
                    break;

                case 3://Joindre une partie
                                                   //  indexPartie
                    emit(siJoindrePartie(m_idClient, parametre.at(1)));
                    break;


                //TODO: Ajouté des nouvelles instructions

                default:;//Instruction inconnue
            }
        }
    }
}

void TDClient::slPartieCreee(int idClient)
{
    if (idClient == m_idClient)
    {
        m_socket.write("#");
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

void TDClient::slTickClient(int idJoueurDroit, int idJoueurGauche)
{

}
