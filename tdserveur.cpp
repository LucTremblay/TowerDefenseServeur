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

    //serveur <-créée-partie- client
    connect(Client, SIGNAL(siCreerPartie(int,QString,QString,int,int,QString)),
            this,   SLOT(slCreerPartie(int,QString,QString,int,int,QString)));

    //serveur -partie-créée-> client
    connect(this, SIGNAL(siPartieCreee(int)), Client, SLOT(slPartieCreee(int)));

    //serveur <-obtenir-partie- client
    connect(Client, SIGNAL(siObtenirParties(int)), this, SLOT(slObtenirParties(int)));

    //serveur -voici-partie-> client
    connect(this,   SIGNAL(siListeParties(int, QString)),
            Client, SLOT(slListePartie(int, QString)));

    //serveur <-joindre-partie- client
    connect(Client, SIGNAL(siJoindrePartie(int,QString,int)),
            this,   SLOT(slJoindrePartie(int,QString,int)));

    //serveur -partie-joint-> client
    connect(this, SIGNAL(siPartieJoint(int, bool)), Client, SLOT(slPartieJoint(int, bool)));

    //serveur -1-seconde-ecoulée-> client
    connect(this, SIGNAL(siTickClient(int,int)), Client, SLOT(slTickClient(int,int)));

    //serveur -rafraichir-ecran-> client
    connect(this, SIGNAL(siFrameClient(int)), Client, SLOT(slFrameClient(int)));

    //serveur <-tour-créée- client1
    connect(Client, SIGNAL(siTourCreee(int,int,int,int,int)),
            this,   SLOT(slTourCreee(int,int,int,int,int)));

    //serveur -tour-créée-> client2
    connect(this,   SIGNAL(siAviserTourCreee(int,int,int,int)),
            Client, SLOT(slAviserTourCreee(int,int,int,int)));

    //serveur <-vie-perdu- client1
    connect(Client, SIGNAL(siViePerdu(int,int)), this, SLOT(slViePerdu(int,int)));

    //serveur -vie-perdu-> client2
    connect(this, SIGNAL(siAviserViePerdu(int)), Client, SLOT(slAviserViePerdu(int)));


    Client->run();
}

void TDServeur::slCreerPartie(int idClient, QString nomJoueur, QString nomPartie,
                              int mntArgent, int qteVie, QString nomMap)
{
    TDPartie *Partie = new TDPartie(m_parties.count(),idClient, nomJoueur, nomPartie,
                                    mntArgent, qteVie, nomMap);

    connect(Partie, SIGNAL(siTick(int)), this, SLOT(slTickPartie(int)));
    connect(Partie, SIGNAL(siFrame(int)), this, SLOT(slFramePartie(int)));

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

void TDServeur::slJoindrePartie(int idJoueur, QString nomJoueur, int indexPartie)
{
    if (m_parties.count() - 1 >= indexPartie)
    {
        bool partiePleine = m_parties.at(indexPartie)->slJoindrePartie(idJoueur, nomJoueur);
        emit(siPartieJoint(idJoueur, partiePleine));
    }
}

void TDServeur::slTickPartie(int indexPartie, int temps)
{
    emit(siTickClient(indexPartie, temps));
}

void TDServeur::slFramePartie(int indexPartie)
{
    emit(siFrameClient(indexPartie));
}

void TDServeur::slViePerdu(int idClient, int indexPartie)
{
    int idAutreJoueur = m_parties.at(indexPartie)->slObtenirAutreJoueur(idClient);
    emit(siAviserViePerdu(idAutreJoueur));
}

void TDServeur::slTourCreee(int idClient, int indexPartie, int caseX, int caseY, int typeTour)
{
    int idAutreJoueur = m_parties.at(indexPartie)->slObtenirAutreJoueur(idClient);
    emit(siAviserTourCreee(idAutreJoueur,caseX, caseY, typeTour));
}
