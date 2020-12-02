#pragma once

#include <QObject>

class QTcpSocket;

// Server side client class
// sends and receives messages to client
// contains QTcpSocket object
class ServerUser: public QObject
{
  Q_OBJECT
public:
  ServerUser(QTcpSocket* ipSocket, QObject* ipParent);
  void sendToClient(const QString& iMessage) const;

private slots:
  void onReadyRead();

signals:
  void sendMessage(const QString& iMessage);
  void disconnected();

private:
  QTcpSocket* _pSocket;
};
