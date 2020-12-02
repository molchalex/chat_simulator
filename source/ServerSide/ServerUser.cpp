#include "ServerUser.h"

#include <QTcpSocket>
#include <QDataStream>
#include <QJsonObject>

ServerUser::ServerUser(QTcpSocket* ipSocket, QObject* ipParent)
  : QObject(ipParent)
  , _pSocket(ipSocket)
{
  connect(_pSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
  connect(_pSocket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
}

void ServerUser::onReadyRead()
{
  QByteArray data;
  QDataStream socketStream(_pSocket);
  socketStream >> data;
  emit sendMessage(data);
}

void ServerUser::sendToClient(const QString& iMessage) const
{
  if (iMessage.isEmpty())
    return;

  if (_pSocket->state() != QAbstractSocket::ConnectedState)
    return;

  QDataStream socketStream(_pSocket);
  socketStream << iMessage;
}