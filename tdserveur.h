#ifndef TDSERVEUR_H
#define TDSERVEUR_H

#include <QTcpServer>

class TDServeur : public QTcpServer
{
Q_OBJECT
public:
    explicit TDServeur();

signals:

public slots:

private slots:
    void incomingConnection(int socketDescriptor);

};

#endif // TDSERVEUR_H
