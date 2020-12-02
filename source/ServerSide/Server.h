#pragma once

#include <QMap>
#include <QTcpServer>

class ServerUser;

// Server side class
// contains QTcpServer
// manages connected users
class Server: public QObject
{
  Q_OBJECT
public:
  Server(const QHostAddress& iHost, int iPort);

public slots:
  void start();
  void stop();

private slots:
  void newUser();
  void removeUser();
  void serverError(QAbstractSocket::SocketError iError);
  void sendMessage(const QString& iMessage);

signals:
  void printLog(const QString& iMessage);

private:
  QTcpServer* _pTcpServer;
  QHostAddress _host;
  int _port;

  QList<ServerUser*> _users;
};
