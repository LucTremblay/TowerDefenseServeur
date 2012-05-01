#ifndef TDCLIENT_H
#define TDCLIENT_H

#include <QThread>

class TDClient : public QThread
{
Q_OBJECT
public:
    explicit TDClient(int socketDescriptor);

signals:

public slots:
    void run();
};

#endif // TDCLIENT_H
