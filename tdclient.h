#ifndef TDCLIENT_H
#define TDCLIENT_H

#include <QThread>
#include <QtNetwork/QTcpSocket>

class TDClient : public QThread
{
Q_OBJECT
public:
    explicit TDClient(int socketDescriptor);

signals:

public slots:
    void run();

private:
    int m_socketDescriptor;
};

#endif // TDCLIENT_H
