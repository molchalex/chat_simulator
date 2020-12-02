#pragma once

#include <QObject>
#include <QHostAddress>

class QTcpSocket;

// Client class
// sends and receives messages to server
// contains QTcpSocket object
class User: public QObject
{
  Q_OBJECT
public:
  User(const QString& iName, const QHostAddress& iHost, int iPort, QObject* ipParent);

  const QString& getUserName() const { return _name; }

public slots:
  void sendToServer(const QString& iMessage);
  void connectToServer();
  void disconnectFromServer();

private slots:
  void onReadyRead();
  void serverConnected();
  void serverDisconnected();
  void serverError(QAbstractSocket::SocketError);

signals:
  void sendToChat(const QString& iMessage);

private:
  QString _name;
  QHostAddress _host;
  int _port;

  QTcpSocket* _pSocket;
};