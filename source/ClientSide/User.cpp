#include "User.h"

#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTcpSocket>
#include <QNetworkProxy>

User::User(const QString& iName, const QHostAddress& iHost, int iPort, QObject* ipParent)
  : QObject(ipParent)
  , _name(iName)
  , _host(iHost)
  , _port(iPort)
{
  _pSocket = new QTcpSocket(this);

  connect(_pSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));

  connect(_pSocket, SIGNAL(connected()), this, SLOT(serverConnected()));
  connect(_pSocket, SIGNAL(disconnected()), this, SLOT(serverDisconnected()));
  connect(_pSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(serverError(QAbstractSocket::SocketError)));
}

void User::sendToServer(const QString& iMessage)
{
  if (iMessage.isEmpty())
    return;

  if (_pSocket->state() != QAbstractSocket::ConnectedState)
    return;

  QDataStream socketStream(_pSocket);
  QJsonObject message;
  message["user_name"] = _name;
  message["message"] = iMessage;
  socketStream << message;

  emit sendToChat(QString("%1: %2").arg("you", iMessage));
}

void User::connectToServer()
{
  emit sendToChat("Connecting to chat");
  _pSocket->connectToHost(_host, _port);
}

void User::disconnectFromServer()
{
  emit sendToChat("Disconnecting from chat");
  _pSocket->disconnectFromHost();
}

void User::onReadyRead()
{
  QString data;
  QDataStream socketStream(_pSocket);
  socketStream >> data;

  QJsonDocument json = QJsonDocument::fromJson(data.toUtf8());
  QJsonObject message = json.object();

  emit sendToChat(QString("%1: %2").arg(message["user_name"].toString(), message["message"].toString()));
}

void User::serverConnected()
{
  QString message("%1 joined to chat");

  // send to server new user name
  QDataStream socketStream(_pSocket);
  QJsonObject jsonName;
  jsonName["user_name"] = _name;
  jsonName["message"] = "joined to chat";
  socketStream << jsonName;

  // update gui
  emit sendToChat(message.arg("You"));
}

void User::serverDisconnected()
{
  emit sendToChat("left from chat");
}

void User::serverError(QAbstractSocket::SocketError)
{
  emit sendToChat("you are offline");
}