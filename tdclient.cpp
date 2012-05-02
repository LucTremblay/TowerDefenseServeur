#include "tdclient.h"

TDClient::TDClient(int socketDescriptor)
{
    //Initialisation du socketdescriptor dans le cconstructeur
    m_socketDescriptor = socketDescriptor;
}

void TDClient::run()
{
    //Attribution du socketdescriptor du client au socket
    QTcpSocket socket;
    socket.setSocketDescriptor(m_socketDescriptor);


}
