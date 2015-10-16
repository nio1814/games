#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>

class ChatServer : public QObject
{
    Q_OBJECT
public:
    ChatServer(QObject *parent = 0);

signals:

public slots:
};

#endif // CHATSERVER_H
