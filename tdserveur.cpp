#include "tdserveur.h"
#include "tdclient.h"
#include "tdpartie.h"

TDServeur::TDServeur()
{
    m_idClienGen = 0;//Génere un identifiant unique pour chaque client
    m_idPartieGen = 0;//Génere un identifiant unique pour chaque partie
}

void TDServeur::incomingConnection(int socketDescriptor)
{
    m_idClienGen += 1;
    TDClient *Client = new TDClient(socketDescriptor, m_idClienGen);

    connect(Client, SIGNAL(siCreerPartie(int,QString, QString)), this, SLOT(slCreerPartie(int,QString, QString)));
    connect(this, SIGNAL(siPartieCreee(int)), Client, SLOT(slPartieCreee(int)));
    connect(Client, SIGNAL(siObtenirParties(int)), this, SLOT(slObtenirParties(int)));
    connect(this, SIGNAL(siListeParties(int, QString)), Client, SLOT(slListePartie(int, QString)));

    Client->run();
}

void TDServeur::slCreerPartie(int idClient, QString nomClient, QString nomPartie)
{
    TDPartie *Partie = new TDPartie(idClient, nomClient, nomPartie);
    m_parties.append(Partie);
    emit(siPartieCreee(idClient));
}

void TDServeur::slObtenirParties(int idClient)
{
    QString parties;
    foreach (TDPartie *partie, m_parties)
    {
        parties += partie->m_nomPartie;
        parties += "/";
    }
    emit(siListeParties(idClient, parties));
}
