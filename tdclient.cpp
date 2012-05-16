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
                case 4://Nouvelle tour
                                                               //        caseX
                    emit(siTourCreee(m_idClient, m_indexPartie, parametre.at(1).toInt(),
                                     //        caseY                typeTour
                                     parametre.at(2).toInt(), parametre.at(3).toInt()));
                    break;

                case 5://Vie Perdu

                    emit(siViePerdu(m_idClient, m_indexPartie));
                    break;

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
                                                    //  nomJoueur           indexPartie
                    emit(siJoindrePartie(m_idClient, parametre.at(1), parametre.at(2).toInt()));
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
    if (idClient == m_idClient)
    {
        parties = parties.remove(parties.length() - 1);
        m_socket.write(parties.toAscii());
    }
    QTcpSocket m_socket;
}

void TDClient::slPartieJoint(int idClient, bool partiePleine)
{
    if (idClient == m_idClient)
    {
        if (partiePleine)
            m_socket.write("@");
        else
            m_socket.write("#");
    }
}

void TDClient::slTickClient(int indexPartie, int temps)
{
    if (indexPartie == m_indexPartie)
    {
        QString strTrame = QString("1") + "#" + temps;
        m_socket.write(strTrame.toAscii());
    }
}

void TDClient::slFrameClient(int indexPartie)
{
    if (indexPartie == m_indexPartie)
    {
        m_socket.write(QString("2").toAscii());
    }
}

void TDClient::slAviserTourCreee(int idClient, int caseX, int caseY, int typeTour)
{
    if(idClient = m_idClient)
    {
        QString strTrame = QString("3") + QString(caseX) + QString(caseY) + QString(typeTour);
        m_socket.write(strTrame.toAscii());
    }
}

void TDClient::slAviserViePerdu(int idClient)
{
    if(idClient = m_idClient)
    {
        m_socket.write(QString("4").toAscii());
    }
}
