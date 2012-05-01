#include "tdserveur.h"
#include "tdclient.h"

TDServeur::TDServeur()
{
}

void TDServeur::incomingConnection(int socketDescriptor)
{
    TDClient *Client = new TDClient(socketDescriptor);
    Client->run();
}
