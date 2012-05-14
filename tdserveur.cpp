#include "tdserveur.h"
#include "tdclient.h"
#include "tdpartie.h"

TDServeur::TDServeur()
{
    m_idClienGen = 0;//Génere un identifiant unique pour chaque client
}

void TDServeur::incomingConnection(int socketDescriptor)
{
    m_idClienGen += 1;
    TDClient *Client = new TDClient(socketDescriptor, m_idClienGen);

    connect(Client, SIGNAL(siCreerPartie(int,QString,QString,int,int,QString)),
            this,   SLOT(slCreerPartie(int,QString,QString,int,int,QString)));
    connect(this, SIGNAL(siPartieCreee(int)), Client, SLOT(slPartieCreee(int)));
    connect(Client, SIGNAL(siObtenirParties(int)), this, SLOT(slObtenirParties(int)));
    connect(this,   SIGNAL(siListeParties(int, QString)),
            Client, SLOT(slListePartie(int, QString)));
    connect(this, SIGNAL(siTickClient(int,int)), Client, SLOT(slTickClient(int,int)));

    Client->run();
}

void TDServeur::slCreerPartie(int idClient, QString nomJoueur, QString nomPartie,
                              int mntArgent, int qteVie, QString nomMap)
{
    TDPartie *Partie = new TDPartie(m_parties.count(), nomJoueur, nomPartie,
                                    mntArgent, qteVie, nomMap);

    connect(Partie, SIGNAL(siTick(int)), this, SLOT(slTickPartie(int)));

    m_parties.append(Partie);
    emit(siPartieCreee(idClient));
}

void TDServeur::slObtenirParties(int idClient)
{
    QString parties;
    foreach (TDPartie *partie, m_parties)
    {
        parties += partie->m_nomPartie;
        parties += "#";
    }
    emit(siListeParties(idClient, parties));
}

void TDServeur::slTickPartie(int indexPartie)
{
    emit(siTickClient(indexPartie));
}
